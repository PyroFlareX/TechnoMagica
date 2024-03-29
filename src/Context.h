#ifndef CONTEXT_H
#define CONTEXT_H

#include <SFML/Graphics.hpp>

constexpr int HEIGHT = 600;
constexpr int WIDTH = 800;

class Context
{
    public:
        Context();

        sf::RenderWindow* getContext();
        void clear();
        void update();
        void draw();
		void close();
        void initAPI();
        bool isOpen();

        ~Context();
    protected:

    private:
        sf::RenderWindow context;
};

#endif // CONTEXT_H
