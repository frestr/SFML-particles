#include "ParticleManager.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include <random>

ParticleManager::ParticleManager(int particleNum, sf::Vector2u windowSize) : threadNum(15)
{
	reset(particleNum, windowSize);
}

void ParticleManager::reset(int particleNum, sf::Vector2u windowSize)
{
	particles.clear();

	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<> disX(0, windowSize.x);
	std::uniform_int_distribution<> disY(0, windowSize.y);

	particleVertices.setPrimitiveType(sf::Points);
	particleVertices.resize(particleNum);

	for (int i = 0; i < particleNum; ++i)
	{
		Particle particle(&particleVertices[i], sf::Vector2f(disX(gen), disY(gen)));
		particles.push_back(particle);
	}
}

void ParticleManager::drawParticles(sf::RenderWindow &window)
{
	window.draw(particleVertices);
}

void ParticleManager::moveParticlesTowardsMouse(double dt, sf::Vector2i mousePos)
{
	int batchSize = particles.size() / threadNum;

	for (int i = 0; i < threadNum; ++i)
	{
		threads[i] = std::thread(&ParticleManager::moveParticleBatch, this, i, batchSize, dt, mousePos);
		//threads[i].detach();
	}
	
	for (int i = 0; i < threadNum; ++i)
	{
		threads[i].join();
	}
}

void ParticleManager::moveParticleBatch(int offset, int batchSize, double dt, sf::Vector2i mousePos)
{
	for (auto it = particles.begin() + offset * batchSize; 
		it != ((offset != threadNum - 1) ? (particles.begin() + offset * batchSize + batchSize) : (particles.end())); ++it)
	{
		if (mousePos != sf::Vector2i(-1, -1))
		{
			sf::Vector2f currPos = (*it).getPtr()[0].position;
		
			double distX = mousePos.x - currPos.x;
			double distY = mousePos.y - currPos.y;
			double dist = sqrt(distX*distX + distY*distY);

			if (dist == 0)
				dist = 1;

			double speed = 10;

			// Those speeds make the simulation quite different
			//double speed = sqrt(dist) * 0.5;
			//double speed = (1.0 / sqrt(dist)) * 50;

			double normDistX = distX / dist;
			double normDistY = distY / dist;

			(*it).changeSpeed(sf::Vector2f(normDistX * speed, normDistY * speed));
		}
		(*it).updatePos(dt);
	}
}
