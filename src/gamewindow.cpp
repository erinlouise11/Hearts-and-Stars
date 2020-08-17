// Hearts & Stars Game                                        |
// Author: Erin Murphy                                        |
// This game is a remake attempt for the classic Tic-Tac-Toe  |
// 2 players chosing between hearts and stars as the symbols  |
// ___________________________________________________________|

#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow) {

    ui->setupUi(this);

    // adding the grid of QPushButtons to an accessible 2d array
    playButtons[0][0] = ui->btn00;
    playButtons[0][1] = ui->btn01;
    playButtons[0][2] = ui->btn02;
    playButtons[1][0] = ui->btn10;
    playButtons[1][1] = ui->btn11;
    playButtons[1][2] = ui->btn12;
    playButtons[2][0] = ui->btn20;
    playButtons[2][1] = ui->btn21;
    playButtons[2][2] = ui->btn22;

    ui->btnStartOver->setVisible(false);
    ui->lblStatus->clear();

    // adding images to the icons and setting
    heart = new QIcon(":/images/heart.png");
    star = new QIcon(":/images/star.png");

    setWindowTitle("Hearts & Stars");
    setWindowIcon(*heart);

    // setting the initial values for the booleans
    // player 1 goes first, duh
    player1Turn = true;
    gameWon = false;

    // positional strings to map to the button signals
    QString topleft = "0 0", topmid = "0 1", topright = "0 2";
    QString midleft = "1 0", midmid = "1 1", midright = "1 2";
    QString botleft = "2 0", botmid = "2 1", botright = "2 2";

    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->btnStartOver, SIGNAL(clicked()), this, SLOT(playAgain()));
    connect(ui->btn00, &QPushButton::pressed, [this, topleft] { playGame(topleft); });
    connect(ui->btn01, &QPushButton::pressed, [this, topmid] { playGame(topmid); });
    connect(ui->btn02, &QPushButton::pressed, [this, topright] { playGame(topright); });
    connect(ui->btn10, &QPushButton::pressed, [this, midleft] { playGame(midleft); });
    connect(ui->btn11, &QPushButton::pressed, [this, midmid] { playGame(midmid); });
    connect(ui->btn12, &QPushButton::pressed, [this, midright] { playGame(midright); });
    connect(ui->btn20, &QPushButton::pressed, [this, botleft] { playGame(botleft); });
    connect(ui->btn21, &QPushButton::pressed, [this, botmid] { playGame(botmid); });
    connect(ui->btn22, &QPushButton::pressed, [this, botright] { playGame(botright); });
}

GameWindow::~GameWindow() {

    delete ui;
}

void GameWindow::startGame() {

    // call the function to create the player objects
    getPlayerSymbols();

    ui->btnStart->setVisible(false);
    ui->btnStartOver->setVisible(true);
    ui->lblStatus->setText(p1->getSymbolText() + " go");
    ui->wPickSpotButtons->setEnabled(true);

   return;
}

void GameWindow::getPlayerSymbols() {

    // if the player 1 chooses a symbol, then assign the second player with the other symbol
    // create the player objects accordingly
    if (ui->cbSymbols->currentText() == "Hearts") {
        p1 = new Player(1, heart, "Hearts");
        p2 = new Player(2, star, "Stars");
    }
    else {
        p1 = new Player(1, star, "Stars");
        p2 = new Player(2, heart, "Hearts");
    }

    return;
}

void GameWindow::playGame(QString signal) {

    // getting the row and colum from the signal string
    QStringList list = signal.split(" ");
    int row = list[0].toInt();
    int col = list[1].toInt();

    int player;

    // getting the symbol associated with the current player
    if (player1Turn) {
        currentSymbol = p1->getSymbol();
        player = 1;
    }
    else {
        currentSymbol = p2->getSymbol();
        player = 2;
    }

    // if the game is still running set the button icon to the current symbol and display whos turn it is
    // no one position can be pressed twice
    if (!gameWon && turn <= 9) {
        playButtons[row][col]->setIcon(*currentSymbol);
        playButtons[row][col]->setIconSize(QSize(51, 51));
        playButtons[row][col]->blockSignals(true);
        currentLines[row][col] = player;
        turn++; // only 9 turns allowed

        checkForWinner();

        if (gameWon)
            return;
        else {
            // when no winning conditions met the game will end allowing the players to play again
            if (turn == 9) {
                ui->lblStatus->setText("No winner!");
                ui->btnStartOver->setText("PLAY AGAIN");
            }
            else if (player1Turn) {
                player1Turn = false;
                ui->lblStatus->setText(p2->getSymbolText() + " go");
            }
            else {
                player1Turn = true;
                ui->lblStatus->setText(p1->getSymbolText() + " go");
            }
        }
    }

    return;
}

void GameWindow::checkForWinner() {

    // to check for a winner, we compare the current symbols on the board to the winning conditions
    // if there is a match, the game is won and the winning line is displayed
    if (currentLines[0][0] > 0 && currentLines[0][0] == currentLines[1][0] && currentLines[1][0] == currentLines[2][0]){
        gameWon = true;
        ui->btn00->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn10->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn20->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[0][0] > 0 && currentLines[0][0] == currentLines[0][1] && currentLines[0][1] == currentLines[0][2]){
        gameWon = true;
        ui->btn00->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn01->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn02->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[0][0] > 0 && currentLines[0][0] == currentLines[1][1] && currentLines[1][1] == currentLines[2][2]){
        gameWon = true;
        ui->btn00->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn11->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn22->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[0][1] > 0 && currentLines[0][1] == currentLines[1][1] && currentLines[1][1] == currentLines[2][1]){
        gameWon = true;
        ui->btn01->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn11->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn21->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[0][2] > 0 && currentLines[0][2] == currentLines[1][2] && currentLines[1][2] == currentLines[2][2]){
        gameWon = true;
        ui->btn02->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn12->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn22->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[0][2] > 0 && currentLines[0][2] == currentLines[1][1] && currentLines[1][1] == currentLines[2][0]){
        gameWon = true;
        ui->btn02->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn11->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn20->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[1][0] > 0 && currentLines[1][0] == currentLines[1][1] && currentLines[1][1] == currentLines[1][2]){
        gameWon = true;
        ui->btn10->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn11->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn12->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }
    else if (currentLines[2][0] > 0 && currentLines[2][0] == currentLines[2][1] && currentLines[2][1] == currentLines[2][2]){
        gameWon = true;
        ui->btn20->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn21->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
        ui->btn22->setStyleSheet("QPushButton { background-color: rgb(191,148,228) }");
    }

    if (gameWon)
        declareWinner();

    return;
}

void GameWindow::declareWinner() {

    // setting the status to display the winning symbol and allow the players to play again
    if (player1Turn) {
        ui->lblStatus->setText(p1->getSymbolText() + " WIN!");
    }
    else {
        ui->lblStatus->setText(p2->getSymbolText() + " WIN!");
    }

    // allow no further input on the board
    for (int i = 0; i < GRID_DMSN; i++) {
        for (int j = 0; j < GRID_DMSN; j++) {
            playButtons[i][j]->blockSignals(true);
        }
    }

    ui->btnStartOver->setText("PLAY AGAIN");

    return;
}

void GameWindow::playAgain() {

    // reset the game
    ui->cbSymbols->setCurrentIndex(0);
    ui->btnStart->setVisible(true);
    ui->btnStartOver->setVisible(false);
    ui->btnStartOver->setText("START OVER");
    ui->lblStatus->clear();
    player1Turn = true;
    gameWon = false;
    turn = 0;

    for (int row = 0; row < GRID_DMSN; row++) {
        for (int col = 0; col < GRID_DMSN; col++) {
            playButtons[row][col]->setIcon(QIcon());
            playButtons[row][col]->blockSignals(false);
            playButtons[row][col]->setStyleSheet("QPushButton { background-color: white; border: 0px; }");
            currentLines[row][col] = 0;
        }
    }

    ui->wPickSpotButtons->setEnabled(false);

    // destroying the player objects in memory
    delete[] p1;
    delete[] p2;

    return;
}
