//@author Greg Cahill

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "FSM" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}


Game::~Game()
{
}


void Game::run()
{
	//This is the game loop, will update based on timeperfram (60 ideally, or 144 if you have a beast of a rig)

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
void Game::jump()
{
	//This if statement Will check if the duration counter is less than
	//or equal to 120, if the jump key has been pressed an all other possible states are false.
	//If yes, it will set its state to jumping by accessing it via the fsm (finite state machine), decrease the sprites y pos until
	//durationCounter >= 60, then will move back down. The sprite changes approperiatly
	if(durationCounter <= 120 
		&& jumpPressed == true 
		&& climbPressed == false
		&& swordPressed == false
		&& shieldPressed == false)
	{
		if (durationCounter < 60)
		{
			rect.setPosition(rect.getPosition().x, rect.getPosition().y - 2);
			rect.setTexture(&m_jumpUpTexture);
		}
		fsm.jumping();
		if (durationCounter >= 60)
		{
			rect.setPosition(rect.getPosition().x, rect.getPosition().y + 2);
			rect.setTexture(&m_jumpDownTexture);
		}
		if (durationCounter == 120)
		{
			//Once duration counter does reach 120, this resets it to zero (120 is around 2 seconds)
			rect.setPosition(700, 520);
			jumpPressed = false;
			durationCounter = 0;
			std::system("CLS");
		}
	}
}
void Game::climb()
{
	//This checks if the climb key has been pressed and all other states are false
	//Then sets state to climbing via the fsm (finite state machine).
	//sprite moves up the screen by decreasing the Y value
	if (climbPressed == true 
		&& jumpPressed == false
		&& swordPressed == false 
		&& shieldPressed == false)
	{
		rect.setPosition(rect.getPosition().x, rect.getPosition().y - 2);
		fsm.climbing();
		rect.setTexture(&m_climbingTexture);
	}
	else 
	{
		std::system("CLS");
	}
}
void Game::sword()
{
	//This if statement Will check if the duration counter is less than
	//or equal to 30, if the swording key has been pressed an all other possible states are false.
	//If yes, it will set its state to swording by accessing it via the fsm (finite state machine), 
	//. The sprite changes approperiatly to the sword sprite
	if (durationCounter <= 30
		&& swordPressed == true 
		&& jumpPressed == false 
		&& climbPressed == false
		&& shieldPressed == false)
	{
		fsm.swording();
		rect.setTexture(&m_swordingTexture);
		if (durationCounter == 30)
		{
			//This is a reset fucntion that once duration counter reaches 30 (about half a second)
			//duration counter will reset to zero and sword key press will return to false
			swordPressed = false;
			durationCounter = 0;
			std::system("CLS");
		}
	}
}
void Game::shield()
{
	//This checks if the shield key has been pressed and all other states are false
	//Then sets state to shielding via the fsm (finite state machine).
	//This sets the sprite to shielding (funnily enough, if you mach the shield key, the sprite T-bags)
	if (shieldPressed == true
		&& climbPressed == false
		&& jumpPressed == false
		&& swordPressed == false)
	{
		rect.setTexture(&m_shieldingTexture);
		fsm.shielding();
	}
	else 
	{
		std::system("CLS");
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}

		//The following two if checks will check if the climb or shield key is not pressed, if they aren't
		//They will be returned to false
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			climbPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			shieldPressed = false;
		}
		//If a key is pressed and the sprite isnt currently falling, it will enter this big chunk of code
		if (sf::Event::KeyPressed == event.type && !falling) //user key press
		{
			//Exits the game if you press escape
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
			//Checks if the climb key is pressed and all other staes are false
			//If yes, sets climbPressed to true
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) 
				&& swordPressed == false
				&& jumpPressed == false
				&& shieldPressed == false)
			{
				climbPressed = true;
			}
			//Checks if the shield key is pressed and all other staes are false
			//If yes, sets shieldPressed to true
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
				&& swordPressed == false
				&& jumpPressed == false
				&& climbPressed == false)
			{
				shieldPressed = true;
			}
			//Checks if the jump key is pressed and all other staes are false
			//If yes, sets jumpPressed to true
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
				&& swordPressed == false 
				&& climbPressed == false
				&& shieldPressed == false)
			{
				jumpPressed = true;
			}
			//Checks if the sword key is pressed and all other staes are false
			//If yes, sets swordPressed to true
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) 
				&& jumpPressed == false
				&& climbPressed == false
				&& shieldPressed == false)
			{
				swordPressed = true;
			}

		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{

	//The below statement checks if all states are false
	//If yes and the object isnt above its base Y position (520), its sprite and state will be idle
	//If yes, but it is above its base Y position, its sprite will be the same as 'jumping down' and its
	//Y val will decrease until it reaches a state where it can return to idle
	if (!shieldPressed &&
		!climbPressed &&
		!jumpPressed &&
		!swordPressed)
	{
		if (rect.getPosition().y < 520 && durationCounter <= 0)
		{
			falling = true;
			rect.setPosition(rect.getPosition().x, rect.getPosition().y + 2);
			rect.setTexture(&m_jumpDownTexture);
		}
		else
		{
			falling = false;
			rect.setTexture(&m_idleTexture);
		}

	}

	//If the sprite isnt currently falling,
	//Will enter this chunk of code
	if (!falling) 
	{
		//If jump or sowrd key has been pressed, duration counter will increase
		if (jumpPressed == true || swordPressed == true)
		{
			durationCounter++;
		}
		//Enters jump function
		jump();
		//Checks if climb key has been pressed, then enters climb
		if (climbPressed)
		{
			climb();
		}
		//Enters sword fucntion
		sword();
		//checks if shield key has been pressed, then enters shield function
		if (shieldPressed)
		{
			shield();
		}
	}
	
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(rect);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	//Setting up our font to be used to display the controls
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Space to jump\nC to climb\nE to sword\nQ to shield");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(25);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	//Loading of the needed textures, and sets up the rectangle shape the texture will be applied to
	
	rect.setSize(sf::Vector2f(80, 80));
	rect.setPosition(700, 520);
	if (!m_jumpUpTexture.loadFromFile("ASSETS\\IMAGES\\Jump up.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Texture" << std::endl;
	}

	if (!m_jumpDownTexture.loadFromFile("ASSETS\\IMAGES\\jump down.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Texture" << std::endl;
	}

	if (!m_swordingTexture.loadFromFile("ASSETS\\IMAGES\\swording.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Texture" << std::endl;
	}

	if (!m_shieldingTexture.loadFromFile("ASSETS\\IMAGES\\shielding.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Texture" << std::endl;
	}

	if (!m_idleTexture.loadFromFile("ASSETS\\IMAGES\\idle.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Texture" << std::endl;
	}

	if (!m_climbingTexture.loadFromFile("ASSETS\\IMAGES\\Climbing.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Texture" << std::endl;
	}
	
}
