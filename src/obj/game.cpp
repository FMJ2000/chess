#include "../include/game.hpp"

Game::Game() : round(0), turn(0), hasPiece(0) {
	// setup
	this->font.loadFromFile(FONT_FILE);
	this->round = 0;
	this->turn = 0;
	for (uint8_t i = 0; i < NUM_PLAYERS; i++) this->players[i] = new Player(this, i);

	// border
	this->border.setFillColor(sf::Color::Transparent);
	this->border.setPosition(sf::Vector2f(BLOCK_OFFSET, BLOCK_OFFSET));
	this->border.setSize(sf::Vector2f(NUM_ROWS*BLOCK_SIZE, NUM_COLS*BLOCK_SIZE));
	this->border.setOutlineThickness(20);
	this->border.setOutlineColor(sf::Color(BORDER));
	
	// blocks
	for (uint8_t i = 0; i < NUM_ROWS; i++) {
		for (uint8_t j = 0; j < NUM_COLS; j++) {
			int index[2] = { i, j };
			sf::Color color = ((i + j) % 2 == 0) ? sf::Color(WHITE_COL) : sf::Color(BLACK_COL);
			sf::Color highlightColor = ((i + j) % 2 == 0) ? sf::Color(WHITE_HIGHLIGHT) : sf::Color(BLACK_HIGHLIGHT);
			this->board[i][j] = new Block(index, color, highlightColor);
		}
	}
	this->piece.setOrigin(sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2));

	// text
	this->info.setFont(this->font);
	std::string infoStr = "Round 1 - white to start";
	this->setInfo(infoStr);

	this->setup();
}

Game::~Game() {
	// players
	for (uint8_t i = 0; i < NUM_PLAYERS; i++) delete this->players[i];

	for (uint8_t i = 0; i < NUM_ROWS; i++) {
		for (uint8_t j = 0; j < NUM_COLS; j++) {
			delete this->board[i][j];
		}
	}
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// players
	for (uint8_t i = 0; i < NUM_PLAYERS; i++) target.draw(*this->players[i]);
	
	// board
	target.draw(this->border);
	for (uint8_t i = 0; i < NUM_ROWS; i++)
		for (uint8_t j = 0; j < NUM_COLS; j++)
			target.draw(*this->board[i][j]);

	if (this->hasPiece) target.draw(this->piece);

	target.draw(this->info);
}

void Game::setInfo(std::string line) {
	this->info.setString(line);
	float width = this->info.getGlobalBounds().width;
	this->info.setPosition(sf::Vector2f(W_WIDTH / 2 - width, W_HEIGHT - 60));
}

void Game::setup() {
	// white pieces
	this->board[7][0]->setPiece(ROOK, WHITE);
	this->board[7][1]->setPiece(KNIGHT, WHITE);
	this->board[7][2]->setPiece(BISHOP, WHITE);
	this->board[7][3]->setPiece(QUEEN, WHITE);
	this->board[7][4]->setPiece(KING, WHITE);
	this->board[7][5]->setPiece(BISHOP, WHITE);
	this->board[7][6]->setPiece(KNIGHT, WHITE);
	this->board[7][7]->setPiece(ROOK, WHITE);
	for (uint8_t i = 0; i < NUM_COLS; i++) this->board[6][i]->setPiece(PAWN, WHITE);

	// black pieces
	this->board[0][0]->setPiece(ROOK, BLACK);
	this->board[0][1]->setPiece(KNIGHT, BLACK);
	this->board[0][2]->setPiece(BISHOP, BLACK);
	this->board[0][3]->setPiece(QUEEN, BLACK);
	this->board[0][4]->setPiece(KING, BLACK);
	this->board[0][5]->setPiece(BISHOP, BLACK);
	this->board[0][6]->setPiece(KNIGHT, BLACK);
	this->board[0][7]->setPiece(ROOK, BLACK);
	for (uint8_t i = 0; i < NUM_COLS; i++) this->board[1][i]->setPiece(PAWN, BLACK);
}

void Game::highlight(std::vector<std::array<int, 2>> indices) {
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			char on = 0;
			for (int k = 0; k < indices.size(); k++) {
				if (indices[k][0] == i && indices[k][1] == j) on = 1;
			}
			this->board[i][j]->highlight(on);
		}
	}
}

void Game::select(std::array<int, 2> index) {
	if (this->hasPiece) {
		// holding piece, put down
		for (auto it = this->valid.begin(); it < this->valid.end(); it++) {
			if (index == *it) {
				this->board[index[0]][index[1]]->setPiece(this->pieceIndex, this->turn);
				this->hasPiece = 0;
				if (it - this->valid.begin() > 0) {
					this->turn ^= 1;
					if (!this->turn) this->round++;
					std::string infoStr = "Round " + std::to_string(this->round + 1) + " - ";
					infoStr += (this->turn) ? "black's turn" : "white's turn";
					this->setInfo(infoStr);
				}
			}
		}
	} else {
		// picking piece up
		if (this->board[index[0]][index[1]]->hasPiece && this->board[index[0]][index[1]]->player == this->turn) {
			this->setPiece(this->board[index[0]][index[1]]->pieceIndex);
			this->board[index[0]][index[1]]->setPiece(NONE, -1);
			this->validMoves(this->pieceIndex, index);
			this->highlight(this->valid);
		}
	}	
}

void Game::setPiece(Piece pieceIndex) {
	this->hasPiece = 1;
	this->pieceIndex = pieceIndex;
	this->piece.setTexture(Texture::pieces[this->pieceIndex][this->turn], true);

	// position and scale
	if (pieceIndex == PAWN) {
		this->piece.setScale(sf::Vector2f((float)BLOCK_SIZE / PAWN_SIZE, (float)BLOCK_SIZE / PAWN_SIZE));
	} else {
		this->piece.setScale(sf::Vector2f((float)BLOCK_SIZE / PIECE_SIZE, (float)BLOCK_SIZE / PIECE_SIZE));
	}
}

void Game::validMoves(Piece pieceIndex, std::array<int, 2> pos) {
	this->valid.clear();
	this->valid.push_back({ pos[0], pos[1] });

	switch (pieceIndex) {
		case KING: {
			for (uint8_t i = 0; i < 8; i++) {
				std::vector<std::array<int, 2>> newValid = this->validLine(pos, i, 1);
				this->valid.insert(std::end(this->valid), std::begin(newValid), std::end(newValid));
			}
			break;
		}

		case QUEEN: {
			for (uint8_t i = 0; i < 8; i++) {
				std::vector<std::array<int, 2>> newValid = this->validLine(pos, i, NUM_ROWS);
				this->valid.insert(std::end(this->valid), std::begin(newValid), std::end(newValid));
			}
			break;
		}

		case ROOK: {
			for (uint8_t i = 0; i < 4; i++) {
				std::vector<std::array<int, 2>> newValid = this->validLine(pos, 2*i+1, NUM_ROWS);
				this->valid.insert(std::end(this->valid), std::begin(newValid), std::end(newValid));
			}
			break;
		}

		case BISHOP: {
			for (uint8_t i = 0; i < 4; i++) {
				std::vector<std::array<int, 2>> newValid = this->validLine(pos, 2*i, NUM_ROWS);
				this->valid.insert(std::end(this->valid), std::begin(newValid), std::end(newValid));
			}
			break;
		}

		case KNIGHT: {
			for (uint8_t i = 0; i < 8; i++) {
				std::array<int, 2> newPos = { pos[0] + knightMod[i][0], pos[1] + knightMod[i][1] };
				if (newPos[COL] >= 0 && newPos[COL] < NUM_COLS && newPos[ROW] >= 0 && newPos[ROW] < NUM_ROWS && (!this->board[newPos[ROW]][newPos[COL]]->hasPiece || this->board[newPos[ROW]][newPos[COL]]->player != turn)) this->valid.push_back(newPos);
			}
			break;
		}

		case PAWN: {
			switch (turn) {
				case WHITE: {
					if (pos[ROW]-1 >= 0) {
						if (!this->board[pos[ROW]-1][pos[COL]]->hasPiece) {
							this->valid.push_back({ pos[ROW]-1, pos[COL] });
							if (pos[ROW] == 6 && !this->board[pos[ROW]-2][pos[COL]]->hasPiece) this->valid.push_back({ pos[ROW]-2, pos[COL] });
						}
						if (pos[COL]-1 >= 0 && this->board[pos[ROW]-1][pos[COL]-1]->hasPiece && this->board[pos[ROW]-1][pos[COL]-1]->player == BLACK) this->valid.push_back({ pos[ROW]-1, pos[COL]-1 });
						if (pos[COL]+1 < NUM_COLS && this->board[pos[ROW]-1][pos[COL]+1]->hasPiece && this->board[pos[ROW]-1][pos[COL]+1]->player == BLACK) this->valid.push_back({ pos[ROW]-1, pos[COL]+1 });
					}
					break;
				}

				case BLACK: {
					if (pos[ROW]+1 < NUM_ROWS) {
						if (!this->board[pos[ROW]+1][pos[COL]]->hasPiece) {
							this->valid.push_back({ pos[ROW]+1, pos[COL] });
							if (pos[ROW] == 1 && !this->board[pos[ROW]+2][pos[COL]]->hasPiece) this->valid.push_back({ pos[ROW]+2, pos[COL] });
						}
						if (pos[COL]-1 >= 0 && this->board[pos[ROW]+1][pos[COL]-1]->hasPiece && this->board[pos[ROW]+1][pos[COL]-1]->player == WHITE) this->valid.push_back({ pos[ROW]+1, pos[COL]-1 });
						if (pos[COL]+1 < NUM_COLS && this->board[pos[ROW]+1][pos[COL]+1]->hasPiece && this->board[pos[ROW]+1][pos[COL]+1]->player == WHITE) this->valid.push_back({ pos[ROW]+1, pos[COL]+1 });
					}
					break;
				}
			}
			break;
		}
	}
}

std::vector<std::array<int, 2>> Game::validLine(std::array<int, 2> startPos, char direction, int length) {
	std::vector<std::array<int, 2>> valid;
	std::array<int, 2> currPos = startPos;
	char flag = 1;
	int index = 0;

	while (flag && index < length) {
		// determine new position
		currPos[0] += posMod[direction][0];
		currPos[1] += posMod[direction][1];

		// check if valid and open
		if (currPos[COL] >= 0 && currPos[COL] < NUM_COLS && currPos[ROW] >= 0 && currPos[ROW] < NUM_ROWS) {
			if (this->board[currPos[ROW]][currPos[COL]]->hasPiece) {
				flag = 0;
				if (this->board[currPos[ROW]][currPos[COL]]->player != turn) valid.push_back(currPos);
			} else valid.push_back(currPos);
		}	else flag = 0;
		index++;
	}

	return valid;
}