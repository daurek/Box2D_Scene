#pragma once


#include <ctime>

#include <vector>
#include "Pool.hpp"
#include "Area.hpp"
#include "CircleParticle.hpp"

namespace rigid
{
	template< class PARTICLE > //, class AREA >
	class ParticleEmitter
	{
	public:

		enum State
		{
			UNINITIALIZED,
			EVOLVING,
			DESTROYED
		};

		//Pool< Particle > particles;
		std::vector<PARTICLE > particles;
		int particles_per_second;

		State state = UNINITIALIZED;


		ParticleEmitter(int particles_per_second, Area * area, sf::Vector2f velocity, sf::Vector2f velocityInterval) : particles_per_second(particles_per_second)
		{
			state = EVOLVING;
			srand(time(NULL));

			for (size_t i = 0; i < particles_per_second; i++)
			{
				particles.push_back(PARTICLE{ area->get_random_position(), velocity, LerpColor(sf::Color::Red, sf::Color::Yellow, 0) });
			}
		}

		void Update(float t)
		{
			//generate_particles(t);

			for (auto & particle : particles)
			{
				particle.Update(t);
			}
			/*for(Pool< Particle >::Iterator i = particles.begin(); i != particles.end(); ++i)
				particle.update(t);*/
		}

		void Render(sf::RenderWindow & ctx)
		{
			for (auto & particle : particles)
			{
				particle.Render(ctx);
			}
			/*for (Pool< Particle >::Iterator i = particles.begin(); i != particles.end(); ++i)
				particle.render(ctx);*/
		}

	private:

		void generate_particles(float t)
		{
			// cuando ha transcurrido cierto tiempo, generar
			// cierto número de partículas
			
		}

		sf::Color LerpColor(sf::Color firstColor, sf::Color secondColor, float time)
		{
			return sf::Color
			{ 
				(sf::Uint8)((float)firstColor.r + std::floorf(static_cast<float>(secondColor.r - firstColor.r) * time)),
				(sf::Uint8)((float)firstColor.g + std::floorf(static_cast<float>(secondColor.g - firstColor.g) * time)),
				(sf::Uint8)((float)firstColor.b + std::floorf(static_cast<float>(secondColor.b - firstColor.b) * time))
			};
		}

	};

	typedef ParticleEmitter< CircleParticle > CircleParticleEmitter;
}