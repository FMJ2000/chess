#ifndef _TEXTURES_HPP
#define _TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "const.hpp"

class Texture {
	public:
		static sf::Texture pieces[NUM_PIECES][NUM_PLAYERS];
		static sf::Texture loadTexture(std::string filename);
};

#endif