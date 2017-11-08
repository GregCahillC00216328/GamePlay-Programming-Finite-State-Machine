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
			rect.setPosition(700, 520);
			jumpPressed = false;
			durationCounter = 0;
			std::system("CLS");
		}
	}
}
void Game::climb()
{
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
			swordPressed = false;
			durationCounter = 0;
			std::system("CLS");
		}
	}
}
void Game::shield()
{
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
/// and user :: Don't do game update here
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
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			climbPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			shieldPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jumpPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			swordPressed = false;
		}
		if (sf::Event::KeyPressed == event.type && !falling) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) 
				&& swordPressed == false
				&& jumpPressed == false
				&& shieldPressed == false)
			{
				climbPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
				&& swordPressed == false
				&& jumpPressed == false
				&& climbPressed == false)
			{
				shieldPressed = true;
			}
			
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			//{
			//	rect.setPosition(rect.getPosition().x, rect.getPosition().y - 2);
			//}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
				&& swordPressed == false 
				&& climbPressed == false
				&& shieldPressed == false)
			{
				jumpPressed = true;
			}
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

	if (!shieldPressed &&
		!climbPressed &&
		!jumpPressed &&
		!swordPressed)
	{
		if (rect.getPosition().y < 520)
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
	if (!falling) 
	{
		if (jumpPressed == true || swordPressed == true)
		{
			durationCounter++;
		}

		jump();
		if (climbPressed)
		{
			climb();
		}
		sword();
		if (shieldPressed)
		{
			shield();
		}
	}
	
	//if (stateSwitcher == 0 && durationCounter >=60) {
	//	fsm.jumping();
	//	stateSwitcher = 1;
	//	durationCounter = 0;
	//}
	//else if(durationCounter >=60){
	//	fsm.climbing();
	//	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//	stateSwitcher = 0;
	//	durationCounter = 0;
	//}
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
	//rect.setFillColor(sf::Color::Blue);
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
