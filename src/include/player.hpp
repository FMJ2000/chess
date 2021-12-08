#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "const.hpp"

class Game;

class Player: public sf::Drawable {
	private:
		uint8_t turn;
		Game * parent;
		sf::Text title;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	public:
		Player(Game * parent, uint8_t turn);
};

#endif