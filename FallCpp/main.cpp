#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

constexpr sf::Vector2f WINDOW_SIZE(1024, 768);

struct Flake {
    sf::Vector2f position;
    sf::Vector2f velocity;
};

class Fall {
public:
    explicit Fall(int amount) : vertices(sf::PrimitiveType::Triangles), gen(rd()) {
        setDensity(amount);
    }

    void setDensity(int amount) {
        flakes.resize(amount);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(0, WINDOW_SIZE.x);
        std::uniform_real_distribution<float> distY(0, WINDOW_SIZE.y);
        std::uniform_real_distribution<float> distVelX(0.0f, 10.0f);
        std::uniform_real_distribution<float> distVelY(0.0f, 20.0f);

        for (int i = 0; i < amount; ++i) {
            flakes[i] = { {distX(gen), distY(gen)}, {distVelX(gen), distVelY(gen)} };
        }
    }

    void update(float gravity, float wind, float dt) {
        for (auto& flake : flakes) {
            flake.position.x += flake.velocity.x * wind * dt;
            flake.position.y += flake.velocity.y * gravity * dt;

            if (flake.position.y > WINDOW_SIZE.y)   flake.position.y = 0;
            if (flake.position.x > WINDOW_SIZE.x)   flake.position.x = 0;
            if (flake.position.x < 0)               flake.position.x = WINDOW_SIZE.x;
            if (flake.position.y < 0)               flake.position.y = WINDOW_SIZE.y;
        }
    }

    void draw(sf::RenderWindow& window, sf::Color color) {
        constexpr static unsigned short verticesPerFlake = 3;
        sf::VertexArray vertices(sf::PrimitiveType::Triangles, flakes.size() * verticesPerFlake);

        for (size_t i = 0; i < flakes.size(); ++i) {
            vertices[i * verticesPerFlake + 0].position = flakes[i].position + sf::Vector2f(-flakeSize, -flakeSize);
            vertices[i * verticesPerFlake + 1].position = flakes[i].position + sf::Vector2f(flakeSize, -flakeSize);
            vertices[i * verticesPerFlake + 2].position = flakes[i].position + sf::Vector2f(flakeSize, flakeSize);

            for (int j = 0; j < verticesPerFlake; ++j) {
                vertices[i * verticesPerFlake + j].color = color;
            }
        }

        window.draw(vertices);
    }

private:
    std::vector<Flake> flakes;
    sf::VertexArray vertices;
    std::random_device rd;
    std::mt19937 gen;
    constexpr static float flakeSize = 3.0f;
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(WINDOW_SIZE.x), static_cast<unsigned>(WINDOW_SIZE.y) }), "FallCpp");

    sf::Clock fpsClock;
    float fps = 0.0f;

    unsigned int density = 500 + rand() % 3000;
    std::cout << "Density: " << density << std::endl;
    Fall fall(density);

    bool snow = true;
    bool rain = false;
    bool laser = false;
    float wind = 50.0f;
    float gravity = 15.0f;
    sf::Color color(150, 150, 150);

    while (window.isOpen()) {
        float deltaTime = fpsClock.restart().asSeconds();
        fps = 1.0f / deltaTime;
        window.setTitle("FallCpp - FPS: " + std::to_string(static_cast<int>(fps)));

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }


            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Y) {
                    density += 100;
                    std::cout << "Density up to: " << density << std::endl;
                    fall.setDensity(density);
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::T) {
                    if (density > 100) density -= 100;
                    std::cout << "Density down to: " << density << std::endl;
                    fall.setDensity(density);
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::G) {
                    gravity -= 3.0f;
                    std::cout << "Gravity down to: " << gravity << std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::H) {
                    gravity += 3.0f;
                    std::cout << "Gravity up to: " << gravity << std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::B) {
                    wind -= 3.0f;
                    std::cout << "Wind down to: " << wind << std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::N) {
                    wind += 3.0f;
                    std::cout << "Wind up to: " << wind << std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::O) {
                    wind = 50.0f;
                    gravity = 10.0f;
                    color = sf::Color(150, 150, 150);
                    std::cout << "Snow Mode" << std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::K) {
                    wind = -80.0f;
                    gravity = 20.0f;
                    color = sf::Color(60, 60, 150);
                    std::cout << "Rain Mode" << std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::M) {
                    wind = 0.0f;
                    gravity = -10.0f;
                    color = sf::Color(170, 30, 30);
                    std::cout << "Laser Mode" << std::endl;
                }
            }
        }

        window.clear(sf::Color(10, 10, 20));

        fall.update(gravity, wind, deltaTime);
        fall.draw(window, color);

        window.display();
    }
    return 0;
}