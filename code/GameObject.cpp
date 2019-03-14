#include "GameObject.hpp"

namespace rigid
{
	void GameObject::render(RenderWindow & window)
	{
		for (auto & rigidBody : rigidBodies)
			rigidBody->Render(window);
	}
}
