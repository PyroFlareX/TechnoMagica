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


	sf::Clock timer;
	sf::Time dt;
	float t = 0;
	int frames = 0;
	m_context.clear();
	m_context.update();
    sf::RenderWindow* p_window = m_context.getContext();
	Camera cam(p_window);


	//GL Stuff
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	//Generate and Bind VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	//Other stuff
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Make a VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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
