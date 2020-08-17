// Hearts & Stars Game
// Author: Erin Murphy

#include "player.h"

Player::Player() : turn(1) {}

Player::Player(int t, QIcon *s, QString st) : turn(t), symbol(s), symbolText(st) {}

Player::~Player(){}

void Player::setTurn(int t) { turn = t; }

void Player::setSymbol(QIcon *s) { symbol = s; }

int Player::getTurn() { return turn; }

QIcon * Player::getSymbol() { return symbol; }

QString Player::getSymbolText() { return symbolText; }
