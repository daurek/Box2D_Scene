#pragma once


#include <vector>
#include "Pool.hpp"
#include "Area.hpp"
#include "CircleParticle.hpp"
#include "RectangleArea.hpp"

namespace rigid
{
	template< class PARTICLE, class AREA >
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

		ParticleEmitter(int particles_per_second) : particles_per_second(particles_per_second)
		{
			state = EVOLVING;

		}

		void Update(float t)
		{
			generate_particles(t);
			for (auto & particle : particles)
				particle.Update(t);
			/*for(Pool< Particle >::Iterator i = particles.begin(); i != particles.end(); ++i)
				particle.update(t);*/
		}

		void Render(sf::RenderWindow & ctx)
		{
			for (auto & particle : particles)
				particle.Render(ctx);
			/*for (Pool< Particle >::Iterator i = particles.begin(); i != particles.end(); ++i)
				particle.render(ctx);*/
		}

	private:

		void generate_particles(float t)
		{
			// cuando ha transcurrido cierto tiempo, generar
			// cierto número de partículas
			particles.push_back(PARTICLE{ sf::Vector2f{300, 300} });
		}

	};

	typedef ParticleEmitter< CircleParticle, RectangleArea > RectangleAreaParticleEmitter;
}