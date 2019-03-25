// System
#include <iostream>

// Libraries
#include "rapidxml_utils.hpp"
// Project
#include "Scene.hpp"
#include "ContactListener.hpp"
#include "Elevator.hpp"


namespace rigid
{
	Scene::Scene(const std::string & filePath, b2Vec2 gravity)
	{
		physicsWorld = new b2World(gravity);
		LoadScene(filePath);

		ContactListener * contactListenerInstance = new ContactListener{};
		physicsWorld->SetContactListener(contactListenerInstance);

		 
		std::shared_ptr< GameObject > car = std::make_shared< GameObject >();

		b2PolygonShape  polygonRigidShape;
		polygonRigidShape.SetAsBox(30, 10);
		std::shared_ptr< RigidBody > chassis = std::make_shared< RigidBody >(
			RigidBody{ *physicsWorld, { 41, 120 }, b2BodyType::b2_dynamicBody, &polygonRigidShape, sf::Color::Yellow, 2.f, 1.f, 0.5f, 0.2f});
		
		//b2PolygonShape  axle1Shape;
		//axle1Shape.SetAsBox(2, 6);
		//std::shared_ptr< RigidBody > axle1 = std::make_shared< RigidBody >(RigidBody{ *physicsWorld, { 20, 100 }, b2BodyType::b2_dynamicBody, &axle1Shape, sf::Color::Red});

		//b2PolygonShape  axle2Shape;
		//axle2Shape.SetAsBox(2, 6);
		//std::shared_ptr< RigidBody > axle2 = std::make_shared< RigidBody >(RigidBody{ *physicsWorld,{ 60, 100 }, b2BodyType::b2_dynamicBody, &axle1Shape, sf::Color::Red });

		b2CircleShape wheel1Shape;
		wheel1Shape.m_radius = 10;
		std::shared_ptr< RigidBody > wheel1 = std::make_shared< RigidBody >(RigidBody{
			*physicsWorld,{ 20, 90 }, b2BodyType::b2_dynamicBody, &wheel1Shape, sf::Color::Blue, 0.3f, 1.f, 5.f, 0.2f });

		b2CircleShape wheel2Shape;
		wheel2Shape.m_radius = 10;
		std::shared_ptr< RigidBody > wheel2 = std::make_shared< RigidBody >(RigidBody{
			*physicsWorld,{ 60, 90 }, b2BodyType::b2_dynamicBody, &wheel1Shape, sf::Color::Blue, 0.3f, 1.f, 5.f, 0.2f });
		
	//	b2PrismaticJointDef jointDef;
	//	jointDef.Initialize(chassis->body, axle1->body, axle1->body->GetWorldCenter(), b2Vec2(0, 1));
	///*	jointDef.lowerTranslation = -0.1;
	//	jointDef.upperTranslation = 0.1;
	//	jointDef.enableLimit = true;*/

	//	std::shared_ptr< Joint > spring1 = std::make_shared< Joint >(Joint{ *physicsWorld, chassis, axle1, &jointDef });
	//	jointDef.Initialize(chassis->body, axle2->body, axle2->body->GetWorldCenter(), chassis->body->GetWorldCenter());
	//	std::shared_ptr< Joint > spring2 = std::make_shared< Joint >(Joint{ *physicsWorld, chassis, axle2, &jointDef });


		b2RevoluteJointDef def;
		def.Initialize(chassis->body, wheel1->body, wheel1->body->GetWorldCenter());
		def.enableMotor = true;
		def.maxMotorTorque = -1000;
		def.motorSpeed = -90000;//90 degrees per second
		std::shared_ptr< Joint > motor1 = std::make_shared< Joint >(Joint{ *physicsWorld, chassis, wheel1, &def });
		//def.Initialize(chassis->body, wheel2->body, wheel2->body->GetWorldCenter());
		//std::shared_ptr< Joint > motor2 = std::make_shared< Joint >(Joint{ *physicsWorld, chassis, wheel2, &def });



		car->rigidBodies.push_back(chassis);
		//car->rigidBodies.push_back(axle1);
		//car->rigidBodies.push_back(axle2);
		car->rigidBodies.push_back(wheel1);
		car->rigidBodies.push_back(wheel2);
		//car->joints.push_back(spring1);
		//car->joints.push_back(spring2);
		car->joints.push_back(motor1);
		//car->joints.push_back(motor2);
		gameObjects["car"] = car;
		
		b2CircleShape wheel12aShape;/*
		wheel12aShape.m_radius = 2;
		b2CircleShape wheel1aShape;
		wheel1aShape.m_radius = 15;
		std::shared_ptr< RigidBody > test = std::make_shared< RigidBody >(RigidBody{
			*physicsWorld,{ 200, 100 }, b2BodyType::b2_dynamicBody, &wheel1aShape, sf::Color::Blue, 0.3f, 1.f, 5.f, 0.2f });
		std::shared_ptr< RigidBody > test2 = std::make_shared< RigidBody >(RigidBody{
			*physicsWorld,{ 210, 120 }, b2BodyType::b2_dynamicBody, &wheel12aShape, sf::Color::Blue, 0.3f, 1.f, 5.f, 0.2f });*/

		//b2RevoluteJointDef defa;
		//defa.Initialize(test->body, test2->body, test->body->GetWorldCenter());
		//defa.enableMotor = true;
		//defa.maxMotorTorque = 170;
		//defa.motorSpeed = 3000000;//90 degrees per second
		//std::shared_ptr< Joint > motor12 = std::make_shared< Joint >(Joint{ *physicsWorld, test, test2, &defa });

		//std::shared_ptr< GameObject > wheelTest = std::make_shared< GameObject >();
		//wheelTest->rigidBodies.push_back(test);
		//wheelTest->rigidBodies.push_back(test2);
		//wheelTest->joints.push_back(motor12);
		//gameObjects["test"] = wheelTest;
		//motor1->SetMotorSpeed(30000);
		//motor2->SetMotorSpeed(30000);
		//motor1->SetMaxMotorTorque(4000);
		//motor2->SetMaxMotorTorque(4000);

		//joint1->SetMaxMotorForce(300);
		////spring1.SetMotorSpeed(-4*Math.pow(spring1.GetJointTranslation(), 1));
		//joint1->SetMotorSpeed(1000);

		//joint2->SetMaxMotorForce(1000);
		//joint2->SetMotorSpeed(1000);

		//chassis->body->ApplyTorque(300, true);
		


		//motor1.SetMaxMotorTorque(input.isPressed(40) || input.isPressed(38) ? 17 : 0.5);
		// particleEmitters.push_back(std::make_shared<RectangleAreaParticleEmitter>( 3 ));
	/*	RectangleAreaParticleEmmiter a{ 2 };
		a.render()*/

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
				gameObject->rigidBodies.push_back(rigidBody);
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
			// rigidBody = std::make_shared< Elevator >(Elevator{ *physicsWorld,{ position.x, position.y }, bodyType, rigidShape, color, 0.1f, gravityScale });
			rigidBody = std::make_shared< RigidBody >(RigidBody{ *physicsWorld,{ position.x, position.y }, bodyType, rigidShape, color, 0.1f, gravityScale });
		}
		else
			std::cout << "\n Type " << shapeType << " incorrect or not supported";

		return rigidBody;
	}

	void Scene::Update(float deltaTime)
	{
		//gameObjects["car"]->rigidBodies[0]->body->ApplyForceToCenter({ 100000,100000 }, true);
		static_cast<b2RevoluteJoint *>(gameObjects["car"]->joints[0]->joint)->SetMotorSpeed(70000);
		//static_cast<b2RevoluteJoint *>(gameObjects["car"]->joints[0]->joint)->SetMaxMotorTorque(30);
		//static_cast<b2RevoluteJoint *>(gameObjects["car"]->joints[1]->joint)->SetMotorSpeed(70000);
		//static_cast<b2RevoluteJoint *>(gameObjects["car"]->joints[1]->joint)->SetMaxMotorTorque(30);
		physicsWorld->Step(deltaTime, 8, 4);

		for (auto & particleEmitter : particleEmitters)
			particleEmitter->Update(deltaTime);
	}

	void Scene::Render(sf::RenderWindow & window)
	{
		for (auto & gameObject : gameObjects)
			gameObject.second->Render(window);

		for (auto & particleEmitter : particleEmitters)
			particleEmitter->Render(window);
	}
}

