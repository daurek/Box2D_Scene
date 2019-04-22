/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Player
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "GameObject.hpp"

namespace rigid
{
	/// Player Class (Only used to Reset Ball)
	class Player : public GameObject
	{
	public:

		using GameObject::GameObject;

		virtual void Start() {};
		virtual void Update(float deltaTime) {};
		virtual void Reset() override { rigidBodies["circle"]->Reset(); };
		virtual void StartContact(GameObject * contactBody) {};
		virtual void EndContact(GameObject * contactBody)  {};

	};
}