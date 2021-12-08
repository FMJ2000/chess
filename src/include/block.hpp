#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <SFML/Graphics.hpp>

#include "const.hpp"
#include "texture.hpp"

class Block: public sf::Drawable {
	private:
		sf::Vector2f pos;
		sf::Color color;
		sf::Color highlightColor;
		sf::RectangleShape rect;
		sf::Sprite piece;

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	public:
		char hasPiece;
		Piece pieceIndex;
		int player;

		Block(int index[2], sf::Color color, sf::Color highlightColor);
		void setPiece(Piece pieceIndex, int player);
		void highlight(char on);
};

#endif