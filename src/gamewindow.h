// Hearts & Stars Game
// Author: Erin Murphy

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QSignalMapper>
#include <QDebug>
#include "player.h"

const int GRID_DMSN = 3;

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow {

    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void getPlayerSymbols();
    void checkForWinner();    
    void declareWinner();

private slots:
    void startGame();
    void playAgain();
    void playGame(QString);

private:
    Ui::GameWindow *ui;
    Player *p1, *p2;    
    QPushButton *playButtons[GRID_DMSN][GRID_DMSN];
    QSignalMapper *mapper; 
    QIcon *heart, *star, *currentSymbol;
    bool player1Turn, gameWon;
    int turn = 0, currentLines[GRID_DMSN][GRID_DMSN] = {{0}};
};
#endif // GAMEWINDOW_H
