#pragma once

#include <vector>

#include "RigidBody.hpp"
#include "Joint.hpp"

namespace rigid
{
	class GameObject
	{

	public:

		GameObject() {};

		std::vector< std::shared_ptr< RigidBody > > rigidBodies;
		std::vector<Joint> joints;

		void render(RenderWindow & window);
	};

}