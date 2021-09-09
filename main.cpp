#include "stdafx.h"

enum class States { Menu, Game };

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Air Penguin");
    sf::Clock clock;

    MenuState menu;
    GameState game;

    States currentState = States::Game;

    while (window.isOpen())
    {
        //Deltatime computation
        float dt = clock.restart().asSeconds();

        //Events manegement
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Update
        if (currentState == States::Menu)
        {
            menu.update(dt);

            if (menu.isClick())
                currentState = States::Game;
        }
        else if (currentState == States::Game)
        {
            if (game.getEndStatus())
            {
                game.reset();
                currentState = States::Menu;
            }
            else
            {
                game.update(dt);
            }
            
        }

        //Draw
        window.clear();

        if (currentState == States::Menu)
            menu.draw(window);
        else if (currentState == States::Game)
            game.draw(window);
        
        window.display();
    }

    return 0;
}