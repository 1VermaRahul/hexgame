#ifndef HEXBOARD_H
#define HEXBOARD_H
#include<QList>
#include"hex.h"

class HexBoard{
public:
    HexBoard();
    QList<Hex *> getHexes();
    void placeHexes(int x,int y,int cols,int rows);
private:
    QList<Hex *> hexes;
    void createHexColumn(int x,int y,int numOfRows);
};

#endif // HEXBOARD_H
