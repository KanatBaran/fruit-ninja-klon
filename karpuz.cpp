//Baran Kanat 22100011013
#include "karpuz.h"

Karpuz::Karpuz(QWidget *p):QPushButton(p) {

    status = false;
    cut = false;
    escape = false;

    connect(this, SIGNAL(clicked()),this,SLOT(changeStatus()));

}

void Karpuz::changeStatus()
{
    status = !status;
}
