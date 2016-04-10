#include "uimanager.h"
#include <iostream>

UIManager::UIManager(sf::View originalView)
{
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "In UIManager::UIManager(): Unable to load font arial.ttf" << std::endl;
        return;
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(25);
    fpsText.setPosition(10, 5);

    view = originalView;
}

void UIManager::setFps(int fps)
{
    fpsText.setString("fps: " + std::to_string(fps));
}

void UIManager::drawUI(sf::RenderWindow& window)
{
    sf::View currView = window.getView();

    window.setView(view);

    window.draw(fpsText);

    window.setView(currView);
}
