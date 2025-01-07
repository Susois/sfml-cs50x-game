////#include<SFML\Graphics.hpp>
////#include<iostream>
////int main() {
////	sf::RenderWindow window(sf::VideoMode({ 600,900 }), "sfml application");
////
////	window.setFramerateLimit(60);
////	window.setKeyRepeatEnabled(false);
////	bool enter = false;
////	bool left = false;
////	bool right = false;
////	int numberrights = 100;
////	int cntleft = 0;
////	int mousex = 0;
////	bool lefarrow = 0, rightarrow = 0;
////
////	while (window.isOpen()) {
////		while (const std::optional event = window.pollEvent()) {
////			if (event->is<sf::Event::Closed>())window.close();
////			if (event->is<sf::Event::KeyReleased>() && event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Enter)
////			{
////				enter = true;
////			}
////			if (event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right)
////			{
////				right = true;
////			}
////			if (event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
////			{
////				left = true;
////			}
////			if (left) {
////				if (event->is<sf::Event::MouseMoved>()) {
////					mousex = event->getIf<sf::Event::MouseMoved>()->position.x;
////					if (mousex < 200)window.close();
////					std::cout << "\nleftclick: " << ++cntleft << "\npositions x: " << mousex<<'\n';
////					left = false;
////				}
////			}
////			if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
////				lefarrow = true;
////			}
////			if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
////				rightarrow = true;
////			}
////			if (lefarrow && rightarrow) {
////				std::cout << "hahahahahah";
////				lefarrow = false;
////				rightarrow = false;
////			}
////		}
////		//logic
////		if (enter) {
////			std::cout << "enter da dc nha\n";
////			enter = false;
////		}
////		if (right) {
////			std::cout << "\nchuot phai dc nhap";
////			std::cout << "\nnumberright = " << --numberrights;
////			right = false;
////		}
////		/*if (left) {
////			std::cout << "\nleftclick: " << ++cntleft<<"\nposition x: "<<mousex;
////			left = false;
////		}*/
////
////		//render
////		window.clear();
////		window.display();
////	}
////}
//
//
//// Flappy Bird in C++ with SFML
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//
//// Constants
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const float GRAVITY = 800.0f;
//const float JUMP_VELOCITY = -300.0f;
//const float PIPE_SPEED = 200.0f;
//const float PIPE_SPAWN_INTERVAL = 1.5f;
//
//// Utility function for random floats
//float getRandomFloat(float min, float max) {
//    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
//}
//
//// Bird class
//class Bird {
//private:
//    sf::Sprite birdSprite;
//    sf::Texture birdTexture;
//    float velocity;
//
//public:
//    Bird(const std::string& textureFile, float startX, float startY) 
//    {
//        birdTexture.loadFromFile(textureFile);
//        birdSprite.setTexture(birdTexture);
//        birdSprite.setPosition({ startX, startY });
//        velocity = 0;
//    }
//
//    void update(float dt) {
//        velocity += GRAVITY * dt;
//        birdSprite.move({ 0, velocity * dt });
//    }
//
//    void jump() {
//        velocity = JUMP_VELOCITY;
//    }
//
//    void render(sf::RenderWindow& window) {
//        window.draw(birdSprite);
//    }
//
//    sf::FloatRect getBounds() const {
//        return birdSprite.getGlobalBounds();
//    }
//
//    void resetPosition(float x, float y) {
//        birdSprite.setPosition({ x, y });
//        velocity = 0;
//    }
//};
//
//// Pipe class
//class Pipe {
//private:
//    sf::Sprite pipeSprite;
//    sf::Texture pipeTexture;
//    bool isTop;
//
//public:
//    Pipe(const std::string& textureFile, float startX, float startY, bool top)
//        : isTop(top) {
//        pipeTexture.loadFromFile(textureFile);
//        pipeSprite.setTexture(pipeTexture);
//        pipeSprite.setPosition({ startX, startY });
//        if (isTop) {
//            pipeSprite.setScale(1, -1); // Flip the pipe if it's the top pipe
//        }
//    }
//
//    void update(float dt) {
//        pipeSprite.move({ -PIPE_SPEED * dt, 0 });
//    }
//
//    void render(sf::RenderWindow& window) {
//        window.draw(pipeSprite);
//    }
//
//    sf::FloatRect getBounds() const {
//        return pipeSprite.getGlobalBounds();
//    }
//
//    float getX() const {
//        return pipeSprite.getPosition().x;
//    }
//};
//
//// PipePair class
//class PipePair {
//private:
//    Pipe topPipe;
//    Pipe bottomPipe;
//    bool scored;
// 
//public:
//    PipePair(float startX, float gapY, float gapHeight)
//        : topPipe("pipe.png", startX, gapY - gapHeight / 2, true),
//        bottomPipe("pipe.png", startX, gapY + gapHeight / 2, false),
//        scored(false) {}
//
//    void update(float dt) {
//        topPipe.update(dt);
//        bottomPipe.update(dt);
//    }
//
//    void render(sf::RenderWindow& window) {
//        topPipe.render(window);
//        bottomPipe.render(window);
//    }
//
//    bool isOffScreen() const {
//        return topPipe.getX() + topPipe.getBounds().width < 0;
//    }
//
//    bool collidesWith(const Bird& bird) const {
//        return topPipe.getBounds().intersects(bird.getBounds()) ||
//            bottomPipe.getBounds().intersects(bird.getBounds());
//    }
//
//    bool isScored() const {
//        return scored;
//    }
//
//    void setScored(bool value) {
//        scored = value;
//    }
//
//    float getX() const {
//        return topPipe.getX();
//    }
//};
//
//// Main Game class
//class Game {
//private:
//    sf::RenderWindow window;
//    Bird bird;
//    std::vector<PipePair> pipes;
//    sf::Clock clock;
//    float timeSinceLastPipe;
//    int score;
//    sf::Font font;
//    sf::Text scoreText;
//
//public:
//    Game()
//        : window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Flappy Bird", sf::Style::Close),
//        bird("bird.png", 100, WINDOW_HEIGHT / 2),
//        timeSinceLastPipe(0),
//        score(0){
//        window.setFramerateLimit(60);
//        font.openFromFile("font.ttf");
//        scoreText.setFont(font);
//        scoreText.setCharacterSize(32);
//        scoreText.setFillColor(sf::Color::White);
//        scoreText.setPosition({ 10, 10 });
//        }
//
//    void run() {
//        while (window.isOpen()) {
//            handleInput();
//            update();
//            render();
//        }
//    }
//
//private:
//    void handleInput() {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
//                bird.jump();
//            }
//        }
//    }
//
//    void update() {
//        float dt = clock.restart().asSeconds();
//        bird.update(dt);
//
//        // Update pipes
//        timeSinceLastPipe += dt;
//        if (timeSinceLastPipe > PIPE_SPAWN_INTERVAL) {
//            float gapY = getRandomFloat(150, WINDOW_HEIGHT - 150);
//            pipes.emplace_back(WINDOW_WIDTH, gapY, 200);
//            timeSinceLastPipe = 0;
//        }
//
//        for (auto& pipe : pipes) {
//            pipe.update(dt);
//        }
//
//        // Remove off-screen pipes
//        pipes.erase(
//            std::remove_if(pipes.begin(), pipes.end(), [](const PipePair& pipe) {
//                return pipe.isOffScreen();
//                }),
//            pipes.end());
//
//        // Check collisions
//        for (auto& pipe : pipes) {
//            if (pipe.collidesWith(bird)) {
//                resetGame();
//                return;
//            }
//
//            if (!pipe.isScored() && bird.getBounds().left > pipe.getX()) {
//                pipe.setScored(true);
//                score++;
//            }
//        }
//
//        // Update score text
//        scoreText.setString("Score: " + std::to_string(score));
//    }
//
//    void render() {
//        window.clear();
//
//        bird.render(window);
//        for (auto& pipe : pipes) {
//            pipe.render(window);
//        }
//        window.draw(scoreText);
//
//        window.display();
//    }
//
//    void resetGame() {
//        bird.resetPosition(100, WINDOW_HEIGHT / 2);
//        pipes.clear();
//        score = 0;
//    }
//};
//
//int main() {
//    srand(static_cast<unsigned>(time(0)));
//    Game game;
//    game.run();
//    return 0;
//}


#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<math.h>

class pipe {
private:
	sf::Sprite pipesprite;
	sf::Texture	pipetexture;
	bool istop;
public:
	pipe(const std::string& texturefile, float startx, float starty, bool top)
		: istop(top)
	{
		pipetexture.loadFromFile("data/pipe.png");
		pipesprite.setTexture(pipetexture);
		pipesprite.setPosition(startx, starty);
		if (istop) {
			pipesprite.setScale(1, -1);
		}
	}
};

class pipepair {
private:
	
};

int main()
{

}