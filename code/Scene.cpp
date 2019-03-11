// System
#include <iostream>

// Libraries
#include "rapidxml_utils.hpp"
// Project
#include "Scene.hpp"

namespace rigid
{
	Scene::Scene(const std::string & filePath, b2Vec2 gravity)
	{
		physicsWorld = std::make_shared< b2World >(b2World(gravity));
		LoadScene(filePath);
	}
		
	void Scene::LoadScene(const std::string & filePath)
	{
		std::cout << "\n________Loading Scene________" << std::endl;
		// Load xml
		rapidxml::file<> xml_file(filePath.c_str());

		// Parse xml
		rapidxml::xml_document<> doc;
		doc.parse<0>(xml_file.data());

		// Load Scene Data
		LoadGameObjects(doc.first_node()->first_node());

		std::cout << "\n\n________Scene  Loaded________" << std::endl;
	}

	void Scene::LoadGameObjects(rapidxml::xml_node<>* gameObjectsNode)
	{
		std::cout << "\n	________Loading GameObjects________\n" << std::endl;
		// Loop through every mesh
		for (rapidxml::xml_node<>* gameObjectNode = gameObjectsNode->first_node(); gameObjectNode; gameObjectNode = gameObjectNode->next_sibling())
		{
			// Get Name
			std::string gameObjectId = gameObjectNode->first_attribute()->value();
			std::cout << "		Name: " << gameObjectId << std::endl;
			// Get Gameobject
			std::shared_ptr< GameObject > gameObject = LoadGameObject(gameObjectNode);
			// Add it to the map if it exists
			if (gameObject)
			{
				gameObjects[gameObjectId] = gameObject;
			}
			else std::cout << "\n GameObject has not been loaded" << std::endl;
		}
	}

	std::shared_ptr< GameObject > Scene::LoadGameObject(rapidxml::xml_node<>* gameObjectNode)
	{
		std::shared_ptr< GameObject > gameObject = std::make_shared< GameObject >();

		for (rapidxml::xml_node<>* rigidBodyNode = gameObjectNode->first_node(); gameObjectNode; gameObjectNode = gameObjectNode->next_sibling())
		{
			// Get RigidBody
			std::shared_ptr< RigidBody > rigidBody = LoadRigidBody(rigidBodyNode);
			// Add it to the list if it exists
			if (gameObject)
			{
				gameObject->rigidBodies.push_back(rigidBody);
			}
			else std::cout << "\n RigidBody has not been loaded";
		}

		return gameObject;
	}

	std::shared_ptr<RigidBody> Scene::LoadRigidBody(rapidxml::xml_node<>* rigidBodyNode)
	{
		std::shared_ptr< RigidBody > rigidBody;// = std::make_shared< RigidBody >();

		std::string rigidBodyType = rigidBodyNode->first_attribute()->value();

		b2Vec2 position
		{
			std::stof(rigidBodyNode->first_node("position")->first_node("x")->value()),
			std::stof(rigidBodyNode->first_node("position")->first_node("y")->value())
		};

		std::cout << "		Position: x: " << position.x << " y: " << position.y << std::endl;
		
		std::cout << "		Type: " << rigidBodyType << std::endl;

		if		(rigidBodyType == "polygon"	)
		{
			b2PolygonShape polygonRigidShape;
			polygonRigidShape.SetAsBox(std::stof(rigidBodyNode->first_node("dimensions")->first_node("width")->value()), 25.f);

			rigidBody = std::make_shared< RigidBody >( RigidBody{ physicsWorld,{ 0,5 }, b2BodyType::b2_staticBody, &polygonRigidShape,  sf::Color::Green, 100.f });
		}
		else if (rigidBodyType == "box")
		{
			b2PolygonShape polygonRigidShape;

			b2Vec2 dimension
			{ 
				std::stof(rigidBodyNode->first_node("dimensions")->first_node("width")->value()),
				std::stof(rigidBodyNode->first_node("dimensions")->first_node("height")->value()) 
			};

			std::cout << "			Dimension: x: " << dimension.x << " y: " << dimension.y << std::endl;
			polygonRigidShape.SetAsBox(dimension.x, dimension.y);

			rigidBody = std::make_shared< RigidBody >(RigidBody{ physicsWorld, { position.x, position.y }, b2BodyType::b2_staticBody, &polygonRigidShape,  sf::Color::Green, 100.f });
		}
		else if (rigidBodyType == "circle"	)
		{

		}
		else
		{
			std::cout << "\n Type " << rigidBodyType << " incorrect or not supported";
		}

		return rigidBody;
	}

	void Scene::Update(float deltaTime)
	{
		physicsWorld->Step(deltaTime, 8, 4);
	}

	void Scene::Render(RenderWindow & window)
	{
		for (auto & gameObject : gameObjects)
			gameObject.second->render(window);
	}
}

