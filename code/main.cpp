// System
#include <memory>
#include <vector>

// Libraries
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// Project
#include "GameObject.hpp"
#include "Scene.hpp"

using namespace sf;
using namespace std;

namespace rigid
{
	// std::vector <RigidBody> rigidBodyList;

  //  shared_ptr< b2World > create_physics_world (float world_width, float world_height)
  //  {
  //      // Se crea el mundo físico:
  //      //shared_ptr< b2World > physics_world(new b2World(b2Vec2(0, -100.f)));

		////b2CircleShape leftWheelShape;
		////leftWheelShape.m_radius = 35;
		//////b2CircleShape rightWheelShape;
		//////rightWheelShape.m_radius = 25;
		////b2PolygonShape boxShape;
		////boxShape.SetAsBox (100.f, 25.f);

		////b2PolygonShape groundShape;
		////groundShape.SetAsBox(800, 5.f);
		//////b2EdgeShape body_shape;
		//////body_shape.Set({ 0.f, 0.f }, { world_width, 0.f });

		////RigidBody leftWheel		{ physics_world, {200,300}, b2BodyType::b2_dynamicBody, &leftWheelShape, sf::Color::Yellow, 0.1f };
		//////RigidBody rightWheel	{ physics_world, {300,100}, b2BodyType::b2_dynamicBody, &rightWheelShape, 0.1f };
		////RigidBody chassis		{ physics_world, {250,100}, b2BodyType::b2_dynamicBody, &boxShape, sf::Color::Blue, 50.f };
		//////Joint leftJoint			{ physics_world, leftWheel, chassis, b2JointType::e_wheelJoint };
		//////Joint rightJoint		{ physics_world, rightWheel, chassis, b2JointType::e_wheelJoint };*/

		////RigidBody ground		{ physics_world, {0,5}, b2BodyType::b2_staticBody, &groundShape,  sf::Color::Green, 100.f };
		////chassis.body->ApplyForce({ 1000000000,0 },chassis.body->GetPosition(), true);

		////rigidBodyList.push_back(leftWheel);
		//////rigidBodyList.push_back(rightWheel);
		////rigidBodyList.push_back(chassis);
		////rigidBodyList.push_back(ground);

  //      //return physics_world;
  //  }

}

using namespace rigid;

int main ()
{
    RenderWindow window(VideoMode(1024, 800), "Box2D Rigid Bodies", Style::Titlebar | Style::Close, ContextSettings(32));
    window.setVerticalSyncEnabled (true);

	Scene scene{ "../../assets/scene.xml" };

    bool running = true;

    Clock timer;
    float deltaTime = 0.017f;          // ~60 fps

    do
    {
        timer.restart ();

        // Process window events:
        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Update:
		scene.Update(deltaTime);
        // Clear Window
		window.clear({ 100, 150, 240, 255 });
		// Render Scene and Display Window
		scene.Render (window);
        window.display ();

		deltaTime = (deltaTime + timer.getElapsedTime ().asSeconds ()) * 0.5f;
    }
    while (running);

    return EXIT_SUCCESS;
}
