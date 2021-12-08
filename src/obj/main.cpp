#include "../include/main.hpp"

int main() {
	Game game;

	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
					break;
				}
				
				case sf::Event::KeyPressed: {
					if (event.key.code == sf::Keyboard::Q) window.close();
					break;
				}

				case sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (event.mouseButton.x >= BLOCK_OFFSET && event.mouseButton.x < (BLOCK_OFFSET + NUM_COLS*BLOCK_SIZE) && event.mouseButton.y >= BLOCK_OFFSET && event.mouseButton.y < (BLOCK_OFFSET + NUM_ROWS*BLOCK_SIZE)) {
							int index[2] = { (event.mouseButton.x - BLOCK_OFFSET) / BLOCK_SIZE, (event.mouseButton.y - BLOCK_OFFSET) / BLOCK_SIZE };
							game.select(index);
							if (game.hasPiece) game.piece.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
						} 
					}
					break;
				}

				case sf::Event::MouseMoved: {
					if (event.mouseMove.x >= BLOCK_OFFSET && event.mouseMove.x < (BLOCK_OFFSET + NUM_COLS*BLOCK_SIZE) && event.mouseMove.y >= BLOCK_OFFSET && event.mouseMove.y < (BLOCK_OFFSET + NUM_ROWS*BLOCK_SIZE)) {
						std::vector<std::array<int, 2>> indices;
						indices.push_back({ (event.mouseMove.x - BLOCK_OFFSET) / BLOCK_SIZE, (event.mouseMove.y - BLOCK_OFFSET) / BLOCK_SIZE });
						game.highlight(indices);
						if (game.hasPiece) game.piece.setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
					} 
					break;
				}

			}
		}

		window.clear(sf::Color(BACKGROUND));
		window.draw(game);
		window.display();
	}

	return 0;
}