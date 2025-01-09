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

//BACKGROUND SCROLL 
const int background_scroll_speed = 60;
// bird
const float GRAVITY = 800.f;
const float JUMP_VELOCITY = -300.f;
// pipe
const float PIPE_SPEED = 200.f;
const float PIPE_SPAWN_INTERVAL = 1.5f;


// enum
enum gamestates {
    menu, 
    play,
    ranking,
    pause,
    endscreen
};


//background
class background {
private:
    sf::Sprite backgroundsprite1;
    sf::Sprite backgroundsprite2;
    sf::Texture backgroundtexture;
public:
    background(const std::string& texturefile) {
        backgroundtexture.loadFromFile(texturefile);
        backgroundsprite1.setTexture(backgroundtexture);
        backgroundsprite2.setTexture(backgroundtexture);
        //set background to ngang với cửa sổ window
        
        // lấy kích thước cửa sổ window
        sf::Vector2u texture = backgroundtexture.getSize();

        //scale để vừa với cửa sổ
        float scalex = static_cast<float>(WINDOW_WIDTH) / texture.x;
        float scaley = static_cast<float>(WINDOW_HEIGHT) / texture.y;

        backgroundsprite1.setScale(scalex, scaley);
        backgroundsprite2.setScale(scalex, scaley);

        backgroundsprite1.setPosition(scalex, scaley);
        backgroundsprite2.setPosition(scalex, scaley);

        // đặt vị trí 2 sprite liền kề nhau

        backgroundsprite1.setPosition(0, 0);
        backgroundsprite2.setPosition(static_cast<float>(texture.x) * scalex, 0);

    }
    
    /*void update(float dt) {
        backgroundsprite.move( -background_scroll_speed * dt ,0);
    }
    void render(sf::RenderWindow& window) {
        window.draw(backgroundsprite);
    }
    void resetposition(float startx, float starty) {
        backgroundsprite.setPosition(startx, starty);
    }
    sf::FloatRect getbound()const {
        return backgroundsprite.getGlobalBounds();
    }*/

    void update(float dt) {
        // di chuyen 2 sprite sang trai
        float movement = -background_scroll_speed * dt;
        backgroundsprite1.move(movement, 0);
        backgroundsprite2.move(movement, 0);

        // kiem tra neu sprite ra khoi man hinh, dat lai vi tri
        if (backgroundsprite1.getPosition().x + backgroundsprite1.getGlobalBounds().width <= 0) {
            backgroundsprite1.setPosition(
                backgroundsprite2.getPosition().x + backgroundsprite2.getGlobalBounds().width, 0
            );
        }
        if (backgroundsprite2.getPosition().x + backgroundsprite2.getGlobalBounds().width <= 0) {
            backgroundsprite2.setPosition(
                backgroundsprite1.getPosition().x + backgroundsprite1.getGlobalBounds().width, 0
            );
        }
    }
    void render(sf::RenderWindow& window) {
        window.draw(backgroundsprite1);
        window.draw(backgroundsprite2);
    }

    void resetposition() {
        backgroundsprite1.setPosition(0, 0);
        backgroundsprite2.setPosition(backgroundsprite1.getGlobalBounds().width, 0);
    }

};

//ground
class ground {
private: 
    sf::Texture groundtexture;
    sf::Sprite groundsprite1;
    sf::Sprite groundsprite2;
public:
    ground(const sf::String& texturefile) {
        groundtexture.loadFromFile(texturefile);
        groundsprite1.setTexture(groundtexture);
        groundsprite2.setTexture(groundtexture);

        // lay kich thuoc cua so window
        sf::Vector2u texture = groundtexture.getSize();

        //lay scale
        //float scalex = static_cast<float>(WINDOW_WIDTH) / texture.x;
        float scalex = static_cast<float>(WINDOW_WIDTH) / texture.x;

        float scaley = texture.y /3;
        

        groundsprite1.setScale(scalex, scaley);
        groundsprite2.setScale(scalex, scaley);

        groundsprite1.setPosition(scalex, scaley);
        groundsprite2.setPosition(scalex, scaley);

        groundsprite1.setPosition(0,WINDOW_HEIGHT * 6/7);
        groundsprite2.setPosition(static_cast<float>(texture.x) * scalex, WINDOW_HEIGHT * 6 / 7 );
        //groundsprite2.setPosition(static_cast<float>(texture.x) * 1, WINDOW_HEIGHT / 2);

    }
    void update(float dt) {
        float movement = -background_scroll_speed * dt;
        groundsprite1.move(movement, WINDOW_HEIGHT*6/7);
        groundsprite2.move(movement, WINDOW_HEIGHT*6/7);

        if (groundsprite1.getPosition().x + groundsprite1.getGlobalBounds().width <= 0) {
            groundsprite1.setPosition(
                groundsprite2.getPosition().x + groundsprite2.getGlobalBounds().width, 0);
        }

        if (groundsprite2.getPosition().x + groundsprite2.getGlobalBounds().width <= 0) {
            groundsprite2.setPosition(
                groundsprite2.getPosition().x + groundsprite2.getGlobalBounds().width, 0);
        }
        
    }
    void render(sf::RenderWindow& window) {
        window.draw(groundsprite1);
        window.draw(groundsprite2);
    }
    void resetpositon() {
        groundsprite1.setPosition(0, WINDOW_HEIGHT * 6/7);
        groundsprite2.setPosition(groundsprite1.getGlobalBounds().width, WINDOW_HEIGHT*6/7);
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
        : topPipe(texture, startX, gapY - gapHeight/3, true),
        bottomPipe(texture,startX, gapY + gapHeight/3, false),
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


class Game {
private:
    sf::RenderWindow window;
    Bird bird;
    std::vector<PipePair> pipes;
    sf::Clock clock;
    float timeSinceLastPipe;
    int score;
    sf::Font font;
    sf::Font fontbutton;
    sf::Text scoreText;
    sf::Texture pipetexture;
    sf::Texture background_texture;
    sf::Texture ground_texture;
    sf::Text startbutton;
    sf::Text pausebutton;
    sf::Text rankingbutton;
    sf::Text menubuttontext;
    sf::Text scoretextend;
    background back_ground;
    ground ground_;
    gamestates game_state;

public:
    Game()
        : window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Flappy Bird", sf::Style::Close),
        game_state(menu),
        back_ground("data/background.png"),
        ground_("data/ground.png"),
        bird("data/bird.png", 100, WINDOW_HEIGHT / 2),
        timeSinceLastPipe(0),
        score(0) {

        window.setFramerateLimit(60);

        fontbutton.loadFromFile("data/flappy.ttf");
        font.loadFromFile("data/font.ttf");
        pipetexture.loadFromFile("data/pipe.png");

        scoreText.setFont(font);
        scoreText.setCharacterSize(32);
        scoreText.setFillColor(sf::Color::Red);
        scoreText.setPosition({ 10, 10 });

        startbutton.setFont(fontbutton);
        startbutton.setString("Start");
        startbutton.setCharacterSize(32);
        startbutton.setFillColor(sf::Color::Red);
        startbutton.setPosition(WINDOW_WIDTH / 2 - 100, 150);

        pausebutton.setFont(fontbutton);
        pausebutton.setString("Pause (null)");
        pausebutton.setCharacterSize(32);
        pausebutton.setFillColor(sf::Color::Red);
        pausebutton.setPosition(WINDOW_WIDTH / 2 - 100, 250);

        rankingbutton.setFont(fontbutton);
        rankingbutton.setString("Ranking (null)");
        rankingbutton.setCharacterSize(32);
        rankingbutton.setFillColor(sf::Color::Red);
        rankingbutton.setPosition(WINDOW_WIDTH / 2 - 100, 350);

        scoretextend.setFont(fontbutton);
        scoretextend.setCharacterSize(72);
        scoretextend.setString("Your Score: " + std::to_string(score));
        scoretextend.setFillColor(sf::Color::Red);
        sf::FloatRect textbounds = scoretextend.getGlobalBounds();
        scoretextend.setPosition((WINDOW_WIDTH - textbounds.width) / 2, WINDOW_HEIGHT / 2 - 100);

        // setup menu
        menubuttontext.setFont(fontbutton);
        menubuttontext.setCharacterSize(52);
        menubuttontext.setString("Menu");
        menubuttontext.setFillColor(sf::Color::Blue);
        menubuttontext.setPosition((WINDOW_WIDTH - textbounds.width) / 2, WINDOW_HEIGHT / 2 );


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
            if (game_state == menu) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
                    if (startbutton.getGlobalBounds().contains(mousepos))
                    {
                        game_state = play;
                    }
                    else if (rankingbutton.getGlobalBounds().contains(mousepos)) {
                        game_state = ranking;
                    }
                }
            }
            else if (game_state == play) {
                if (event.type == sf::Event::KeyPressed && event.mouseButton.button == sf::Keyboard::Space)bird.jump();
            }
            else if (game_state == endscreen) {
                sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
                if (menubuttontext.getGlobalBounds().contains(mousepos))
                {
                    game_state = menu;
                }
            }
        }
    }

    void update() {
        float dt = clock.restart().asSeconds();
        if (game_state == play)
        {
            bird.update(dt);
            back_ground.update(dt);

            // Update pipes
            timeSinceLastPipe += dt;
            if (timeSinceLastPipe > PIPE_SPAWN_INTERVAL) {
                float gapY = getRandomFloat(150, WINDOW_HEIGHT - 150);
                //pipes.emplace_back(WINDOW_WIDTH, gapY, 200);
                pipes.emplace_back(pipetexture, WINDOW_WIDTH, gapY, 200);
                timeSinceLastPipe = 0;
            }

            //if (back_ground.getbound().left + back_ground.getbound().width <= window.getSize().x) {
            //    back_ground.resetposition(0, 0);
            //}


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
            // vòng for cho dành cho tất cả pipe đang chạy
            for (auto& pipe : pipes) {
                if (pipe.collidesWith(bird)) { // kiểm tra va chạm giữa bird và pipe, trả về true nếu có va chạm
                    resetGame();
                    //game_state = menu;

                    return;
                }

                if (!pipe.isScored() && bird.getBounds().left > pipe.getX()) {
                    pipe.setScored(true);
                    score++;
                }
            }

            // check nếu bird ở ngoài màn hìnưind
            if (bird.getBounds().top < 0 || bird.getBounds().top + bird.getBounds().height >= window.getSize().y) {
                resetGame();
                return;
            }
            // Update score text
            scoreText.setString("Score: " + std::to_string(score));
        }
    }

    void render() {
        window.clear();
        if (game_state == menu) {
            back_ground.render(window);
            ground_.render(window);
            window.draw(startbutton);
            window.draw(pausebutton);
            window.draw(rankingbutton);
        }
        else if (game_state == play) {
            back_ground.render(window);
            ground_.render(window);
            bird.render(window);
            for (auto& pipe : pipes)pipe.render(window);
            window.draw(scoreText);
        }
        else if (game_state == endscreen) {
            back_ground.render(window);
            ground_.render(window);
            window.draw(scoretextend);
            window.draw(menubuttontext);
        }
        window.display();
    }

    void resetGame() {
        bird.resetPosition(100, WINDOW_HEIGHT / 2);
        back_ground.resetposition();
        ground_.resetpositon();
        pipes.clear();
        score = 0;
        game_state = endscreen;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    Game game;
    game.run();
    return 0;
}
