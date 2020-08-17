// Hearts & Stars Game
// Author: Erin Murphy

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>

class Player : public QObject{

    Q_OBJECT

public:
    Player();
    ~Player();
    Player(int, QIcon *, QString);
    void setTurn(int);
    void setSymbol(QIcon *);
    int getTurn();
    QIcon * getSymbol();
    QString getSymbolText();

private:
    int turn;
    QIcon *symbol;
    QString symbolText;
};

#endif // PLAYER_H
