#include "../include/player.hpp"
#include "../include/game.hpp"

Player::Player(Game * parent, uint8_t turn) {
	this->parent = parent;
	this->turn = turn;

	// title
	this->title.setFont(this->parent->font);
	std::string titleStr = "Player " + std::to_string(turn+1);
	this->title.setString(titleStr);
	this->title.setPosition(sf::Vector2f(PLAYER_LEFT, PLAYER_TOP + PLAYER_HEIGHT*turn));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(this->title);
}