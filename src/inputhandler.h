#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class InputHandler
{
public:
    InputHandler();

    void readInput(sf::RenderWindow& window);
    bool isKeyActive(sf::Keyboard::Key key);
    void untoggleKey(sf::Keyboard::Key key);
    bool shouldCloseWindow();
    bool mouseClicked(char button=' ');
    sf::Vector2f getClickPos();
    int mouseScrolled();
    sf::Vector2i getGlobalMousePos(sf::RenderWindow& window);

private:
    std::vector<sf::Keyboard::Key> activeKeys; // i.e. toggled keys
    bool closeWindow;
    sf::Vector2f clickPos;
    bool leftClick;
    int scrollDelta;
};
