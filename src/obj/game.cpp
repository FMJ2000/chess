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
				if (indices.at(k).at(1) == i && indices.at(k).at(0) == j) on = 1;
			}
			this->board[i][j]->highlight(on);
		}
	}
}

void Game::select(int index[2]) {
	if (this->hasPiece) {
		// holding piece, put down
		this->board[index[1]][index[0]]->setPiece(this->pieceIndex, this->turn);
		this->hasPiece = 0;
		this->turn ^= 1;
	} else {
		// picking piece up
		if (this->board[index[1]][index[0]]->hasPiece && this->board[index[1]][index[0]]->player == this->turn) {
			this->setPiece(this->board[index[1]][index[0]]->pieceIndex);
			this->board[index[1]][index[0]]->setPiece(NONE, -1);
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

