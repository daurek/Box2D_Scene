#pragma once

#include "Area.hpp"

namespace rigid
{
	class RectangleArea : public Area
	{
		sf::Vector2f position;
		sf::Vector2f dimension;

	public:

		RectangleArea(sf::Vector2f _position, sf::Vector2f _dimension)
			: position(_position), dimension(_dimension) {}

		virtual sf::Vector2f get_random_position() override
		{
			return sf::Vector2f
			{
				position.x + float(rand() % int(dimension.x)),
				position.y + float(rand() % int(dimension.y)),
			};
		}
	};
}