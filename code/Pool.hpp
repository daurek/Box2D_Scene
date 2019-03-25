#pragma once

#include "Particle.hpp"

namespace rigid
{
	template< class PARTICLE >
	class Pool
	{
	public:

		class Iterator
		{
			
		};

		class Node
		{
			Particle * particle;
			Node     * next;
			Node     * prev;
		};

	private:

		typedef PARTICLE Particle;

		std::vector< Particle > particles;
		std::vector< Node     > used;
		std::vector< Node     > free;

	public:

		Particle * getFreeParticle();

		Iterator begin();
		Iterator end();
	};
}