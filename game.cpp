#include "game.h"
#include "hex.h"
#include<QDebug>
#include"button.h"
#include<QGraphicsTextItem>
#include"hexboard.h"
#include<QBrush>
#include<QGraphicsRectItem>
#include<QGraphicsScene>
#include<QDebug>
Game::Game(QWidget *parant)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);

    setScene(scene);
    whosTurn_ = QString("PLAYER1");
    cardToPlace = NULL;
}


void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem *panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI()
{
    drawPanel(0,0,150,768,Qt::darkCyan,1);
    drawPanel(874,0,150,768,Qt::darkCyan,1);
   // qDebug()<<"started";
    QGraphicsTextItem *p1 = new QGraphicsTextItem("Player 1's cards: ");
    p1->setPos(5,0);
    scene->addItem(p1);

    QGraphicsTextItem *p2 = new QGraphicsTextItem("Player 2's cards: ");
    p2->setPos(874+5,0);
    scene->addItem(p2);

    whosTurnText = new QGraphicsTextItem();
    setWhosTurn(QString("PLAYER1"));
    whosTurnText->setPos(490,0);
    scene->addItem(whosTurnText);
}


void Game::displayMainMenu()
{
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Hex Warz"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    Button *quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

QString Game::getWhosTurn()
{
    return whosTurn_;
}

void Game::setWhosTurn(QString player)
{
    whosTurn_ = player;

    whosTurnText->setPlainText(QString("whos turn: ") + player);
}


void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(cardToPlace){
        cardToPlace->setPos(event->pos());

    }
    QGraphicsView::mouseMoveEvent(event);
}

void Game::pickUpCard(Hex *card)
{
    if((card->getOwner() == getWhosTurn()) && cardToPlace == NULL){
        cardToPlace = card;
        originalPos = card->pos();
        return;
    }
}

void Game::placeCard(Hex *hexToReplace)
{
    cardToPlace->setPos(hexToReplace->pos());
    hexboard->getHexes().removeAll(hexToReplace);
    hexboard->getHexes().append(cardToPlace);

    scene->removeItem(hexToReplace);
    cardToPlace->setIsPlaced(false);

    removeFromDeck(cardToPlace,getWhosTurn());
    cardToPlace = NULL;

    nextPlayerTurn();
}

void Game::nextPlayerTurn()
{
    if(getWhosTurn() == QString("PLAYER1")){
        setWhosTurn(QString("PLAYER2"));
    }else{
        setWhosTurn(QString("PLAYER1"));
    }

}

void Game::removeFromDeck(Hex *card, QString player)
{
    if(player == QString("PLAYER1")){
        player1Cards.removeAll(card);
    }
    if(player == QString("PLAYER2")){
        player2Cards.removeAll(card);
    }
}

void Game::createNewCards(QString player)
{
    Hex *card = new Hex();
    card->setOwner(player);
    card->setIsPlaced(false);

    if(player == QString("PLAYER1")){
        player1Cards.append(card);
    }else
        player2Cards.append(card);

   // drawCards();
}

void Game::createInitialCards()
{
    for(size_t i=0;i<5;i++){
        createNewCards(QString("PLAYER1"));
    }

    for(size_t i=0;i<5;i++){
        createNewCards(QString("PLAYER2"));
    }

    drawCards();
}

void Game::drawCards()
{
   /* for(size_t i = 0 , n = player1Cards.size() ; i < n ; i++){
        scene->removeItem(player1Cards[i]);
    }

    for(size_t i = 0 , n = player2Cards.size() ; i < n ; i++){
        scene->removeItem(player2Cards[i]);
    }
*/
    for(size_t i = 0,n=player1Cards.size();i<n;i++){
        Hex* card=player1Cards[i];
        card->setPos(13,25+85*i);
        scene->addItem(card);
    }

    for(size_t i = 0,n=player2Cards.size();i<n;i++){
        Hex* card=player2Cards[i];
        card->setPos(13+874,25+85*i);
        scene->addItem(card);
    }
}

void Game::start()
{
    scene->clear();
    hexboard=new HexBoard();
    hexboard->placeHexes(240,30,7,7);
    drawGUI();
    createInitialCards();
}
