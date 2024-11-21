#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
using namespace std;

class Wall : public sf::Sprite {
    public:
        bool vertWall;
        Wall(const sf::Texture& wallTexture, float x, float y, bool vertWall) {
            this->setTexture(wallTexture);
            this->setPosition(x, y);
            this->setScale(5.f, 5.f);
            this->vertWall = vertWall;
        }
        Wall() = default;
        
};

class Bounceable : public sf::Sprite {
    public:
        string tag;
        sf::Clock clockX;
        sf::Clock clockY;
        float xSpeed;
        float ySpeed;
        sf::FloatRect hitBox;
        Bounceable(const sf::Texture& texture, float xSpeed, float ySpeed, string tag) {
            this->setTexture(texture);
            this->setPosition(400.f, 300.f);
            this->setScale(5.f, 5.f);
            this->xSpeed = xSpeed;
            this->ySpeed = ySpeed;
            this->tag = tag;
        }
        int onClick(int score) {
            return 0;
        }
        Bounceable() = default;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::Clock clickTime;
    sf::Vector2i mousePos;
    sf::Vector2f mousePosF;

    sf::Font font;
    if (!font.loadFromFile("res/fonts/nerdfont.ttf"))
    {
        cout << "font loading error";
    }

    sf::Text scoreText;
    
    int score;
    int bounceCount = 0;

    scoreText.setString("Score : 0");
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setPosition(80.f, 70.f);
    scoreText.setFillColor(sf::Color::Black);

    sf::RectangleShape backgroundrect;

    sf::Texture coinTexture;
    sf::Texture slimeTexture;
    sf::Texture wallTexture;
    
    Wall walls[100];


    if (!coinTexture.loadFromFile("res/textures/coin.png", sf::IntRect(0, 0, 16, 16)))
    {
        cout << "OMG IT DIDNT LOAD BRO";
    }

    if (!slimeTexture.loadFromFile("res/textures/slime_purple.png", sf::IntRect(0, 32, 20, 16)))
    {
        cout << "OMG IT DIDNT LOAD BRO";
    }

    if (!wallTexture.loadFromFile("res/textures/world_tileset.png", sf::IntRect(16, 0, 16, 16)))
    {
        cout << "OMG IT DIDNT LOAD BRO";
    }

    Bounceable bounceables[100];

    bounceables[0] = Bounceable(coinTexture, 0.4f, 0.4f, "coin");
    bounceables[1] = Bounceable(slimeTexture, -0.3f, 0.3f, "slime");
    bounceCount++;
    bounceCount++;


    backgroundrect.setFillColor(sf::Color::White);
    backgroundrect.setPosition(10.f, 10.f);
    backgroundrect.setSize(sf::Vector2f(900.0f, 900.0f));


    // HORIZONTAL WALLS
    for (int i = 0; i < 10; i++) {
        walls[i] = Wall(wallTexture, i*80, 0, false);
        walls[i+10] = Wall(wallTexture, i*80, 720, false);
    }

    // VERTICAL WALLS
    for (int i = 0; i < 9; i++) {
        walls[i+20] = Wall(wallTexture, 0, (i+1)*80, true);
        walls[i+30] = Wall(wallTexture, 720, (i+1)*80, true);
    }

    

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < bounceCount; i++)
        {
            bounceables[i].hitBox = bounceables[i].getGlobalBounds();
            bounceables[i].hitBox.left += 15.f;  // Adjust the left boundary
            bounceables[i].hitBox.top += 15.f;   // Adjust the top boundary
            bounceables[i].hitBox.width -= 30.f; // Adjust the width
            bounceables[i].hitBox.height -= 30.f; // Adjust the height
        }
        for (int i = 0; i < bounceCount; i++) {
            if (bounceables[i].clockX.getElapsedTime().asSeconds() > 0.1f)
            {
                for (Wall wall : walls)
                {
                    
                    if (bounceables[i].hitBox.intersects(wall.getGlobalBounds()) && wall.vertWall)
                    {
                        bounceables[i].xSpeed *= -1;
                        bounceables[i].clockX.restart();
                        break;
                    }
                }
                    
            }
        }

        for (int i = 0; i < bounceCount; i++) {
            if (bounceables[i].clockY.getElapsedTime().asSeconds() > 0.1f)
            {
                for (Wall wall : walls)
                {
                    
                    if (bounceables[i].hitBox.intersects(wall.getGlobalBounds()) && !wall.vertWall)
                    {
                        bounceables[i].ySpeed *= -1;
                        bounceables[i].clockX.restart();
                        break;
                    }
                }
                    
            }
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTime.getElapsedTime().asSeconds() > 0.5f)
        {
            mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (int i = 0; i < bounceCount; i++)
            {
                if (bounceables[i].getGlobalBounds().contains(mousePosF))
                {
                    if (bounceables[i].tag == "coin")
                    {
                        score += 1;
                        float speedBoost = bounceCount/10;
                        if (score%10 == 0)
                        {
                            
                            bounceables[bounceCount] = Bounceable(slimeTexture, 0.5f+speedBoost, 0.5f+speedBoost, "slime");
                            bounceCount++;
                        }

                        scoreText.setString("Score : " + std::to_string(score));
                        int randomChoice = rand() % 2;
                        switch (randomChoice) {
                            case 0:
                                bounceables[i].xSpeed += speedBoost;
                                bounceables[i].xSpeed *= -1;
                                break;
                            case 1:
                                bounceables[i].ySpeed -= speedBoost;
                                bounceables[i].ySpeed *= -1;
                                break;
                        }
                    }
                    else
                    {
                        window.close();
                    }
                }
                
                
            }
            
            
            clickTime.restart();
        } 

        for (int i = 0; i < bounceCount; i++)
        {
            bounceables[i].move(bounceables[i].xSpeed, bounceables[i].ySpeed);
        }

        window.clear();
        window.draw(backgroundrect);


        for (sf::Sprite wall : walls)
        {
            window.draw(wall);
        }

        for (Bounceable bounce : bounceables)
        {
            window.draw(bounce);
        }

        window.draw(scoreText);

        window.display();

    }

    return 0;
}