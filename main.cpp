#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>


int main() {

	constexpr float window_height = 150; // set the height of the window to be displayed
	constexpr float window_length = 450;//set the length of the window to be displayed
	constexpr float ground_height = window_height/6; // ground height is one sixth of the window height


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
	instructions.setPosition(0, 0);
	instructions.setString("Press any key to begin.\nPress Up to jump.\nGet hit 3 times and lose.");
	instructions.setFillColor(sf::Color::White);
	instructions.setFont(font); //set the font 

	while (window.isOpen()) {

		sf::Event event; //initialize an event to track user inputs
		while (window.pollEvent(event)) { //poll the event
			if (event.type == sf::Event::Closed) { // if the event is that the user wants to close the display
				window.close(); //close the window
			}
		}

		window.clear(sf::Color::Black); //clear the window and fill the background with black
		window.draw(ground);
		window.draw(instructions);
		window.display();//finally, display the window
	}
	return 0;

	}
		
