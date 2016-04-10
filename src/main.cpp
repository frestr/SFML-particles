#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "particlemanager.h"
#include "uimanager.h"

/*
TODO:

- Find out why the simulation seems to go in fast motion when the
  mouse button is pressed down (i.e. the particles are changing their velocity)

- Add some color effect

- Add the ability to zoom

- Maybe add some other effect than following the mouse pointer

*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Particle test");
    window.setFramerateLimit(60);

    int particleNum = 500000;

    ParticleManager particleManager(particleNum, window.getSize());
    sf::Clock clock;

    UIManager ui(window.getView());

    sf::Clock fpsTimer;

    sf::View view;
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
    window.setView(view);

    while (window.isOpen())
    {
        double dt = clock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asMilliseconds() > 100)
        {
            fpsTimer.restart();
            int fps = (1.0 / dt > 60) ? 60 : (1.0 / dt);
            ui.setFps(fps);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseWheelMoved)
            {
                view.zoom(2.0f);
                window.setView(view);
            }
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            particleManager.reset(particleNum, window.getSize());
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            particleManager.moveParticlesTowardsMouse(dt, sf::Mouse::getPosition(window));
        }
        else
        {
            particleManager.moveParticlesTowardsMouse(dt, sf::Vector2i(-1, -1));
        }

        //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //mousePos.x *= (view.getSize().x / 2) / window.getSize().x;
        //mousePos.y *= (view.getSize().y / 2) / window.getSize().y;


        window.clear();

        particleManager.drawParticles(window);
        ui.drawUI(window);

        window.display();
    }

    return 0;
}
