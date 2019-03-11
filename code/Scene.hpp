#pragma once

// System
#include <vector>

// Libraries
#include "rapidxml.hpp"
// Project
#include "GameObject.hpp"

namespace rigid
{
	class Scene
	{

	public:

		Scene(const std::string & filePath, b2Vec2 gravity = { 0, -100 });

		void							LoadScene		(const std::string & filePath);
		void							LoadGameObjects	(rapidxml::xml_node<>* gameObjectsNode);
		std::shared_ptr< GameObject >	LoadGameObject	(rapidxml::xml_node<>* gameObjectNode);
		std::shared_ptr< RigidBody >	LoadRigidBody	(rapidxml::xml_node<>* rigidBodyNode);

		void							Update(float deltaTime);
		void							Render(RenderWindow & window);

		std::shared_ptr< b2World >								physicsWorld;
		std::map< std::string, std::shared_ptr< GameObject >>	gameObjects;
	};

}