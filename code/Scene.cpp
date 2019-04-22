/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Scene
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Scene.hpp"

// System
#include <iostream>
// Libraries
#include "rapidxml_utils.hpp"
// Project
#include "ContactListener.hpp"
#include "RectangleArea.hpp"
#include "Joint.hpp"
#include "Car.hpp"
#include "Platform.hpp"
#include "Elevator.hpp"
#include "Goal.hpp"
#include "Player.hpp"
#include "Fire.hpp"


namespace rigid
{
	Scene::Scene(const std::string & filePath, b2Vec2 gravity) : physicsWorld(new b2World(gravity))
	{
		// Loads entire scene
		LoadScene(filePath);

		// Set world Colision Listener
		physicsWorld->SetContactListener(new ContactListener{});

		// Start every GameObject to it's initial state
		for (auto & gameObject : gameObjects)
			gameObject.second->Start();
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

		//_______________________________________________Joints_______________________________________________
		// I was going to add joints to the xml but it would take more time since I have to read both objects and all their properties

		// Elevator Joint
		b2PrismaticJointDef prismaticJointDef;
		prismaticJointDef.enableMotor		= true;
		prismaticJointDef.maxMotorForce		= 200000.f;
		prismaticJointDef.enableLimit		= true;
		prismaticJointDef.lowerTranslation	= 0.f;
		prismaticJointDef.upperTranslation	= 405.f;
		prismaticJointDef.localAxisA.Set(0.f, 1.f);
		prismaticJointDef.localAnchorA.Set(0.f, 70.f);

		gameObjects["elevator1"]->AddJoint("elevatorJoint", std::make_shared< Joint >(*physicsWorld, gameObjects["elevator1Anchor"]->GetRigidBody("anchor"), gameObjects["elevator1"]->GetRigidBody("elevator"), &prismaticJointDef));
		gameObjects["elevator1Anchor"]->isVisible = false;

		prismaticJointDef.upperTranslation	= 155.f;
		prismaticJointDef.localAnchorA.Set(0.f, 320.f);
		gameObjects["elevator2"]->AddJoint("elevatorJoint", std::make_shared< Joint >(*physicsWorld, gameObjects["elevator2Anchor"]->GetRigidBody("anchor"), gameObjects["elevator2"]->GetRigidBody("elevator"), &prismaticJointDef));
		gameObjects["elevator2Anchor"]->isVisible = false;

		// Cache Car 
		std::shared_ptr< Car > car = std::dynamic_pointer_cast<Car>(gameObjects["car"]);

		// Wheel Joints
		b2RevoluteJointDef revoluteDef;
		revoluteDef.referenceAngle = 0;
		revoluteDef.localAnchorA.Set(-30, -20);
		revoluteDef.enableMotor = true;
		revoluteDef.maxMotorTorque = 130000;
		car->AddJoint("wheel1Joint", std::make_shared< Joint >(*physicsWorld, car->GetRigidBody("chassis"), car->GetRigidBody("wheel1"), &revoluteDef));

		revoluteDef.localAnchorA.Set(30, -20);
		car->AddJoint("wheel2Joint", std::make_shared< Joint >(*physicsWorld, car->GetRigidBody("chassis"), car->GetRigidBody("wheel2"), &revoluteDef));

		b2WeldJointDef weldDef;
		weldDef.localAnchorA.Set(-27, 20);
		car->AddJoint("gripLeftJoint", std::make_shared< Joint >(*physicsWorld, car->GetRigidBody("chassis"), car->GetRigidBody("gripLeft"), &weldDef));
		weldDef.localAnchorA.Set(27, 20);
		car->AddJoint("gripRightJoint", std::make_shared< Joint >(*physicsWorld, car->GetRigidBody("chassis"), car->GetRigidBody("gripRight"), &weldDef));

		b2RevoluteJointDef closerJoint;
		closerJoint.enableMotor = true;
		closerJoint.maxMotorTorque = 100000;
		closerJoint.enableLimit = true;
		closerJoint.lowerAngle = -3.f;
		closerJoint.upperAngle = 0.5f;
		closerJoint.localAnchorA.Set(0, 12);
		closerJoint.localAnchorB.Set(25, 0);
		car->AddJoint("closerJoint", std::make_shared< Joint >(*physicsWorld, car->GetRigidBody("gripLeft"), car->GetRigidBody("closer"), &closerJoint));

		weldDef.localAnchorA.Set(70, 0);
		car->AddJoint("waterJoint", std::make_shared< Joint >(*physicsWorld, car->GetRigidBody("chassis"), car->GetRigidBody("water"), &weldDef));

		// Setup fire scene reference 
		std::dynamic_pointer_cast<Fire>(gameObjects["fire"])->scene = this;

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
				gameObjects[gameObjectId] = gameObject;
			else 
				std::cout << "\n GameObject has not been loaded" << std::endl;
		}
	}

	std::shared_ptr< GameObject > Scene::LoadGameObject(rapidxml::xml_node<>* gameObjectNode)
	{
		std::shared_ptr< GameObject > gameObject;

		// Create class by classType
		std::string classType = gameObjectNode->first_attribute("classType")->value();
		if		(classType == "Player")
			gameObject = std::make_shared< Player >();
		else if (classType == "Platform")
			gameObject = std::make_shared< Platform >();
		else if (classType == "Elevator")
			gameObject = std::make_shared< Elevator >();
		else if (classType == "Goal")
			gameObject = std::make_shared< Goal >();
		else if (classType == "Fire")
			gameObject = std::make_shared< Fire >();
		else if (classType == "Car")
			gameObject = std::make_shared< Car >();

		// Loop RigidBodies and create them
		for (rapidxml::xml_node<>* rigidBodyNode = gameObjectNode->first_node(); rigidBodyNode; rigidBodyNode = rigidBodyNode->next_sibling())
		{
			// Get RigidBody
			std::string classType = rigidBodyNode->first_attribute("name")->value();
			std::shared_ptr< RigidBody > rigidBody = LoadRigidBody(rigidBodyNode);
			// Add it to the list if it exists
			if (gameObject)
				gameObject->AddRigidbody(classType, rigidBody);
			else 
				std::cout << "\n RigidBody has not been loaded";
		}

		return gameObject;
	}

	std::shared_ptr< RigidBody > Scene::LoadRigidBody(rapidxml::xml_node<>* rigidBodyNode)
	{
		// Create ptr to Rigibody
		std::shared_ptr< RigidBody > rigidBody;

		// _______________________________________________________________________ Get Common properties

		// Get type
		std::string shapeType = rigidBodyNode->first_attribute("type")->value();

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
			else if (rigidBodyType == "kinetic")
				bodyType = b2_kinematicBody;
			else bodyType = b2_dynamicBody;
			std::cout << "				Body Type: " << rigidBodyType << std::endl;

			// Get Density value
			rapidxml::xml_attribute<>* densityValueNode = rigidBodyNode->first_attribute("density");
			float densityValue = 0.1f;
			if (densityValueNode)
				densityValue = std::stof(densityValueNode->value());


			// Get Gravity scale
			rapidxml::xml_attribute<>* gravityScaleNode = rigidBodyNode->first_attribute("gravityScale");
			float gravityScale = 1.f;
			if (gravityScaleNode)
				gravityScale = std::stof(gravityScaleNode->value());

			// Get Sensor state
			rapidxml::xml_attribute<>* isSensorNode = rigidBodyNode->first_attribute("isSensor");
			bool isSensor = false;
			if (isSensorNode)
				isSensor = std::stoi(isSensorNode->value()) == 1;

			// Create rigid body with all the properties
			rigidBody = std::make_shared< RigidBody >(*physicsWorld, b2Vec2{ position.x, position.y }, bodyType, rigidShape, color, densityValue, gravityScale, 1.f, 1.f, isSensor);
		}
		else
			std::cout << "\n Type " << shapeType << " incorrect or not supported";

		return rigidBody;
	}

	void Scene::Update(float deltaTime)
	{
		// Reset world if R is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			Reset();

		// Physics Step
		physicsWorld->Step(deltaTime, 8, 4);

		// Update every gameobject
		for (auto & gameObject : gameObjects)
		{
			gameObject.second->Update(deltaTime);
			// Check if it needs to be reseted (has to be outside Step, that's why there's a flag)
			if (gameObject.second->toReset)
			{
				gameObject.second->toReset = false;
				gameObject.second->Reset();
			}
		}
	}

	void Scene::Render(sf::RenderWindow & window)
	{
		// Render everything
		for (auto & gameObject : gameObjects)	
			gameObject.second->Render(window);
	}

	void Scene::Reset()
	{
		// Reset everything
		for (auto & gameObject : gameObjects)
			gameObject.second->toReset = true;
	}
}

