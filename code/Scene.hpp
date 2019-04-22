/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Scene
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Libraries
#include "rapidxml.hpp"
// Project
#include "GameObject.hpp"

namespace rigid
{
	/// Scene Container class that updates and renders every GameObject, also stores the Physics World
	class Scene 
	{

	public:

		/// Creates Scene with the given XML file path and world gravity
		Scene(const std::string & filePath, b2Vec2 gravity = { 0, -100 });

		/// Clear world
		~Scene() 
		{ 
			delete physicsWorld; 
			// When world is deleted Box2D deletes every b2Shape on it 
		}

		/// Updates every GameObject (Logic and Physics Step)
		void							Update(float deltaTime);

		/// Renders every GameObject with the given window
		void							Render(sf::RenderWindow & window);

		/// Resets every GameObject in the Scene 
		void							Reset();
		
		// Loaders

		/// Loads Scene with the given XML file path
		void							LoadScene		(const std::string & filePath);

		/// Loads every GameObject with the given node 
		void							LoadGameObjects	(rapidxml::xml_node<>* gameObjectsNode);

		/// Loads every RigidBody of a GameObject with the given node 
		std::shared_ptr< GameObject >	LoadGameObject	(rapidxml::xml_node<>* gameObjectNode);

		/// Loads RigidBody with the given node 
		std::shared_ptr< RigidBody >	LoadRigidBody	(rapidxml::xml_node<>* rigidBodyNode);

	private:

		/// Physics Box2D World Reference
		b2World * physicsWorld;

		/// Every GameObject in the scene along with it's name
		std::map< std::string, std::shared_ptr< GameObject >>				gameObjects;
	};

}