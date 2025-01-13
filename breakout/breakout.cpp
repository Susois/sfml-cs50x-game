#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Window.hpp>

#include<iostream>
#include<string>
#include<vector>
#include<ctime>

// physicalscreen
const int window_width = 1000;
const int window_height = 512;

enum GAME_state {
	menu,
	play,
	ranking, // chua co
	endscreen // chua co
};

class paddle {
public:
	sf::RectangleShape shape;
	float velocity = 0.0f;
	const float speed = 400.0f;
	paddle(float x, float y) {
		shape.setSize({ 100.f,20.f });
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(x, y);
	}

	void update(float dt, float windowwidth) {
		shape.move(velocity * dt, 0.0f);
		if (shape.getPosition().x < 0) shape.setPosition(0, shape.getPosition().y);
		if (shape.getPosition().x + shape.getSize().x > windowwidth)
			shape.setPosition(windowwidth - shape.getSize().x, shape.getPosition().y);
	}

	void moveleft()		{ velocity = -speed; }
	void moveright()	{ velocity = speed; }
	void stop()			{ velocity = 0.0f; }
	
	sf::FloatRect getbound() const { return shape.getGlobalBounds(); }

};


class ball {
public:
	sf::CircleShape shape;
	sf::Vector2f velocity = { 200.f,-200.f };
	ball(float x, float y) {
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(x, y);
	}

	void update(float dt, float windowwidth, float windowheight) {
		shape.move(velocity * dt);
		if (shape.getPosition().x <= 0 || shape.getPosition().x + shape.getRadius() * 2 >= windowwidth) {
			velocity.x = -velocity.x;
		}
		if (shape.getPosition().y <= 0) velocity.y = -velocity.y;
 	}

	void reset(float x, float y) {
		shape.setPosition(x, y);
		velocity = { 200.f,-200.f };
	}
	sf::FloatRect getbound() const {
		return shape.getGlobalBounds();
	}
};

class Brick {
public:
	sf::RectangleShape shape;
	bool destroyed = false;
	Brick(float x, float y, float width, float height) {
		shape.setSize({ width, height });
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(x, y);
	}
	sf::FloatRect getbounds() const {
		return shape.getGlobalBounds();
	}
};

class level {
public:
	std::vector<Brick> bricks;

	void loadlevel(int rows, int cols, float windowwidth, float brickheight) {
		float brickwidth = windowwidth / cols;
		float xoffset = (windowwidth - (brickwidth * cols)) / 2;
		for (int row = 0; row < rows; row++) {
			for(int col =0; col <cols; col++)
				bricks.emplace_back(xoffset + col * brickwidth, row * brickheight, brickwidth - 5.f, brickheight - 5.f);
		}
	}

	void render(sf::RenderWindow& window) {
		for (auto& brick : bricks) {
			if (!brick.destroyed) window.draw(brick.shape);
		}
	}

};

class Game {
private:
	sf::RenderWindow window;
	sf::Font font;
	sf::Text scoretext;
	sf::Text startbutton;
	sf::Text pausebutton;
	sf::Text rankingbutton;
	sf::Text menubutton; // endscreen
	GAME_state gamestates = menu;
	sf::Clock clock;

	paddle paddlesgame;
	ball ballgame;
	level levelgame;
	int score = 0;
	int lives = 3;

protected:
	void handleInput() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)window.close();

			if (gamestates == menu) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
					if (startbutton.getGlobalBounds().contains(mousepos)) {
						gamestates = play;
					}
					else if (rankingbutton.getGlobalBounds().contains(mousepos)) {
						gamestates = ranking;
					}
				}
			}
			else if (gamestates == play) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))paddlesgame.moveleft();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))paddlesgame.moveright();
				else paddlesgame.stop();
			}
			else if (gamestates == endscreen) {
				sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
				if (menubutton.getGlobalBounds().contains(mousepos)) {
					gamestates = menu;
				}
			}
		}
	}
	void update(float dt) {
		if (gamestates == play) {
			// do something

			paddlesgame.update(dt, window.getSize().x);
			ballgame.update(dt, window.getSize().x, window.getSize().y);

			//check ball collision with paddle
			if (ballgame.getbound().intersects(paddlesgame.getbound()))
				ballgame.velocity.y = -ballgame.velocity.y;

			// check ball collision with bricks
			for (auto& brick_game : levelgame.bricks) {
				if (!brick_game.destroyed && ballgame.getbound().intersects(brick_game.getbounds())) {
					brick_game.destroyed = true;
					ballgame.velocity.y = -ballgame.velocity.y;
					score ++;
					break;
				}
			}

			//check if ball hits the bottom
			if (ballgame.shape.getPosition().y > window.getSize().y) {
				lives--;
				ballgame.reset(400.f, 300.f);
				paddlesgame.shape.setPosition(450.f, window_height-30.f);
			}

			if (lives <= 0) {
				std::cout << "Game Over! Final Score: " << score << std::endl;
				gamestates = endscreen;
			}
		}

	}
	void render() {
		window.clear();
		
		//logic
		if (gamestates == menu) {
			/*background.render(window);
			ground.render(window);*/
			window.draw(startbutton);
			window.draw(rankingbutton);
		}
		else if (gamestates == play) {
			//background.render(window);
			//ground.render(window);
			window.draw(paddlesgame.shape);
			window.draw(ballgame.shape);
			levelgame.render(window);
		}
		window.display();

	}


public:
	Game()
		: window(sf::VideoMode(window_width, window_height), "BreakOut", sf::Style::Close),
		paddlesgame(350.f, 550.f),
		ballgame(400.f,300.f),
		gamestates(menu)
	{
		window.setFramerateLimit(60);
		font.loadFromFile("data/fonts/font.ttf");

		scoretext.setFont(font);
		scoretext.setString("Score: ");
		scoretext.setCharacterSize(32);
		scoretext.setFillColor(sf::Color::Red);
		scoretext.setPosition(10, 10);

		startbutton.setFont(font);
		startbutton.setString("Start");
		startbutton.setCharacterSize(40);
		startbutton.setFillColor(sf::Color::Red);
		startbutton.setPosition(window_width / 2 - 100, window_height / 2 - 100);

		rankingbutton.setFont(font);
		rankingbutton.setString("Ranking");
		rankingbutton.setCharacterSize(40);
		rankingbutton.setFillColor(sf::Color::Red);
		rankingbutton.setPosition(window_width / 2 - 100, window_height / 2 + 100);


		//set level
		levelgame.loadlevel(5, 10, 800.f, 30.f);

	}
	void run() {
		while (window.isOpen()) {
			handleInput();
			update(clock.restart().asSeconds());
			render();
		}
	}
};

int main() {
	srand(static_cast<unsigned>(time(0)));
	Game game;
	game.run();
	return 0;
}