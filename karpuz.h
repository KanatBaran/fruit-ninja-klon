#ifndef KARPUZ_H
#define KARPUZ_H
//Baran Kanat 22100011013
#include <QPushButton>

class Karpuz : public QPushButton
{
    Q_OBJECT
public:
    Karpuz(QWidget *p = 0);
    bool status;
    bool cut;
    bool escape;

public slots:
    void changeStatus();


};

#endif // KARPUZ_H
