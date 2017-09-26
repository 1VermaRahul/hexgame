#ifndef HEX_H
#define HEX_H

#include<QGraphicsPolygonItem>
#include<QGraphicsSceneMouseEvent>

class Hex:public QGraphicsPolygonItem{
public:
    Hex(QWidget *parant=NULL);
    int getAttackOf(int side);
    bool getIsPlaced();
    void setIsPlaced(bool b);
    QString getOwner();
    void setAttackOf(int side,int Attack);
    void setOwner(QString player);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    bool isPlaced;
    QString owner;
    int side0Attack;
    int side1Attack;
    int side2Attack;
    int side3Attack;
    int side4Attack;
    int side5Attack;
};

#endif // HEX_H
