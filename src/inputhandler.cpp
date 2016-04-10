#include "inputhandler.h"
#include <algorithm>
#include <SFML/Config.hpp>

InputHandler::InputHandler() : closeWindow(false),
                               clickPos(sf::Vector2f(-1, -1)),
                               leftClick(false) {}

void InputHandler::readInput(sf::RenderWindow& window)
{
    clickPos = sf::Vector2f(-1, -1);
    scrollDelta = 0;
    sf::Event event;
    sf::Vector2f worldPos;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                closeWindow = true;
                break;
            case sf::Event::KeyPressed:
                if (isKeyActive(event.key.code))
                    untoggleKey(event.key.code);
                else
                    activeKeys.push_back(event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                clickPos = sf::Vector2f(worldPos.x, worldPos.y);
                leftClick = event.mouseButton.button == sf::Mouse::Left;
                break;
#if SFML_VERSION_MINOR < 3
            case sf::Event::MouseWheelMoved:
                scrollDelta = event.mouseWheel.delta;
                break;
#else
            case sf::Event::MouseWheelScrolled:
                scrollDelta = event.mouseWheelScroll.delta;
                break;
#endif
            default:
                break;
        }
    }
}

bool InputHandler::isKeyActive(sf::Keyboard::Key key)
{
    // Returns true if key is found in activeKeys
    return std::find(activeKeys.begin(), activeKeys.end(), key) != activeKeys.end();
}

void InputHandler::untoggleKey(sf::Keyboard::Key key)
{
    activeKeys.erase(std::remove(activeKeys.begin(), activeKeys.end(), key), 
            activeKeys.end());
}

bool InputHandler::shouldCloseWindow()
{
    return closeWindow;
}

bool InputHandler::mouseClicked(char button)
{
    bool correctButton = true;
    if (button == 'l' || button == 'r')
        correctButton = (button == 'l' ? leftClick : !leftClick);

    return clickPos.x != -1 && clickPos.y != -1 && correctButton;
}

sf::Vector2f InputHandler::getClickPos()
{
    return clickPos;
}

int InputHandler::mouseScrolled()
{
    return scrollDelta;
}

sf::Vector2i InputHandler::getGlobalMousePos(sf::RenderWindow& window)
{
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return sf::Vector2i(worldPos.x, worldPos.y);
}
