#include "GameObject.hpp"

namespace rigid
{
	void GameObject::Render(sf::RenderWindow & window)
	{
		for (auto & rigidBody : rigidBodies)
			rigidBody->Render(window);
	}
}
