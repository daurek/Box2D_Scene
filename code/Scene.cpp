// System
#include <iostream>

// Libraries
#include "rapidxml_utils.hpp"
// Project
#include "Scene.hpp"
#include "ContactListener.hpp"

namespace rigid
{
	Scene::Scene(const std::string & filePath, b2Vec2 gravity)
	{
		physicsWorld = new b2World(gravity);
		LoadScene(filePath);

		ContactListener * contactListenerInstance = new ContactListener{};
		physicsWorld->SetContactListener(contactListenerInstance);
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

		for (rapidxml::xml_node<>* rigidBodyNode = gameObjectNode->first_node(); rigidBodyNode; rigidBodyNode = rigidBodyNode->next_sibling())
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
		// Create ptr to Rigibody
		std::shared_ptr< RigidBody > rigidBody;

		// _______________________________________________________________________ Get Common properties

		// Get type
		std::string shapeType = rigidBodyNode->first_attribute()->value();

		// Get Position
		rapidxml::xml_node<>* positionNode = rigidBodyNode->first_node("position");
		b2Vec2 position
		{
			std::stof(positionNode->first_node("x")->value()),
			std::stof(positionNode->first_node("y")->value())
		};

		// Get Color
		rapidxml::xml_node<>* colorNode = rigidBodyNode->first_node("color");
		sf::Color color
		{
			sf::Uint8(std::stoi(colorNode->first_node("red")->value())),
			sf::Uint8(std::stoi(colorNode->first_node("green")->value())),
			sf::Uint8(std::stoi(colorNode->first_node("blue")->value()))
		};


		// Log Common properties
		std::cout << std::endl;
		std::cout << "			Position: x: " << position.x << " y: " << position.y << std::endl;
		std::cout << "			Color: red: " << int(color.r) << " green: " << int(color.g) << " blue: " << int(color.b) << std::endl;
		std::cout << "			Type: " << shapeType << std::endl;

		// _______________________________________________________________________ Create given type
		b2Shape * rigidShape;

		if		(shapeType == "polygon"	)
		{
			b2PolygonShape polygonRigidShape;

			rapidxml::xml_node<>* pointsNode = rigidBodyNode->first_node("points");

			std::vector< b2Vec2 > pointsList;

			for (rapidxml::xml_node<>* positionNode = pointsNode->first_node(); positionNode; positionNode = positionNode->next_sibling())
				pointsList.push_back({ std::stof(positionNode->first_node("x")->value()), std::stof(positionNode->first_node("y")->value())});

			polygonRigidShape.Set(&pointsList[0], pointsList.size());

			rigidShape = new b2PolygonShape(polygonRigidShape);
		}
		else if (shapeType == "box")
		{
			b2PolygonShape polygonRigidShape;

			rapidxml::xml_node<>* dimensionNode = rigidBodyNode->first_node("dimension");

			b2Vec2 dimension
			{ 
				std::stof(dimensionNode->first_node("width")->value()),
				std::stof(dimensionNode->first_node("height")->value())
			};

			std::cout << "				Dimension: x: " << dimension.x << " y: " << dimension.y << std::endl;
			polygonRigidShape.SetAsBox(dimension.x, dimension.y);

			rigidShape = new b2PolygonShape(polygonRigidShape);
		}
		else if (shapeType == "circle"	)
		{
			b2CircleShape circleRigidShape;

			float radius = std::stof(rigidBodyNode->first_node("radius")->value());
			std::cout << "				Radius: " << radius << std::endl;

			circleRigidShape.m_radius = radius;

			rigidShape = new b2CircleShape (circleRigidShape);
		}

		if (rigidShape != nullptr)
		{
			// Get body type
			b2BodyType bodyType;
			std::string rigidBodyType = rigidBodyNode->first_attribute("bodyType")->value();
			if (rigidBodyType == "static")
				bodyType = b2_staticBody;
			else if(rigidBodyType == "dynamic")
				bodyType = b2_dynamicBody;
			else if (rigidBodyType == "kinetic")
				bodyType = b2_kinematicBody;
			else bodyType = b2_dynamicBody;
			std::cout << "				Body Type: " << rigidBodyType << std::endl;

			// Get Gravity scale
			rapidxml::xml_attribute<>* gravityScaleNode = rigidBodyNode->first_attribute("gravityScale");
			float gravityScale = std::stof(gravityScaleNode->value());

			// Create rigid body with all the properties
			rigidBody = std::make_shared< RigidBody >(RigidBody{ *physicsWorld,{ position.x, position.y }, bodyType, rigidShape, color, 0.1f, gravityScale });
		}
		else
		{
			std::cout << "\n Type " << shapeType << " incorrect or not supported";
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

