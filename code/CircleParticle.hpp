#pragma once

#include <iostream>
#include "Particle.hpp"

namespace rigid
{
	class CircleParticle : Particle
	{
	public:

		CircleParticle(sf::Vector2f startingPosition) : Particle{ startingPosition }
		{
		}

		virtual void Update(float deltaTime) override
		{
			position.y += 1.f;
		}

		virtual void Render(sf::RenderWindow & window) override
		{
			sf::CircleShape a{ 3 };
			a.setPosition(position.x, position.y);
			window.draw(a);
		}
	};
}