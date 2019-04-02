#pragma once

#include <iostream>
#include "Particle.hpp"

namespace rigid
{
	class CircleParticle : public Particle
	{
	public:

		CircleParticle(sf::Vector2f _position, sf::Vector2f _direction, sf::Color _color) : 
			Particle{ _position, _direction, _color }
		{
			shape = new sf::CircleShape(3);
			shape->setFillColor(color);
		}

		virtual void Update(float deltaTime) override
		{
			position += direction;
			shape->setPosition(position.x, position.y);
		}

		virtual void Render(sf::RenderWindow & window) override
		{
			window.draw(*shape);
		}
	};
}