#ifndef _CONST_HPP
#define _CONST_HPP

// files
#define FONT_FILE "textures/arial.ttf"
#define W_KING_FILE "textures/w_king.png"
#define W_QUEEN_FILE "textures/w_queen.png"
#define W_ROOK_FILE "textures/w_rook.png"
#define W_BISHOP_FILE "textures/w_bishop.png"
#define W_KNIGHT_FILE "textures/w_knight.png"
#define W_PAWN_FILE "textures/w_pawn.png"
#define B_KING_FILE "textures/b_king.png"
#define B_QUEEN_FILE "textures/b_queen.png"
#define B_ROOK_FILE "textures/b_rook.png"
#define B_BISHOP_FILE "textures/b_bishop.png"
#define B_KNIGHT_FILE "textures/b_knight.png"
#define B_PAWN_FILE "textures/b_pawn.png"

// layout
#define W_WIDTH 1200
#define W_HEIGHT 900
#define W_TITLE "Cheesy Chess"

// players
#define NUM_PLAYERS 2
#define PLAYER_LEFT 900
#define PLAYER_TOP 100
#define PLAYER_HEIGHT 400
#define WHITE 0
#define BLACK 1

// board
#define NUM_ROWS 8
#define NUM_COLS 8
#define PIECE_OFFSET 12
#define PAWN_OFFSET 20
#define QUEEN_OFFSET 7
#define BLOCK_OFFSET 50
#define PIECE_SIZE 160
#define PAWN_SIZE 180
#define BLOCK_SIZE 100
#define NUM_PIECES 6

// colors
#define BACKGROUND 0x34568bff
#define BORDER 0x603909ff
#define WHITE_COL 0xf3bc7aff
#define WHITE_HIGHLIGHT 0xf9debeff
#define BLACK_COL 0x644219ff
#define BLACK_HIGHLIGHT 0x926124ff

enum Piece {KING=0, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE};

#endif