#ifndef _JUMP_
#define _JUMP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/**
@class enemy represents the blocks that come at the player in the game
*/
class enemy : public sf::Shape{

private:

	static constexpr int speed = 200; // speed of the enemy in pixels/second
	sf::Clock clock; //clock to keep track of position of enemy
	sf::RectangleShape body; //body of the enemy


public:

	/**
	default constructor for enemy 
	*/
	enemy(); 

	/**
	simple function to update the position of the enemy to be called upon by Game
	@param pos the new position of enemy
	*/
	void update_position(sf::Vector2f pos);

	/**
	simple function to find the leftmost position of the enemy
	@return the smallest x position of the enemy
	*/
	float get_x_min() const;

	/**
	simple function to find the topmost position of the enemy
	@return the largest y position of the enemy
	*/
	float get_y_max() const;

};


/**
@class character that represents the object that the user controls
*/
class character {

private:

	//some static variables for calculating jump height
	static constexpr float T1 = 1;
	static constexpr float T2 = 1.1;

	const sf::Vector2f init_pos; //static variable to keep track of the intial bottom left position (x pos is 0, y pos is the height of the window)
	sf::Clock last_jump; //clock to keep track of time since the last jump
	sf::RectangleShape top; //square part of the character
	sf::RectangleShape bottom; //rectangle part of the character
	sf::Sound hit; //sound to make when hit
	sf::Sound jump; //sound to make when jump

public:

	/**
	default constructor for character class
	*/
	character(); 



};



#endif
