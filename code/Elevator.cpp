/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Elevator
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Elevator.hpp"
// Project
#include "Car.hpp"

namespace rigid
{
	void Elevator::Start()
	{
		// Cahing elements
		elevator = rigidBodies["elevator"];
		elevatorJoint = static_cast< b2PrismaticJoint * >(joints["elevatorJoint"]->joint);
	}

	void Elevator::Update(float deltaTime)
	{
		// If the car is not inside then wait some time and go down
		if (!inside)
		{
			timer += deltaTime;
			if (timer >= 3)
				elevatorJoint->SetMotorSpeed(-350);
		}
		// If the car is inside then go up
		else
		{
			timer = 0;
			elevatorJoint->SetMotorSpeed(350);
		}
	}

	void Elevator::StartContact(GameObject * contactBody)
	{
		// If the car has collided enable flag
		Car * car = dynamic_cast<Car *>(contactBody);
		if (car)
			inside = true;
	}

	void Elevator::EndContact(GameObject * contactBody)
	{
		// If the car has left disable flag
		Car * car = dynamic_cast<Car *>(contactBody);
		if (car)
			inside = false;
	}

	void Elevator::Reset()
	{
		// Reset elements
		elevatorJoint->SetMotorSpeed(0);
		elevator->Reset();
	}
}