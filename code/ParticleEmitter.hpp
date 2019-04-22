/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::ParticleEmitter
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// System
#include <vector>
#include <ctime>
// Project
#include "Area.hpp"
#include "CircleParticle.hpp"

namespace rigid
{
	/// Templatized Particle Emitter that stores and renders Particles 
	template< class PARTICLE >
	class ParticleEmitter
	{

	public:

		/// Sets up area and particle count
		ParticleEmitter(int particles_per_second, Area * area) : particlesCount(particles_per_second), currentArea(area)
		{
			// Seed randomness with time
			srand((unsigned int)time(NULL));
		}

		~ParticleEmitter()
		{
			delete currentArea;
		}

		/// Creates every particle with given properties
		void Start()
		{
			// Creates particles with given particle count 
			for (int i = 0; i < particlesCount; i++)
			{
				particles.push_back(PARTICLE
				{ 
					// Random position on given area
					currentArea->GetRandomPosition(), 
					// Random velocity
					sf::Vector2f(RandomFloat(particleVelocity.x, particleVelocityInterval.x), RandomFloat(particleVelocity.y, particleVelocityInterval.y)),
					// Random color
					LerpColor(firstColor, secondColor, RandomFloat(0, 1)),
					// Random lifetime
					RandomFloat(lifetime, lifetimeInterval),
					// Random size
					RandomFloat(sizeInterval.x, sizeInterval.y),
				});
			}
		}

		/// Updates every particle and reset those who died
		void Update(float t)
		{
			for (PARTICLE & particle : particles)
			{
				if (!particle.isDead)
					particle.Update(t);
				else
				{
					particle.position = currentArea->GetRandomPosition();
					particle.direction = sf::Vector2f(RandomFloat(particleVelocity.x, particleVelocityInterval.x), RandomFloat(particleVelocity.y, particleVelocityInterval.y));
					particle.Reset();
				}
			}
		}

		/// Only Renders particles when emitting
		void Render(sf::RenderWindow & ctx)
		{
			if (!emit) return;

			for (PARTICLE & particle : particles)
				particle.Render(ctx);
		}

		/// Area in which particles are spawned
		Area                  *	currentArea;

		/// Particles list
		std::vector< PARTICLE > particles;

		/// Particles count (to create)
		int						particlesCount;

		/// Current particle velocity
		sf::Vector2f			particleVelocity;

		/// Interval added randomly to velocity
		sf::Vector2f			particleVelocityInterval;

		/// Random size between interval
		sf::Vector2f			sizeInterval;

		/// First color to lerp
		sf::Color				firstColor;

		/// Second color to lerp
		sf::Color				secondColor;

		/// Particle lifetime
		float					lifetime;

		/// Interval added randomly to lifetime
		float					lifetimeInterval;

		/// If emitter is currently emitting particles 
		bool					emit = true;
		

	private:

		/// Returns lerped color with given colors and time (0-1)
		sf::Color LerpColor(sf::Color firstColor, sf::Color secondColor, float time)
		{
			return sf::Color
			{ 
				(sf::Uint8)((float)firstColor.r + std::floorf(static_cast<float>(secondColor.r - firstColor.r) * time)),
				(sf::Uint8)((float)firstColor.g + std::floorf(static_cast<float>(secondColor.g - firstColor.g) * time)),
				(sf::Uint8)((float)firstColor.b + std::floorf(static_cast<float>(secondColor.b - firstColor.b) * time))
			};
		}

		/// Returns random float between both given floats
		float RandomFloat(float a, float b) 
		{
			float random = ((float)rand()) / (float)RAND_MAX;
			float diff = b - a;
			float r = random * diff;
			return a + r;
		}

	};

	typedef ParticleEmitter< CircleParticle > CircleParticleEmitter;
	
}