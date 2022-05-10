#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp >
#include "jump.h"


enemy::enemy() : clock(), body() { //first default construct clock and body

	constexpr float side_length = 150 / 6; // the side length is the window height (150) over 6

	body.setFillColor(sf::Color::Yellow); //make it yellow
	body.setSize(sf::Vector2f(side_length, side_length)); //set the size appropriately

	//x position is the length of the window (450)
	//y position twice the height of the square
	body.setPosition(sf::Vector2f(450, float(150 - 2*150 / 6))); //set the position to be the rightmost of the screen, lying on the ground
}

void enemy::update_position() {
	if (clock.getElapsedTime().asMilliseconds() >= 10)
	{
		auto t = clock.getElapsedTime().asMilliseconds();
		body.setPosition(static_cast<float>(body.getPosition().x - 2), body.getPosition().y);
		clock.restart();
	}
}

float enemy::get_x_min() const {

	/*
		//get the origin of the body (top left corner) and return the x part
	const sf::Vector2f origin = body.getOrigin();
	return origin.x;
	*/
	return body.getPosition().x;
}

float enemy::get_y_max() const {

	/**		old stuff
	//get the origin of the body (top left corner) and return the y part 
	const sf::Vector2f origin = body.getOrigin();
	return origin.y;
	*/
	auto t = body.getPosition().y;
	return body.getPosition().y + square_length;	//getPosition() corresponds to the bottom left corner, so we add the square length
}

size_t enemy::getPointCount() const {	return body.getPointCount(); }

sf::Vector2f enemy::getPoint(size_t index) const { return body.getPoint(index); }

void enemy::display(sf::RenderWindow& window) const { window.draw(body); }

character::character() : init_pos(0.f, float(150 - 150 / 6)), last_jump(), top(), bottom(), lives(3) { //construct the init post to be x position of 0 and y position to be window height minus ground height, default construct last jump, top and bottom


	//set the correct properties of the shapes
	constexpr float window_height = 150;
	constexpr float square_length = window_height / 6; // square length is one sixth of the window height
	constexpr float rectangle_length = square_length * 3; // rectangle length is three times the square length
	constexpr float bottom_x_pos = 0; //the intial x position of the bottom part is 0
	constexpr float bottom_y_pos = window_height - 2 * square_length; //the inital y position of the bottom part is the window height minus twice the square length
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
	hit_sound = sf::Sound(hit_buffer);

	sf::SoundBuffer jump_buffer;
	if (!jump_buffer.loadFromFile("Resources/jump.wav")) {//if we are unable to load the sound file, throw an error
		throw std::logic_error("Could not open file jump.wav");
	}

	jump_sound = sf::Sound(jump_buffer);
}

float character::get_y_min() const {

	//getPoint(3) will return the coordiantes of the 4th vertex of bottom 
	return bottom.getPoint(3).y; //return y component of the last vertex of the bottom part of the character (which is at the bottom of the character)


}

float character::get_x_max() const {

	constexpr float square_length = 150 / 6; // square length is one sixth of the window height
	constexpr float rectangle_length = square_length * 3; // rectangle length is three times the square length

	return rectangle_length;

}

void character::display(sf::RenderWindow& window) const {

	//draw the top and bottom
	window.draw(top);
	window.draw(bottom);

}

void character::jump() {

	float time = last_jump.getElapsedTime().asSeconds();

	if (time <= T2) { //if time is less than t2, we can't jump so do nothing
		return;
	}
	else { // otherwise restart the clock
		jump_sound.play();
		last_jump.restart();
	}

}

bool character::alive() const {

	if (lives == 0) { //if we have 0 lives, then return false
		return false;
	}
	else {//otherwise return true
		return true;
	}

}

bool character::hit_by(enemy& Enemy) {

	if ((Enemy.get_y_max() >= get_y_min()) && (Enemy.get_x_min() <= get_x_max())) { // if the y or x values of enemy and character are intersecting  

		hit_sound.play(); //play hit sound
		lives--; // decrement lives
		return true;

	}
	else { //otherwise, return false
		return false;
	}

}

<<<<<<< HEAD
void character::update_position() {

	constexpr float square_length = 150 / 6;
	float time = last_jump.getElapsedTime().asSeconds();
	float jump_height;

	if (time <= T1) { //if the time since the last jump is under 1 second, then the character is in motion so use the formula to find jump height
		jump_height = (8 * (square_length)*time * (T1 - time)) / (T1 * T1);
	}
	else { //otherwise, the character is not in motion so jump height is 0 
		jump_height = 0;
	}

	//translate the top and the bottom by the jump height 
	top.move(0.f, jump_height);
	bottom.move(0.f, jump_height); 

}




=======
>>>>>>> 49aafc770c14a3364ae23746e6463fc972e3368a
void Game::do_removals()
{
	if (!enemies.empty())
	{
		enemy* front = enemies.front();
		bool hit_by;
		if (front)
		{
			hit_by = _character->hit_by(*front);
			//checks if the player is hit by the frontmost enemy or if the enemy is out of bounds
			if (hit_by || front->get_x_min() < (0 - square_length))
			{
				delete enemies.front();	//delete enemy and shift queue forwards
				enemies.pop_front();

				if (!hit_by) { ++score; }//if the player was not hit by the enemy then increase the score by one
			}
		}
	}


}
void Game::move_enemies()
{

	for (auto it : enemies)		//move every enemy in the list 2 pixels to the left
	{
		
		it->update_position();	//move the enemy to the left
	}
	

}
void Game::move_character()
{
	//uncomment when update_position has been implemented
	//_character->update_position();
}
void Game::make_enemies()
{

	if (timer.getElapsedTime().asSeconds() >= 1.5)	//if more than 1.5 seconds have elapsed, we generate a new enemy with probability 50%
	{
		int val = rand();
		
		//uncomment the next line will cause the game program to not compile as enemy is an abc
		if (val % 2 == 0) { enemies.push_back(new enemy); }	//note: enemy is pure virtual, we need to override some functions

		timer.restart();	//restart the timer
	}
}

void Game::step()
{
	move_character();
	move_enemies();
	do_removals();
	make_enemies();
}

void Game::manage_events(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Up)	//here we try to implement jump
		{
			_character->jump();
		}
	}
}

Game::Game(): score(0), timer()
{
	_character = new character;
	
}

Game::~Game()
{
	delete _character;
	_character = nullptr;

	for (auto it : enemies)
	{
		if (it != nullptr)
		{
			delete it;
			it = nullptr;
		}
	}
}

void Game::display(sf::RenderWindow& window) const
{
	_character->display(window);

	for (auto it : enemies)
	{
		it->display(window);
	}
}

unsigned int Game::get_score() const
{
	return score;
}
