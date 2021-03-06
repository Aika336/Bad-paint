#include "SFML\Graphics.hpp"
#include <vector>

#define CLOSE window.close()
#define MOUSEPOS sf::Mouse::getPosition()

int main() {
    std::vector<sf::VertexArray> vertices;
    vertices.push_back(sf::VertexArray());
    vertices[0].setPrimitiveType(sf::LinesStrip);

    int lines_number = 0;
    bool locked = false;

    sf::Color curr_col = sf::Color::Black;
    sf::Vector2i last_Mouse_pos(0, 0);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Paint");
    window.setFramerateLimit(60);

    sf::Vector2f Border_Offset(-5, -25);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Key::Escape)
                    CLOSE;
            if (event.type == sf::Event::Closed)
                CLOSE;

            if (event.type == sf::Event::MouseButtonPressed) {
                locked = true;
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                lines_number++;
                vertices.push_back(sf::VertexArray());
                vertices[lines_number].setPrimitiveType(sf::LinesStrip);

                locked = false;
            }
        }

        if (locked) {
            if (last_Mouse_pos != MOUSEPOS) {
                vertices[lines_number].append(sf::Vertex(sf::Vector2f(MOUSEPOS.x - window.getPosition().x + Border_Offset.x, MOUSEPOS.y - window.getPosition().y + Border_Offset.y), curr_col));

                last_Mouse_pos = MOUSEPOS;
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < vertices.size(); i++) {
            window.draw(vertices[i]);
        }
        window.display();
    }

    return 0;
}