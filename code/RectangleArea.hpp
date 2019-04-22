/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::RectangleArea
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "Area.hpp"

namespace rigid
{
	/// Rectangular Area with dimension
	class RectangleArea : public Area
	{

	public:

		/// Creates Rectangular Area on given position with given dimension
		RectangleArea(sf::Vector2f _position, sf::Vector2f _dimension) : dimension(_dimension) 
		{
			position = _position;
		}

		/// Returns random position inside rectangular Area
		virtual sf::Vector2f GetRandomPosition() override
		{
			return sf::Vector2f
			{
				position.x + float(rand() % int(dimension.x)),
				position.y + float(rand() % int(dimension.y)),
			};
		}

	private:

		/// Area Dimension
		sf::Vector2f dimension;

	};
}