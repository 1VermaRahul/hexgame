#include"hex.h"
#include<QBrush>
#include"game.h"
#include<QDebug>

extern Game *game;
Hex::Hex(QWidget *parant)
{
    QVector<QPointF> hexpoints;
    hexpoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2) << QPointF(1,2) << QPointF(0,1);

    int SCALE_BY = 40;
    for(size_t i=0, n=hexpoints.size();i<n;i++){
        hexpoints[i]*=SCALE_BY;
    }

    QPolygonF hexagon(hexpoints);
    setPolygon(hexagon);

    isPlaced = false;
}

bool Hex::getIsPlaced()
{
    return isPlaced;
}

void Hex::setIsPlaced(bool b)
{
    isPlaced = b;
}

QString Hex::getOwner()
{
    return owner;
}

void Hex::setOwner(QString player)
{
    owner = player;

    if(player == QString("NOONE")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if(player == QString("PLAYER1")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }

    if(player == QString("PLAYER2")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(getIsPlaced() == false){
        game->pickUpCard(this);
        //isPlaced = true;
    }else{
      //  qDebug()<<"ran";
        game->placeCard(this);
       // isPlaced = false;
    }
}

