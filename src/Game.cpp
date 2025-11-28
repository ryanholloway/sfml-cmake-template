#include "../include/Game.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Game::Game(const std::string& title, unsigned int width, unsigned int height, unsigned int ups, unsigned int fps)
    : updatesPerSecond(ups), framesPerSecond(fps), window(sf::VideoMode({width, height}), title), running(true), thisIsABool(true)
{
    assetsPath = "assets";
}

void Game::loadAssets() {
    fs::path fontPath = fs::path(assetsPath) / "fonts" / "arial.ttf";
    if (fs::exists(fontPath)) {
        if (!font.openFromFile(fontPath)) {
            std::cerr << "Failed to open font from " << fontPath << "\n";
        }
    } else {
    }

    fs::path imagePath = fs::path(assetsPath) / "images" / "image.png";
    if (fs::exists(imagePath)) {
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << "Failed to load texture from " << imagePath << "\n";
        }
    }
}

void Game::handleMouseInput(const sf::Event::MouseButtonPressed& event) {
    std::cout << "Mouse button pressed: " << static_cast<int>(event.button) << " at (" << event.position.x << ", " << event.position.y << ")\n";
}

void Game::handleKeyboardInput(const sf::Event::KeyPressed& event) {
    if (event.code == sf::Keyboard::Key::Escape) {
        window.close();
    }
}

void Game::update(float dt) {
    (void)dt;
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (!font.getInfo().family.empty()) {
        sf::Text txt(font);
        txt.setString("SFML Template");
        txt.setCharacterSize(24);
        txt.setFillColor(sf::Color::White);
        txt.setPosition({10.f, 10.f});
        window.draw(txt);
    }

    if (texture.getSize().x > 0) {
        sf::Sprite s(texture);
        s.setPosition({100.f, 100.f});
        window.draw(s);
    }

    window.display();
}

void Game::run() {
    loadAssets();

    const float fixedDt = 1.0f / static_cast<float>(updatesPerSecond);
    const float minFrameTime = (framesPerSecond > 0) ? 1.0f / static_cast<float>(framesPerSecond) : 0.0f;

    sf::Clock clock;
    float accumulator = 0.0f;
    float renderTimer = 0.0f;

    while (window.isOpen()) {
        float elapsed = clock.restart().asSeconds();
        accumulator += elapsed;
        renderTimer += elapsed;

            while (auto event = window.pollEvent()) {
                if (const auto* closed = event->getIf<sf::Event::Closed>()) {
                    window.close();
                }

                if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                    handleKeyboardInput(*key);

                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                    handleMouseInput(*mouse);
            }

        while (accumulator >= fixedDt) {
            update(fixedDt);
            accumulator -= fixedDt;
        }

        if (minFrameTime == 0.0f || renderTimer >= minFrameTime) {
            render();
            renderTimer = 0.0f;
        } else {
            sf::sleep(sf::milliseconds(1));
        }
    }
}
