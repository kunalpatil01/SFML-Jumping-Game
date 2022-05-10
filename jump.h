#ifndef _JUMP_
#define _JUMP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <random>


constexpr float window_height = 150; // set the height of the window to be displayed
constexpr float window_length = 450;//set the length of the window to be displayed
constexpr float ground_height = window_height / 6; // ground height is one sixth of the window height
constexpr float square_length = window_height / 6;
constexpr float player_width = 3 * square_length;


/**
@class enemy represents the blocks that come at the player in the game
*/
class enemy : public sf::Shape {

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
	void update_position();

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

	/**
	function to get the number of points in the enemy class
	@return number of vertices of the rectange
	*/
	size_t getPointCount() const;

	/**
	function to return the coordinates of a given vertex
	@param index specify the vertex number that you want the coordiantes of 
	@return coordinates of that index
	*/
	sf::Vector2f getPoint(size_t index) const;

<<<<<<< HEAD
	/**
	function to display the enemy
	*/
=======
>>>>>>> 49aafc770c14a3364ae23746e6463fc972e3368a
	void display(sf::RenderWindow& window) const;

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
	sf::Sound hit_sound; //sound to make when hit
	sf::Sound jump_sound; //sound to make when jump
	int lives; //number of lives that the character has

	
public:

	/**
	default constructor for character class
	*/
	character();

	/**
	accessor function to find the smallest y value of character
	@return the minimum y value of the bottom part
	*/
	float get_y_min() const;

	/**
	accessor function to find the greatest x value of character
	@return max y value of character
	*/
	float get_x_max() const;

	/**
	function that will display the character
	@param window the render window to display the top and bottom part of the characetr on
	*/
	void display(sf::RenderWindow& window) const;

	/**
	member function to make the character jump
	*/
	void jump();

	/**
	member function to check if character is alive
	@return true if character is alive, false if not
	*/
	bool alive() const;

	/**
	function to check if character is currently touching an enemy
	@param Enemy the specific enemy that we're checking for hit
	@return true if so, false if not
	*/
	bool hit_by(enemy& Enemy);

	/**
	function to be called by Game class to update the position of character if it jumped
	*/
	void update_position();


};

class Game {

private:
	character* _character;	//member variables are pointer to character and enemy classes
	std::deque<enemy*> enemies;
	unsigned int score;
	sf::Clock timer;

	/**
	Function that handles the removal of enemy objects by checking if the object is either touching the player or out of range
	*/
	void do_removals();

	/**
	Moves each enemy left by one point
	*/
	void move_enemies();

	/**
	Moves character (not defined yet; would require some information from character class regarding time since last jump)
	*/
	void move_character();


	/**
	Makes enemies and adds them to the deque of enemies.
	*/
	void make_enemies();



public:

	/**
	Default constructor for Game
	*/
	Game();

	/**
	Destructor for game to free dynamically allocated memory
	*/
	~Game();

	/**
	This function will be called in each iteration of the while-loop in int main and will orchestrate most of the
	events in the game
	*/
	void step();	//function that orchestrates one "frame" of the game

	/**
	For now this just manages the case of the player pressing the jump button
	*/
	void manage_events(sf::Event e);

	/**
	Function that calls display on all enemies and characters
	@param sf::RenderWindow& window The window object to display in
	*/
	void display(sf::RenderWindow& window) const;

	/**
	Getter for the score of the game
	@return The score of the game
	*/
	unsigned int get_score() const;
};

#endif