#include "Application.h"

#include "States/Gamestate.h"
#include "Shaders/Shader.h"


Application::Application()
{
	pushState(std::make_unique<GameState>());
}

void Application::RunLoop()
{
	sf::Clock timer;
	sf::Time dt;
	float t = 0;
	float frames = 0.0f;
	m_context.clear();
	m_context.update();
    sf::RenderWindow* p_window = m_context.getContext();
	Camera cam(p_window);
//===================================================================================

	//GL Stuff
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	sf::Image img;
	img.loadFromFile("res/container.jpg");
	sf::Texture tex;
	tex.loadFromImage(img);
	tex.bind(&tex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex.generateMipmap();

	tex.bind(NULL);


	Shader shader("res/Shaders/vert.glsl", "res/Shaders/frag.glsl");

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
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


		shader.use();
		tex.bind(&tex);
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

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
