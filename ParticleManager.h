#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "Particle.h"

class ParticleManager
{
private:
	std::vector<Particle> particles;
	sf::VertexArray particleVertices;

	const int threadNum;
	std::thread threads[15];

	void moveParticleBatch(int offset, int batchSize, double dt, sf::Vector2i mousePos);

public:
	ParticleManager(int particleNum, sf::Vector2u windowSize);
	void reset(int particleNum, sf::Vector2u windowSize);

	void drawParticles(sf::RenderWindow &window);
	void moveParticlesTowardsMouse(double dt, sf::Vector2i mousePos);
};

#endif
