#include "Game.h" 



//Private Functions
void Game::initEnemies()
{
	this->enemy.setPosition(50.f, 50.f);
	this->enemy.setSize(sf::Vector2f(100.f, 300.f));
	this->enemy.setFillColor(sf::Color::Black);
	
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Dosis-Light.ttf")) {
		std::cout << "ERROR::GAME::INITFONTS: Failed to load font! " << '\n';
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(48);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setOutlineColor(sf::Color::Black);
	this->uiText.setOutlineThickness(4);
	this->uiText.setString("NONE");
	this->uiText.setPosition(100, 0);
}

void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this -> points = 0;
	this->health = 1;
	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 4;
	this->mouseHeld = false;
	this->tilePosition = 100;

}

void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 400;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Constructor/Destructor

Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();

}

Game::~Game(){
	delete this->window;

}

//Accesors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}




//Functions

void Game::spawnEnemy()
{
	
	this->randMultiplier = rand() % 4 + 0;

	this->enemy.setPosition(this->tilePosition * this->randMultiplier, 0.f);

	this->enemy.setFillColor(sf::Color::Black);

	//Spawn the enemy
	this->enemies.push_back(this->enemy);

}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::pollEvents()
{
	//event polling
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		}
	}
}

void Game::updateEnemies()
{
	//Updating the timer of enemies spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}

		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies

	for (int i = 0; i < enemies.size(); i++) {
		bool deleted = false;
		this->enemies[i].move(0.f, 10.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
		


	}

	//check if clicked upon

	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) 
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < enemies.size() && deleted == false; i++) 
			{

				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) 
				{
					//Play sound
					int random = rand() % 3 + 1;
					switch (random) {
					case 1:
						if (!this->buffer.loadFromFile("piano.wav"))
							std::cout << "sound error";

						this->sound.setBuffer(this->buffer);
						this->sound.play();
						break;
					case 2:
						if (!this->buffer.loadFromFile("piano2.wav"))
							std::cout << "sound error";

						this->sound.setBuffer(this->buffer);
						this->sound.play();
						break;
					case 3:
						if (!this->buffer.loadFromFile("piano1.wav"))
							std::cout << "sound error";

						this->sound.setBuffer(this->buffer);
						this->sound.play();
						break;


					}
					

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//gain points
					this->points += 10;
					std::cout << "  points: " << this->points << "   Health:" << this->health;
				}


			}


		}
		
		}
	else 
	{
		this->mouseHeld = false;
	}

		
	

}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->uiText.setString(ss.str());
}



void Game::update()
{
	this->pollEvents();

	if (!this->endGame) 
	{
		this->updateMousePosition();

		this->updateText();

		this->updateEnemies();
	}
	//End game condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies) {
		target.draw(e);
	}
}

void Game::render()
{
	/*
		Renders the game objects
		Clear old frame
		render objects
		display frame in window
	*/
	this->window->clear(sf::Color::White);
	//Draw game objects

	this->renderEnemies(*this->window);
	this->renderText(*this->window);

	this->window->display();
}
