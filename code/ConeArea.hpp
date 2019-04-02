#pragma once

#include "Area.hpp"

namespace rigid
{
	class ConeArea : public Area
	{
		sf::Vector2f position;
		float firstAngle;
		float secondAngle;
		float height;

	public:

		ConeArea ( sf::Vector2f _position, float _firstAngle, float _secondAngle) 
			: position (_position), firstAngle(_firstAngle), secondAngle(_secondAngle) {}


		virtual sf::Vector2f get_random_position() override
		{
			return position;
		}

	/*	virtual sf::Vector2f get_random_angle() override
		{
			float random = (float)rand() / (float)RAND_MAX  * secondAngle + firstAngle;
			return sf::Vector2f(std::cos(random), std::sin(random));
		}*/
	};
}