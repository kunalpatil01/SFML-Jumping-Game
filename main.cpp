#include <SFML/Graphics.hpp>
#include <iostream>


int main() {

	constexpr float window_height = 400; // set the height of the window to be displayed
	constexpr float window_length = 400;//set the length of the window to be displayed
	constexpr float circ_radius = 150;  //set the radius of the circle to be drawn

	sf::RenderWindow window(sf::VideoMode(window_length, window_height), "Hello World"); //initialize the window to be displayed, with size 400x400 pixels
	 
	sf::CircleShape circ(circ_radius); //create a circle object with radius 150 to be filled
	const sf::Color UCLA_yellow{ 255,209, 0 , 255 }; //create the color for UCLA's yellow color, to be the circle's color
	const sf::Color UCLA_blue{ 39, 116, 174, 255 }; //create the color for UCLA's blue color, to be the background and text color

	circ.setFillColor(UCLA_yellow); // fill the circle with UCLA yellow color
	circ.setOrigin(circ_radius, circ_radius); //make the origin of the cirlce its center (radius by radius)
	circ.setPosition(window_length/2, window_height/2); //put the origin at the center of the window (half its length and width) so that the whole circle is centered

	sf::Font font; // initialize a font for the text PIC10C
	if (!font.loadFromFile("comic.ttf")) { // if the font cannot be loaded from the file
		std::cerr << "could not load comic font" << '\n'; // send an error to cerr
		return -1; //return a non-zero integer to main to indicate failure
	}

	constexpr float text_size = 50; //set the size of the text to be 50

	sf::Text text; // initialize a text for the text PIC10C
	text.setCharacterSize(text_size); //set the size of the text 
	text.setString("PIC 10C"); //make the text write PIC10C
	text.setFillColor(UCLA_blue); // set the color of the text to be UCLA's blue 
	text.setPosition(110, 165); // put the position of the start of the text such that the text is roughly centered on the screen, which is 110 pixels to the right and 165 pixels down from the top left corner 
	text.setFont(font); // set the font of the text to be comic.ttf font 


	while (window.isOpen()) { //while the window is open (the user hasn't clicked close)
		sf::Event event; //initialize an event to track user inputs
		while (window.pollEvent(event)) { //poll the event
			if (event.type == sf::Event::Closed) { // if the event is that the user wants to close the display
				window.close(); //close the window
			}
		} 
		window.clear(UCLA_blue); //clear the window and fill the background with UCLA blue
		window.draw(circ); //draw the circle first
		window.draw(text);//draw the text over it


		window.display();//finally, display the window
	}
	return 0;



}