/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Particle
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace rigid
{
	/// Base Particle class that stores common properties
	class Particle
	{
	public:

		/// Creates Particle with the given properties
		Particle(sf::Vector2f _position, sf::Vector2f _direction, sf::Color _color, float lifetime, float _size) 
			: position(_position), direction(_direction), color(_color) , maxTime (lifetime), size(_size) {}

		/// Base Update (Logic)
		virtual void Update(float deltaTime) = 0;

		/// Base Render with given window
		virtual void Render(sf::RenderWindow & window) = 0;

		/// Reset timer
		void		 Reset()
		{
			isDead = false;
			currentTime = 0;
		}
		
		/// Shape Reference
		sf::Shape		* shape;
		/// Current Position
		sf::Vector2f	position;
		/// Current Direction
		sf::Vector2f	direction;
		/// Current Color
		sf::Color		color;
		/// If Particle has died
		bool			isDead = false;
		/// Current Speed
		float			speed;
		/// Current size
		float			size;
		/// Max Time alive
		float			maxTime;
		/// Time alive
		float			currentTime = 0;
	};
}