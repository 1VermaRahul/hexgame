#ifndef GAME_H
#define GAME_H

#include<QGraphicsView>
#include<QGraphicsScene>
#include<QString>
#include"hexboard.h"
#include<QGraphicsRectItem>
#include<QMouseEvent>

class Game:public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parant=NULL);

    void displayMainMenu();

    QString getWhosTurn();
    void setWhosTurn(QString player);
    HexBoard *hexboard;
    void createNewCards(QString player);
    void mouseMoveEvent(QMouseEvent *event);
    QGraphicsScene *scene;
    Hex *cardToPlace;
    void pickUpCard(Hex *card);
    QPointF originalPos;
    void placeCard(Hex * hexToReplace);
    void nextPlayerTurn();
    void removeFromDeck(Hex* card,QString player);
public slots:
    void start();
private:
void drawPanel(int x,int y,int width,int height,QColor color,double opacity);
void drawGUI();
void createInitialCards();
void drawCards();
// variables
QString whosTurn_;
QGraphicsTextItem *whosTurnText;
QList<Hex*> player1Cards;
QList<Hex*> player2Cards;
};

#endif // GAME_H
