#ifndef _GAME_HPP
#define _GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "const.hpp"
#include "player.hpp"
#include "block.hpp"

class Game: public sf::Drawable {
	private:
		// setup
		char turn;
		unsigned int round;
		
		// players
		Player * players[NUM_PLAYERS];

		// board
		Block * board[NUM_ROWS][NUM_COLS];
		sf::RectangleShape border;
		std::vector<std::array<int, 2>> valid;
		sf::Text info;

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	public:
		sf::Font font;
		char hasPiece;
		Piece pieceIndex;
		sf::Sprite piece;

		Game();
		~Game();
		void setInfo(std::string line);
		void setup();
		void highlight(std::vector<std::array<int, 2>> indices);
		void select(std::array<int, 2> index);
		void setPiece(Piece pieceIndex);
		void validMoves(Piece pieceIndex, std::array<int, 2> pos);
		std::vector<std::array<int, 2>> validLine(std::array<int, 2> pos, char direction, int length);
};

#endif