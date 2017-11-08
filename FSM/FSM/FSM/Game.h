//@author Greg Cahill
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "State.h"
#include "Animation.h"
class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	void jump();
	void climb();
	void sword();
	void shield();
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	sf::RectangleShape rect;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_jumpUpTexture; // texture used for Jumping up texture
	sf::Texture m_jumpDownTexture; // Texture used for jumping down texture
	sf::Texture m_swordingTexture; //Texture used for swording
	sf::Texture m_shieldingTexture; //Texture used for shielding
	sf::Texture m_climbingTexture; //texture used for climbing
	sf::Texture m_idleTexture; //texture used for idle
	sf::Sprite m_squareSprite; // sprite used for the square shape
	bool m_exitGame; // control exiting game
	Animation fsm; int stateSwitcher = 0;
	int durationCounter = 0;

	bool jumpPressed = false;
	bool climbPressed = false;
	bool swordPressed = false;
	bool shieldPressed = false;
	bool falling = false;
};

#endif // !GAME

