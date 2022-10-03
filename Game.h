#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
/*Class that acts as game engine*/




class Game
{
private:

	//Variables
	//Window
	sf::RenderWindow *window;
	sf::RenderWindow *endWindow;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	//Resources
	sf::Font font;
	sf::Sound sound;

	//Text
	sf::Text uiText;

	//Audio
	sf::SoundBuffer buffer;
	

	//Game Logic
	int randMultiplier;
	float tilePosition;
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void initEnemies();
	void initFonts();
	void initText();
	void initVariables();
	void initWindow();
	


public:
	//Constructor/destructor
	Game();
	virtual ~Game();

	//accesors
	const bool running()const;
	const bool getEndGame() const;

	//funtions

	void spawnEnemy();
	void updateMousePosition();
	void pollEvents();
	
	void updateEnemies();
	void updateText();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();

	
	
};

