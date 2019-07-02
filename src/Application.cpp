#include "Application.h"

#include "States/Gamestate.h"
#include "Util/FileUtil.h"
#include "glad/glad/glad.h"


Application::Application()
{
	pushState(std::make_unique<GameState>());
}

void Application::RunLoop()
{
	std::string vertSource = getFileContents("res/Shaders/vert.glsl");
	const char* vertPtr = vertSource.c_str();
	std::string fragSource = getFileContents("res/Shaders/frag.glsl");
	const char* fragPtr = fragSource.c_str();

	//Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertPtr, NULL);
	glCompileShader(vertexShader);

	//Check Success of Vert Shader
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragPtr, NULL);
	glCompileShader(fragmentShader);

	//Check Success of Frag Shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check Success of Program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR! Program Stuff failed!\n" << infoLog << "\n";
	}

	//Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
//===================================================================================

	sf::Clock timer;
	sf::Time dt;
	float t = 0;
	int frames = 0;
	m_context.clear();
	m_context.update();
    sf::RenderWindow* p_window = m_context.getContext();
	Camera cam(p_window);
//===================================================================================

	//GL Stuff
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
//==============================================================================
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); //VAO
	glGenBuffers(1, &VBO);		//Gen VBO
	glGenBuffers(1, &EBO);		//Gen EBO
	glBindVertexArray(VAO);		//Bind VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//Store Verticies

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//Store Indicies

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

//===================================================================================

	//Main Loop
    while(m_context.isOpen() && !m_states.empty())
    {
		dt = timer.restart();
        ///Main Loop, do cycle of Input, Update, Draw, Render & Swap Buffers, Handle Events
        ///Input
		currentState().input(*this);

        /// Update
        currentState().update(p_window, dt.asSeconds());
		currentState().lateUpdate(&cam);

        /// Draw
		currentState().render(&m_renderer);

        /// Render
		m_context.clear();
		m_renderer.render(p_window);


		float timeValue = frames / 10.0f;
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, greenValue, 0.0f, 0.0f, 1.0f);


		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        m_context.update();

        /// Handle Window Events
		t += timer.getElapsedTime().asSeconds();
		frames++;
		if (t >= 1)
		{
			std::cout << frames << " per sec\n";
			t = 0;
			frames = 0;
		}
		handleEvents();
    }
}

void Application::popState()
{
    m_states.pop_back();
}

Basestate& Application::currentState()
{
    return *m_states.back();
}

void Application::handleEvents()
{
    sf::Event e;
	sf::View v;
    while(m_context.getContext()->pollEvent(e))
        {
        switch(e.type)
			{
			case sf::Event::Closed:
				m_context.close();
				break;

			case sf::Event::Resized:
				// update the view to the new size of the window
				v = m_context.getContext()->getView();
				v.setSize(e.size.width, e.size.height);
				m_context.getContext()->setView(v);

			case sf::Event::KeyPressed:
				switch(e.key.code)
				{
				    case sf::Keyboard::Escape:
						m_context.close();
					    break;

	                default:
		                break;
            }
            break;

        default:
            break;
        }
    }

}
