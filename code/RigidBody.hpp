/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::RigidBody
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Libraries
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace rigid
{
	using sf::CircleShape;
	using sf::ConvexShape;
	using sf::Shape;
	using sf::Vector2f;

	/// Translates Box2D position to SFML position with the given window height
	inline static Vector2f box2d_position_to_sfml_position(const b2Vec2 & box2d_position, float window_height)
	{
		return Vector2f(box2d_position.x, window_height - box2d_position.y);
	}

	/// Visual (SFML) and Physics (Box2D) container class
	class RigidBody
	{

	public:

		RigidBody(){};
		
		/// Creates a RigidBody with the given world and properties
		RigidBody(b2World & physicsWorld, b2Vec2 position, b2BodyType bodyType, b2Shape * _shape, sf::Color color = sf::Color::Magenta, float density = 1, float gravityScale = 1, float friction = 1, float restitution = 1, bool isSensor = false);

		/// Renders the Rigidbody's Shape on the given window
		void Render(sf::RenderWindow & window);

		/// Reverts some properties to their initial state
		void Reset();

		/// Body reference
		b2Body						  * body;

		/// Physics Shape Reference
		b2Shape						  *	rigidShape;

		/// Visual Shape Reference
		std::shared_ptr<Shape>			shape;

		/// Tag (Used for Collision Detection)
		std::string						tag = "";

		/// Only Render Visible Objects
		bool							isVisible = true;

	private:

		/// Caching initial position
		b2Vec2							startingPosition;
	};

}