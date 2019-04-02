// System
#include <memory>
#include <vector>

// Libraries
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// Project
#include "GameObject.hpp"
#include "Scene.hpp"

using namespace rigid;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(1024, 800), "Box2D Rigid Bodies", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(32));
    window.setVerticalSyncEnabled (true);

	Scene scene{ "../../assets/scene.xml" };

    bool running = true;

	
    sf::Clock timer;
    float deltaTime = 0.017f;          // ~60 fps

    do
    {
        timer.restart ();

        // Process window events:
        sf::Event event;

        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                running = false;
        }

        // Update:
		scene.Update(deltaTime);
        // Clear Window
		window.clear({ 15, 20, 100, 255 });
		// Render Scene and Display Window
		scene.Render (window);
        window.display ();

		deltaTime = (deltaTime + timer.getElapsedTime ().asSeconds ()) * 0.5f;
    }
    while (running);

    return EXIT_SUCCESS;
}
