#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
private:
	sf::Vertex* pointPtr;
	sf::Vector2f speed;
	sf::Vector2f size;

public:
	Particle(sf::Vertex* point, sf::Vector2f pos);
	void changeSpeed(sf::Vector2f deltaSpeed);
	sf::Vertex* getPtr();

	void updatePos(double dt);
};
