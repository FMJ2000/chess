#include "../include/block.hpp"

Block::Block(int index[2], sf::Color color, sf::Color highlightColor) : color(color), highlightColor(highlightColor), hasPiece(0) {
	this->pos = sf::Vector2f(BLOCK_OFFSET + index[1]*BLOCK_SIZE, BLOCK_OFFSET + index[0]*BLOCK_SIZE);
	this->rect.setPosition(pos);
	this->rect.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
	this->rect.setFillColor(color);
}

void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(rect);
	if (this->hasPiece) target.draw(this->piece);	
}

void Block::setPiece(Piece pieceIndex, int player) {
	if (player >= 0 && player < NUM_PLAYERS) {
		this->hasPiece = 1;
		this->pieceIndex = pieceIndex;
		this->player = player;
		this->piece.setTexture(Texture::pieces[this->pieceIndex][this->player], true);

		// position and scale
		if (pieceIndex == PAWN) {
			this->piece.setScale(sf::Vector2f((float)BLOCK_SIZE / PAWN_SIZE, (float)BLOCK_SIZE / PAWN_SIZE));
			this->piece.setPosition(sf::Vector2f(this->pos.x + PAWN_OFFSET, this->pos.y + PAWN_OFFSET));
		} else {
			this->piece.setScale(sf::Vector2f((float)BLOCK_SIZE / PIECE_SIZE, (float)BLOCK_SIZE / PIECE_SIZE));
			if (pieceIndex == QUEEN) this->piece.setPosition(sf::Vector2f(this->pos.x + QUEEN_OFFSET, this->pos.y + PIECE_OFFSET));
			else this->piece.setPosition(sf::Vector2f(this->pos.x + PIECE_OFFSET, this->pos.y + PIECE_OFFSET));
		}
	} else this->hasPiece = 0;
}

void Block::highlight(char on) {
	if (on) this->rect.setFillColor(highlightColor);
	else this->rect.setFillColor(color);
}