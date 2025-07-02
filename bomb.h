#ifndef BOMB_H
#define BOMB_H
//Baran Kanat 22100011013
#include <QPushButton>

class Bomb : public QPushButton
{
    Q_OBJECT
public:
    Bomb(QWidget *point = 0);
    bool statusBomb;
    bool cutBomb;

public slots:
    void changeStatusBomb();

};

#endif // BOMB_H
