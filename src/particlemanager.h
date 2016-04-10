#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "particle.h"

class ParticleManager
{
private:
    std::vector<Particle> particles;
    sf::VertexArray particleVertices;

    int threadNum;
    std::vector<std::thread> threads;

    void moveParticleBatch(int offset, int batchSize, double dt, sf::Vector2i mousePos);

public:
    ParticleManager(int particleNum, sf::Vector2u windowSize);
    ~ParticleManager();
    void reset(int particleNum, sf::Vector2u windowSize);

    void drawParticles(sf::RenderWindow &window);
    void moveParticlesTowardsMouse(double dt, sf::Vector2i mousePos);
};
