#pragma once

#include "Area.hpp"

namespace rigid
{
	class RectangleArea : Area
	{
		float left_x;
		float bottom_y;
		float width;
		float height;

	public:

		RectangleArea
		(
			float given_left_x,
			float given_bottom_y,
			float given_width,
			float given_height
		)
		{
			left_x = given_left_x;
			bottom_y = given_bottom_y;
			width = given_width;
			height = given_height;
		}

		virtual sf::Vector2f get_random_position() override
		{
			return sf::Vector2f
			{
				left_x + float(rand() % int(width)),
				bottom_y + float(rand() % int(height)),
			};
		}
	};
}