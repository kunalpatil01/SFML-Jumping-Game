#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp >
#include "jump.h"


enemy::enemy() : clock(), body() { //first default construct clock and body

	constexpr float side_length = 150 / 6; // the side length is the window height (150) over 6

	body.setFillColor(sf::Color::Yellow); //make it yellow
	body.setSize(sf::Vector2f(side_length, side_length)); //set the size appropriately

	//x position is the length of the window (450)
	//y position twice the height of the square
	body.setPosition(sf::Vector2f(450, 2*side_length)); //set the position to be the rightmost of the screen, lying on the ground
}

void enemy::update_position(sf::Vector2f pos){
	body.setPosition(pos);
}

float enemy::get_x_min() const{

	//get the origin of the body (top left corner) and return the x part
	const sf::Vector2f origin = body.getOrigin(); 
	return origin.x;
}

float enemy::get_y_max() const {

	//get the origin of the body (top left corner) and return the y part 
	const sf::Vector2f origin = body.getOrigin();
	return origin.y;
}

character::character() : init_pos(0.f, float(150-150/6)), last_jump(), top(), bottom() { //construct the init post to be x position of 0 and y position to be window height minus ground height, default construct last jump, top and bottom


	//set the correct properties of the shapes
	constexpr float window_height = 150; 
	constexpr float square_length = window_height / 6; // square length is one sixth of the window height
	constexpr float rectangle_length = square_length * 3; // rectangle length is three times the square length
	constexpr float bottom_x_pos = 0; //the intial x position of the bottom part is 0
	constexpr float bottom_y_pos = window_height - 2*square_length; //the inital y position of the bottom part is the window height minus twice the square length
	constexpr float top_y_pos = window_height - 3 * square_length; //the initial y position of the top part is the window height minus three times the square legnth
	constexpr float top_x_pos = square_length; //the intial x positon of the top part is the square length

	bottom.setSize(sf::Vector2f(rectangle_length, square_length));
	bottom.setPosition(sf::Vector2f(bottom_x_pos, bottom_y_pos));
	bottom.setFillColor(sf::Color::Red);

	top.setSize(sf::Vector2f(square_length, square_length));
	top.setPosition(sf::Vector2f(top_x_pos, top_y_pos));
	top.setFillColor(sf::Color::Red);

	//initialize the sounds 
	sf::SoundBuffer hit_buffer;
	if (!hit_buffer.loadFromFile("Resources/hit.wav")) {//if we are unable to load the sound file, throw an error
		throw std::logic_error("Could not open file hit.wav");
	}
	hit = sf::Sound(hit_buffer);

	sf::SoundBuffer jump_buffer;
	if (!jump_buffer.loadFromFile("Resources/jump.wav")) {//if we are unable to load the sound file, throw an error
		throw std::logic_error("Could not open file jump.wav");
	}
	jump = sf::Sound(jump_buffer); 
}





