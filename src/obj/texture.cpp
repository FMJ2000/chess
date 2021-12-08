#include "../include/texture.hpp"

sf::Texture Texture::loadTexture(std::string filename) {
	sf::Texture tmp;
	if (!tmp.loadFromFile(filename)) std::cout << "Error loading file " << filename << std::endl;
	return tmp;
}

sf::Texture Texture::pieces[NUM_PIECES][NUM_PLAYERS] = {
	{ Texture::loadTexture(W_KING_FILE), Texture::loadTexture(B_KING_FILE) },
	{ Texture::loadTexture(W_QUEEN_FILE), Texture::loadTexture(B_QUEEN_FILE) },
	{ Texture::loadTexture(W_ROOK_FILE), Texture::loadTexture(B_ROOK_FILE) },
	{ Texture::loadTexture(W_BISHOP_FILE), Texture::loadTexture(B_BISHOP_FILE) },
	{ Texture::loadTexture(W_KNIGHT_FILE), Texture::loadTexture(B_KNIGHT_FILE) },
	{ Texture::loadTexture(W_PAWN_FILE), Texture::loadTexture(B_PAWN_FILE) }
};