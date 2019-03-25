#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace rigid
{
	class Particle
	{
	public:

		Particle( sf::Vector2f startingPosition ) : position(startingPosition)
		{

		}


		virtual void Update(float deltaTime) = 0;
		virtual void Render(sf::RenderWindow & window) = 0;
		
		sf::Vector2f position;
	};
}