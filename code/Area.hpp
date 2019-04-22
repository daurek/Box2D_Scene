/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Area
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

namespace rigid
{
	/// Base Area class with basic properties 
	class Area
	{

	public:
		
		/// Sets given position
		void SetPosition(const sf::Vector2f & _position)
		{
			position = _position;
		}

		/// Returns Random Position in Area
		virtual sf::Vector2f GetRandomPosition()	= 0;

	protected:

		/// Area Position
		sf::Vector2f position;
	};
}