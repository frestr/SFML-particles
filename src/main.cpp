#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "particlemanager.h"
#include "uimanager.h"
#include "inputhandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Particle test");
    window.setFramerateLimit(60);

    int particleNum = 500000;

    sf::Clock clock;
    sf::Clock fpsTimer;
    int scrollDelta;

    ParticleManager particleManager(particleNum, window.getSize());
    UIManager ui(window.getView());
    InputHandler input;

    sf::View view;
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
    window.setView(view);

    while (window.isOpen())
    {
        input.readInput(window);
        if (input.shouldCloseWindow())
        {
            window.close();
            break;
        }

        int scrollDelta = input.mouseScrolled();
        if (scrollDelta > 0 && view.getSize().y > 100)
            view.zoom(0.75);
        else if (scrollDelta < 0 && view.getSize().y < 16000)
            view.zoom(1.0/0.75);
        window.setView(view);

        double dt = clock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asMilliseconds() > 100)
        {
            fpsTimer.restart();
            int fps = (1.0 / dt > 60) ? 60 : (1.0 / dt);
            ui.setFps(fps);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        if (input.isKeyActive(sf::Keyboard::Key::R))
        {
            particleManager.reset(particleNum, window.getSize());
            input.untoggleKey(sf::Keyboard::Key::R);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = input.getGlobalMousePos(window);
            particleManager.moveParticlesTowardsMouse(dt, mousePos);
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
