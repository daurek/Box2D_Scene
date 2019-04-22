/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Car
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Project
#include "Car.hpp"
#include "RectangleArea.hpp"

namespace rigid
{
	void Car::Start()
	{
		// Cache water RigidBody
		water = rigidBodies["water"];
		// Cache chassis RigidBody
		chassis = rigidBodies["chassis"];

		// Cache joints
		wheel1Joint = static_cast<b2RevoluteJoint *>(joints["wheel1Joint"]->joint);
		wheel2Joint = static_cast<b2RevoluteJoint *>(joints["wheel2Joint"]->joint);
		closerJoint = static_cast<b2RevoluteJoint *>(joints["closerJoint"]->joint);

		// Set tag for collision and invisible shape
		water->tag = "waterJet";
		water->isVisible = false;

		// Water Particle Setup
		waterParticles = std::make_shared<CircleParticleEmitter>(50, new RectangleArea{ sf::Vector2f{ 230, 740.f }, sf::Vector2f{ 50, 10 } });
		waterParticles->particleVelocity = sf::Vector2f{ 0.1f, 0.f };
		waterParticles->particleVelocityInterval = sf::Vector2f{ 0.5f, 0.2f };
		waterParticles->lifetime = 1;
		waterParticles->lifetimeInterval = 0.5f;
		waterParticles->sizeInterval = { 2, 4 };
		waterParticles->firstColor = sf::Color{ 0, 119, 190 };
		waterParticles->secondColor = sf::Color{ 0, 24, 190 };
		waterParticles->emit = false;
		waterParticles->Start();
	}

	void Car::Update(float deltaTime)
	{
		// Input check and driving

		// Left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			wheel1Joint->SetMotorSpeed(2000);
			wheel2Joint->SetMotorSpeed(2000);
		}
		// Right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			wheel1Joint->SetMotorSpeed(-2000);
			wheel2Joint->SetMotorSpeed(-2000);
		}
		else
		{
			wheel1Joint->SetMotorSpeed(0);
			wheel2Joint->SetMotorSpeed(0);
		}

		// Closing and opening the closer
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			closerJoint->SetMotorSpeed(-50000);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			closerJoint->SetMotorSpeed(50000);
		}

		// Switching on and off the water thrower
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			isWaterEnabled = true;
			waterParticles->emit = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			isWaterEnabled = false;
			waterParticles->emit = false;
		}

		// Brakes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			chassis->body->SetLinearVelocity(b2Vec2(chassis->body->GetLinearVelocity().x * 0.9f, chassis->body->GetLinearVelocity().y * 0.9f));
		}
		
		waterParticles->Update(deltaTime);
	}

	void Car::Render(sf::RenderWindow & window)
	{
		// Render car
		GameObject::Render(window);
		// Update particles position with water thrower and render it
		waterParticles->currentArea->SetPosition(sf::Vector2f(-35,-10) + box2d_position_to_sfml_position(rigidBodies["water"]->body->GetPosition(), (float)window.getSize().y));
		waterParticles->Render(window);
	}

	void Car::Reset()
	{
		// Reset every rigidbody
		for (auto & rigidBody : rigidBodies)
			rigidBody.second->Reset();

		// Reset joints speed
		wheel1Joint->SetMotorSpeed(0);
		wheel2Joint->SetMotorSpeed(0);
		closerJoint->SetMotorSpeed(0);

		// Stop emiting particles 
		waterParticles->emit = false;
		isWaterEnabled = false;
	}

}


