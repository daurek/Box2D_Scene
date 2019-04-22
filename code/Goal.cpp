/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Goal
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Project
#include "Goal.hpp"
#include "Car.hpp"
#include "RectangleArea.hpp"

namespace rigid
{
	void Goal::Start()
	{
		// Win Particle Setup
		winParticles = std::make_shared<CircleParticleEmitter>(300, new RectangleArea{ sf::Vector2f{ 0.f, 400.f }, sf::Vector2f{ 200, 100 } });
		winParticles->particleVelocity				= sf::Vector2f{ 0.f, -0.3f };
		winParticles->particleVelocityInterval		= sf::Vector2f{ 0.f, -0.7f };
		winParticles->lifetime						= 1;
		winParticles->lifetimeInterval				= 0.5f;
		winParticles->sizeInterval					= { 1, 2 };
		winParticles->firstColor					= sf::Color{ 255, 175, 0 };
		winParticles->secondColor					= sf::Color{ 255, 255, 160 };
		winParticles->emit							= false;
		winParticles->Start();
	}

	void Goal::Update(float deltaTime)
	{
		// If the player has finished then wait for some time and enable the win particles :)
		if (hasFinished && !winParticles->emit)
		{
			currentTime += deltaTime;

			if (currentTime >= maxTime)
				winParticles->emit = true;
		}

		// Always update the particles
		winParticles->Update(deltaTime);
	}

	void Goal::Render(sf::RenderWindow & window)
	{
		// Render both the shape and the particles
		GameObject::Render(window);
		winParticles->Render(window);
	}

	void Goal::Reset()
	{
		// Reset to the initial state
		hasFinished = false;
		currentTime = 0;
		winParticles->emit = false;
	}

	void Goal::StartContact(GameObject * contactBody)
	{
		// If the car is in contact then the player has won
		Car * car = dynamic_cast<Car *>(contactBody);
		if (car)
			hasFinished = true;
	}

}


