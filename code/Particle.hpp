#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace rigid
{
	class Particle
	{
	public:

		Particle(sf::Vector2f _position, sf::Vector2f _direction, sf::Color _color) 
			: position(_position), direction(_direction), color(_color) {}

		~Particle()
		{
			//delete shape;
		}

		virtual void Update(float deltaTime) = 0;
		virtual void Render(sf::RenderWindow & window) = 0;
		
		sf::Vector2f	position;
		sf::Vector2f	direction;
		sf::Color		color;
		float			speed;
		sf::Shape		* shape;
	};
}