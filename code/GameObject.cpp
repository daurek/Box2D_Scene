/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::GameObject
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "GameObject.hpp"

namespace rigid
{
	void GameObject::Render(sf::RenderWindow & window)
	{
		// Render only if visible
		if (isVisible)
			for (auto & rigidBody : rigidBodies)
				rigidBody.second->Render(window);
	}
}
