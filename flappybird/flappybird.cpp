#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Window.hpp>

#include<iostream>
#include<string>
#include<vector>
#include<ctime>	

//physical screen
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 512;

//VIRTUAL RESOLUTION 
const int VIRTUAL_WIDTH = 512;
const int VIRTUAL_HEIGHT = 288;

//BACKGROUND SCROLL 
const int backgound_scroll = 0;
const int ground_scroll = 0;
const int background_scroll_speed = 60;
const int ground_scroll_speed = 30;
// bird
const float GRAVITY = 800.f;
const float JUMP_VELOCITY = -300.f;
// pipe
const float PIPE_SPEED = 200.f;
const float PIPE_SPAWN_INTERVAL = 1.5f;




//background
class background {
private:
    sf::Sprite backgroundsprite;
    sf::Texture backgroundtexture;
public:
    background(const std::string& texturefile) {
        backgroundtexture.loadFromFile(texturefile);
        backgroundsprite.setTexture(backgroundtexture);
    }

    void update(float dt) {
        backgroundsprite.move(0, -background_scroll_speed);
    }

};

// getrandom
float getRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Bird class
class Bird {
private:
    sf::Sprite birdSprite;
    sf::Texture birdTexture;
    float velocity;

public:
    Bird(const std::string& textureFile, float startX, float startY) 
    {
        birdTexture.loadFromFile(textureFile);
        birdSprite.setTexture(birdTexture);
        birdSprite.setPosition({ startX, startY });
        velocity = 0;
    }

    void update(float dt) {
        velocity += GRAVITY * dt;
        birdSprite.move({ 0, velocity * dt });
    }

    void jump() {
        velocity = JUMP_VELOCITY;
    }

    void render(sf::RenderWindow& window) {
        window.draw(birdSprite);
    }

    sf::FloatRect getBounds() const {
        return birdSprite.getGlobalBounds();
    }

    void resetPosition(float x, float y) {
        birdSprite.setPosition({ x, y });
        velocity = 0;
    }
};

// Pipe class
class Pipe {
private:
    sf::Sprite pipeSprite;
    sf::Texture pipeTexture;
    bool isTop;

public:
    //Pipe(const std::string& texturefile, float startX, float startY, bool top)
    Pipe(sf::Texture& texture, float startX, float startY, bool top)
        : isTop(top) {
        /*pipeTexture.loadFromFile(textureFile);
        pipeSprite.setTexture(pipeTexture);*/
        pipeSprite.setTexture(texture);
        pipeSprite.setPosition({ startX, startY });
        if (isTop) {
            pipeSprite.setScale(1, -1); // Flip the pipe 
        }
    }

    void update(float dt) {
        pipeSprite.move({ -PIPE_SPEED * dt, 0 });
    }

    void render(sf::RenderWindow& window) {
        window.draw(pipeSprite);
    }

    sf::FloatRect getBounds() const {
        return pipeSprite.getGlobalBounds();
    }

    float getX() const {
        return pipeSprite.getPosition().x;
    }
};

// PipePair class
class PipePair {
private:
    Pipe topPipe;
    Pipe bottomPipe;
    bool scored;
 
public:
    //PipePair(const std::string& texture,float startX, float gapY, float gapHeight)
    PipePair(sf::Texture& texture, float startX, float gapY, float gapHeight)
        /*: topPipe("data/pipe.png", startX, gapY - gapHeight / 2, true),
        bottomPipe("data/pipe.png", startX, gapY + gapHeight /2 , false),*/
        : topPipe(texture, startX, gapY - gapHeight/2, true),
        bottomPipe(texture,startX, gapY + gapHeight/2, false),
        scored(false) {}

    void update(float dt) {
        topPipe.update(dt);
        bottomPipe.update(dt);
    }

    void render(sf::RenderWindow& window) {
        topPipe.render(window);
        bottomPipe.render(window);
    }

    bool isOffScreen() const {
        return topPipe.getX() + topPipe.getBounds().width < 0;
    }

    bool collidesWith(const Bird& bird) const {
        return topPipe.getBounds().intersects(bird.getBounds()) ||
            bottomPipe.getBounds().intersects(bird.getBounds());
    }

    bool isScored() const {
        return scored;
    }

    void setScored(bool value) {
        scored = value;
    }

    float getX() const {
        return topPipe.getX();
    }
};

// Main Game class
class Game {
private:
    sf::RenderWindow window;
    Bird bird;
    std::vector<PipePair> pipes;
    sf::Clock clock;
    float timeSinceLastPipe;
    int score;
    sf::Font font;
    sf::Text scoreText;
    sf::Texture pipetexture;
    sf::Texture background_texture;
public:
    Game()
        : window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Flappy Bird", sf::Style::Close),
        bird("data/bird.png", 100, WINDOW_HEIGHT / 2),
        timeSinceLastPipe(0),
        score(0){
        window.setFramerateLimit(60);
        pipetexture.loadFromFile("data/pipe.png");
        background_texture.loadFromFile("data/background.png");
        font.loadFromFile("data/font.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(32);
        scoreText.setFillColor(sf::Color::Red);
        scoreText.setPosition({ 10, 10 });
        }

    void run() {
        while (window.isOpen()) {
            handleInput();
            update();
            render();
        }
    }

protected:
    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                bird.jump();
            }
        }
    }

    void update() {
        float dt = clock.restart().asSeconds();
        bird.update(dt);

        // Update pipes
        timeSinceLastPipe += dt;
        if (timeSinceLastPipe > PIPE_SPAWN_INTERVAL) {
            float gapY = getRandomFloat(150, WINDOW_HEIGHT-150);
            //pipes.emplace_back(WINDOW_WIDTH, gapY, 200);
            pipes.emplace_back(pipetexture, WINDOW_WIDTH, gapY, 200);
            timeSinceLastPipe = 0;
        }

        for (auto& pipe : pipes) {
            pipe.update(dt);
        }

        // Remove off-screen pipes
        pipes.erase(
            std::remove_if(pipes.begin(), pipes.end(), [](const PipePair& pipe) {
                return pipe.isOffScreen();
                }),
            pipes.end());

        // Check collisions
        for (auto& pipe : pipes) {
            if (pipe.collidesWith(bird)) {
                resetGame();
                return;
            }

            if (!pipe.isScored() && bird.getBounds().left > pipe.getX()) {
                pipe.setScored(true);
                score++;
            }
        }

        // Update score text
        scoreText.setString("Score: " + std::to_string(score));
    }

    void render() {
        window.clear();

        bird.render(window);
        for (auto& pipe : pipes) {
            pipe.render(window);
        }
        window.draw(scoreText);

        window.display();
    }

    void resetGame() {
        bird.resetPosition(100, WINDOW_HEIGHT / 2);
        pipes.clear();
        score = 0;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    Game game;
    game.run();
    return 0;
}
