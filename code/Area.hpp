#pragma once

#include <SFML/Graphics.hpp>

namespace rigid
{
	class Area
	{
	public:
		virtual sf::Vector2f get_random_position() = 0;
	};
}