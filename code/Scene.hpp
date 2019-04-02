#pragma once

// System
#include <vector>

// Libraries
#include "rapidxml.hpp"
// Project
#include "GameObject.hpp"
#include "ParticleEmitter.hpp"

namespace rigid
{
	class Scene 
	{

	public:

		Scene(const std::string & filePath, b2Vec2 gravity = { 0, -100 });

		~Scene() { delete physicsWorld; }

		void							LoadScene		(const std::string & filePath);
		void							LoadGameObjects	(rapidxml::xml_node<>* gameObjectsNode);
		std::shared_ptr< GameObject >	LoadGameObject	(rapidxml::xml_node<>* gameObjectNode);
		std::shared_ptr< RigidBody >	LoadRigidBody	(rapidxml::xml_node<>* rigidBodyNode);

		void							Update(float deltaTime);
		void							Render(sf::RenderWindow & window);

		b2World *															physicsWorld;
		std::map< std::string, std::shared_ptr< GameObject >>				gameObjects;
		std::vector < std::shared_ptr< CircleParticleEmitter >>		particleEmitters;
	};

}