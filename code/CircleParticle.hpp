/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::CircleParticle
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "Particle.hpp"

namespace rigid
{
	class CircleParticle : public Particle
	{
	public:

		CircleParticle(sf::Vector2f _position, sf::Vector2f _direction, sf::Color _color, float _lifetime, float _size) :
			Particle{ _position, _direction, _color, _lifetime, _size }
		{
			// Create circular shape with given size and color
			shape = new sf::CircleShape(_size);
			shape->setFillColor(color);
		}

		virtual void Update(float deltaTime) override
		{
			// Update position with current direction
			position += direction;
			shape->setPosition(position.x, position.y);
			// Add lifetime until it dies
			currentTime += deltaTime;
			if (currentTime >= maxTime)
				isDead = true;
		}

		virtual void Render(sf::RenderWindow & window) override
		{
			window.draw(*shape);
		}
	};
}