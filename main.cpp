#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "jump.h"
#include <iostream>

//moved constexpr variables to header file

int main() {

	sf::RenderWindow window(sf::VideoMode(window_length, window_height), "Jumping Game"); //initialize the window to be displayed, with size 400x400 pixels

	//initialize the ground of the game
	sf::RectangleShape ground;
	ground.setSize(sf::Vector2f(window_length, ground_height));
	ground.setFillColor(sf::Color::White);
	ground.setPosition(sf::Vector2f(0, window_height-ground_height));

	//initialize the instructional text 
	sf::Text instructions;
	instructions.setCharacterSize(20);

	sf::Font font; 
	if(!font.loadFromFile("Resources/sansation.ttf")) { //if we couldn't open the font file, throw an error
		throw std::logic_error("Could not find font sansation.ttf");
	}
	//instructions.setPosition(0, 0);
	instructions.setString("Press any key to begin.\nPress Up to jump.\nGet hit 3 times and lose.");
	instructions.setFillColor(sf::Color::White);
	instructions.setFont(font); //set the font 

	bool start = false;

	Game game;
	while (window.isOpen()) {

		sf::Event event; //initialize an event to track user inputs
		while (window.pollEvent(event)) { //poll the event

			if (event.type == sf::Event::Closed) { // if the event is that the user wants to close the display
				window.close(); //close the window
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (start == false) { start = true; }
				else 
				{
					game.manage_events(event);
					//game.step();
					//game.display(window);

				}
			}


		}

		//game.step();


		window.clear(sf::Color::Black); //clear the window and fill the background with black
		window.draw(ground);
		(start) ? (game.display(window)):(window.draw(instructions));
		window.display();//finally, display the window
		int x = 0;
	}
	return 0;

	}
		
