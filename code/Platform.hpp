/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Platform
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
	/// Platform class (Just empty since I can't use GameObject due to abstractness)
	class Platform : public GameObject
	{
	public:

		using GameObject::GameObject;

		virtual void Start()  {};
		virtual void Update(float deltaTime) {};
		virtual void Reset() {};
		virtual void StartContact(GameObject * contactBody) {};
		virtual void EndContact(GameObject * contactBody)  {};

	};

	
	

}