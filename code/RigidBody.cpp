#include "RigidBody.hpp"

#include <iostream>

namespace rigid
{
	RigidBody::RigidBody(b2World & physicsWorld, b2Vec2 position, b2BodyType bodyType, b2Shape * _shape, sf::Color color, float density)
	{
		//Set body properties and create
		body_definition.type = bodyType;
		body_definition.position.Set(position.x, position.y);          
		body = physicsWorld.CreateBody(&body_definition);
		
		// Set fixture properties and create
		body_fixture.shape = _shape;
		body_fixture.density = density;
		body_fixture.restitution = 0.75f;
		body_fixture.friction = 0.50f;
		body->CreateFixture(&body_fixture);

		// Check type
		switch (_shape->GetType())
		{
			case b2Shape::e_circle:
			{
				// Create visual Shape
				shape = std::make_shared<CircleShape>(CircleShape{});
				// Cast RigidShape
				rigidShape = dynamic_cast<b2CircleShape * >(body->GetFixtureList()->GetShape());
				// Cache casted visual Shape 
				std::shared_ptr<CircleShape> circleShapeRef = std::dynamic_pointer_cast<CircleShape>(shape);

				// Set properties
				circleShapeRef->setRadius(rigidShape->m_radius);

				break;
			}

			case b2Shape::e_polygon:
			{
				// Create visual Shape
				shape = std::make_shared<ConvexShape>(ConvexShape{});
				// Cast RigidShape
				rigidShape = dynamic_cast<b2PolygonShape * >(body->GetFixtureList()->GetShape());
				// Cache casted visual Shape 
				std::shared_ptr<ConvexShape> polygonShapeRef = std::dynamic_pointer_cast<ConvexShape>(shape);
				// Cache casted rigid Shape
				b2PolygonShape * polygonRigidShape = dynamic_cast<b2PolygonShape * >(rigidShape);

				// Set properties
				polygonShapeRef->setPointCount(polygonRigidShape->GetVertexCount());

				break;
			}
		default:
			break;
		}

		// Set shape properties
		shape->setFillColor(color);
	}

	void RigidBody::render(RenderWindow & window)
	{
		switch (rigidShape->GetType())
		{
			case b2Shape::e_circle:
			{
				// Cast visual Shape
				std::shared_ptr<CircleShape> circleShapeRef = std::dynamic_pointer_cast<CircleShape>(shape);
				// Cast rigid Shape
				b2CircleShape * circleRigidShape = dynamic_cast<b2CircleShape * >(rigidShape);
				// Updating Position
				circleShapeRef->setPosition(box2d_position_to_sfml_position(b2Mul(body->GetTransform(), circleRigidShape->m_p), (float)window.getSize().y) - Vector2f(circleRigidShape->m_radius, circleRigidShape->m_radius));
				// Drawing shape
				window.draw(*circleShapeRef);
				break;
			}
			case b2Shape::e_polygon:
			{
				// Cast visual Shape
				std::shared_ptr<ConvexShape> polygonShapeRef = std::dynamic_pointer_cast<ConvexShape>(shape);
				// Cast rigid Shape
				b2PolygonShape * polygonRigidShape = dynamic_cast<b2PolygonShape * >(rigidShape);
				// Updating Position
				int number_of_vertices = polygonRigidShape->GetVertexCount();
			
				for (int index = 0; index < number_of_vertices; index++)
					polygonShapeRef->setPoint ( index, box2d_position_to_sfml_position(b2Mul(body->GetTransform(), polygonRigidShape->GetVertex(index)), (float)window.getSize().y));
				// Drawing shape
				window.draw(*polygonShapeRef);
				break;
			}
			case b2Shape::e_edge:
			{

				//NOT DONE _ USE POLYGON
				break;
			}
			default:
				break;
		}

		
	}
}

