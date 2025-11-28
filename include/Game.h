#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Game {
public:
    Game(const std::string& title = "SFML Game", unsigned int width = 800, unsigned int height = 600,
         unsigned int ups = 60, unsigned int fps = 60);

    void loadAssets();
    void handleMouseInput(const sf::Event::MouseButtonPressed& event);
    void handleKeyboardInput(const sf::Event::KeyPressed& event);
    void update(float dt);
    void render();
    void run();

private:
    std::string assetsPath;
    unsigned int updatesPerSecond;
    unsigned int framesPerSecond;
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture texture;
    bool running;
    bool thisIsABool; // example camelCase default variable name as requested
};
