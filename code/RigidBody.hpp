#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace rigid
{
	using sf::CircleShape;
	using sf::ConvexShape;
	using sf::Shape;
	using sf::RenderWindow;
	using sf::Vector2f;

	class RigidBody
	{

	public:

		RigidBody(){};
		RigidBody(std::shared_ptr< b2World > physicsWorld, b2Vec2 position, b2BodyType bodyType, b2Shape * _shape, sf::Color color = sf::Color::Magenta, float density = 1);

		~RigidBody(){}

		b2BodyDef body_definition;
		b2FixtureDef body_fixture;

		b2Body * body;
		b2Shape * rigidShape;
		std::shared_ptr<Shape> shape;

		void render(RenderWindow & window);

		inline static Vector2f box2d_position_to_sfml_position(const b2Vec2 & box2d_position, float window_height)
		{
			return Vector2f(box2d_position.x, window_height - box2d_position.y);
		}

	};

}