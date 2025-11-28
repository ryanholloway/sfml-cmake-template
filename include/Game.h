#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Main game class that manages window, assets, input, update and render loop.
 */
class Game {
public:
    /**
    * @brief Construct a new Game object
    *
    * @param title Window title (default: "SFML Game")
    * @param width Window width in pixels (default: 800)
    * @param height Window height in pixels (default: 600)
    * @param ups Updates per second (default: 60)
    * @param fps Frames per second (default: 60)
    */
    Game(const std::string& title = "SFML Game", unsigned int width = 800, unsigned int height = 600,
        unsigned int ups = 60, unsigned int fps = 60);

    /**
    * @brief Load fonts, textures and other game assets from the assets directory.
    */
    void loadAssets();

    /**
    * @brief Handle mouse input events.
    *
    * @param event The mouse button pressed event to process.
    */
    void handleMouseInput(const sf::Event::MouseButtonPressed& event);

    /**
    * @brief Handle keyboard input events.
    *
    * @param event The key pressed event to process.
    */
    void handleKeyboardInput(const sf::Event::KeyPressed& event);

    /**
    * @brief Update game state.
    *
    * @param dt Delta time in seconds since last update.
    */
    void update(float dt);

    /**
    * @brief Render the current game state to the window.
    */
    void render();

    /**
    * @brief Start the main game loop (process events, update, render).
    */
    void run();

private:
    std::string assetsPath;
    unsigned int updatesPerSecond;
    unsigned int framesPerSecond;
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture texture;
    bool running;
};
