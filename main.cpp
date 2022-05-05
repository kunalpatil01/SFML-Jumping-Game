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
	ground.setPosition(sf::Vector2f(0, ground_height));

	while (window.isOpen()) {

		sf::Event event; //initialize an event to track user inputs
		while (window.pollEvent(event)) { //poll the event
			if (event.type == sf::Event::Closed) { // if the event is that the user wants to close the display
				window.close(); //close the window
			}
		}

		window.clear(sf::Color::Black); //clear the window and fill the background with black
		window.draw(ground);

	

		window.display();//finally, display the window
	}
	return 0;

	}
		
