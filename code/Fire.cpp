/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Fire
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Fire.hpp"

// Project
#include "RectangleArea.hpp"
#include "Car.hpp"
#include "Scene.hpp"

namespace rigid
{
	void Fire::Start()
	{
		// Cache fire RigidBody
		fire = rigidBodies["fire"];

		// Fire Particle Setup
		fireParticles = std::make_shared<CircleParticleEmitter>(50, new RectangleArea{ sf::Vector2f{ 500.f, 720.f }, sf::Vector2f{ 50, 60 } });
		fireParticles->particleVelocity = sf::Vector2f{ 0.f, -0.05f };
		fireParticles->particleVelocityInterval = sf::Vector2f{ 0.f, -0.3f };
		fireParticles->lifetime = 1;
		fireParticles->lifetimeInterval = 0.5f;
		fireParticles->sizeInterval = { 2, 4 };
		fireParticles->firstColor = sf::Color{ 255, 128, 0 };
		fireParticles->secondColor = sf::Color{ 255, 0, 0 };
		fireParticles->Start();
	}

	void Fire::Update(float deltaTime)
	{
		fireParticles->Update(deltaTime);

		// If fire has finished then stop blocking the way
		if (isFinished)
			fire->body->SetActive(false);
	}

	void Fire::Render(sf::RenderWindow & window)
	{
		// Only Render fire particles
		fireParticles->Render(window);
	}

	void Fire::Reset()
	{
		// Reset fire to initial state
		isFinished = false;
		fire->body->SetActive(true);
		fireParticles->emit = true;
	}

	void Fire::StartContact(GameObject * contactBody)
	{
		// Check if collision has been with the water rigidbody and it's enabled
		if (contactBody->GetRigidBody("water") && static_cast<Car *>(contactBody)->isWaterEnabled)
		{
			// Disable particles
			fireParticles->emit = false;
			isFinished = true;
		}
		else
		{
			// Otherwise reset the scene
			scene->Reset();
		}
	}

}


