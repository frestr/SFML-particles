#include "Particle.h"

Particle::Particle(sf::Vertex* point, sf::Vector2f pos)
{
	pointPtr = point;

	pointPtr->position = sf::Vector2f(pos.x, pos.y);
	pointPtr->color = sf::Color(255, 255, 0);

	speed.x = 0;
	speed.y = 0;
}

void Particle::changeSpeed(sf::Vector2f deltaSpeed)
{
	speed.x += deltaSpeed.x ;
	speed.y += deltaSpeed.y;

	double absSpeed = sqrt(speed.x*speed.x + speed.y*speed.y);
	double maxSpeed = 750;

	if (absSpeed > maxSpeed)
		absSpeed = maxSpeed;

	pointPtr->color = sf::Color(255, 255 - 255 * (absSpeed / maxSpeed), 0);
}

void Particle::updatePos(double dt)
{
	sf::Vector2f currPos = pointPtr->position;
	pointPtr->position = sf::Vector2f(currPos.x + speed.x * dt, currPos.y + speed.y * dt);
}

sf::Vertex* Particle::getPtr()
{
	return pointPtr;
}
