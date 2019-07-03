#include "Context.h"
#include <iostream>
#include "glad/glad/glad.h"

constexpr int HEIGHT = 600;
constexpr int WIDTH = 800;

Context::Context()
{
    sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
    context.create(sf::VideoMode(WIDTH, HEIGHT), "TechnoMagica", sf::Style::Default, settings);
    //context.setFramerateLimit(60);
    initAPI();
}

Context::~Context()
{
    //context.close();
}

sf::RenderWindow* Context::getContext()
{
    return &context;
}

void Context::clear()
{
    //context.clear(sf::Color::Black);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Context::update()
{
    context.display();
}

void Context::draw()
{

}

void Context::close()
{
	context.close();
}

void Context::initAPI()
{
	gladLoadGL();
	glViewport(0, 0, WIDTH, HEIGHT);
}

bool Context::isOpen()
{
    return context.isOpen();
}
