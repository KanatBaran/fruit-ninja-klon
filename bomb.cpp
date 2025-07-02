//Baran Kanat 22100011013
/*
Ekstra Fonksiyon: Burada karpuzlar disinda bomba sinifi icin yapici metot ve bir fonksiyon
vardir. Bomba ozelligi, bombaya tiklandigi zaman skordan bir puan azaltir.
*/
#include "bomb.h"

Bomb::Bomb(QWidget *point):QPushButton(point) {

    statusBomb = false;
    cutBomb = false;

    connect(this, SIGNAL(clicked()),this,SLOT(changeStatusBomb()));


}

void Bomb::changeStatusBomb()
{
    statusBomb = !statusBomb;
}
