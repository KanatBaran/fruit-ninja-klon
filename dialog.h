#ifndef DIALOG_H
#define DIALOG_H
//Baran Kanat 22100011013
#include <QDialog>
#include <QTimer>
#include <QList>
#include <QFile>
#include <QTextStream>
#include "karpuz.h"
#include "bomb.h"
#include "dialogstart.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QString data, QWidget *parent = nullptr);
    ~Dialog();
    void olusturKarpuz();
    void kayanKarpuz();
    void KontrolKarpuz();
    void GameTime();
    void kacanKarpuz();

    void olusturBomba();
    void kayanBomb();
    void kontrolBomb();

public:
    Ui::Dialog *ui;
    int gameTimer;
    int GameStatus;
    QTimer *Game = new QTimer(this);
    QTimer *Time = new QTimer(this);
    QTimer *Move = new QTimer(this);
    QTimer *Control = new QTimer(this);
    QList<Karpuz*> Karpuzlar;
    QList<Karpuz*> cutKarpuz;
    QList<Karpuz*> escapeKarpuz;

    QTimer *BombCreataTimer = new QTimer(this);
    QTimer *BombMoveTimer = new QTimer(this);
    QTimer *BombControlTimer = new QTimer(this);
    QList<Bomb*> Bombalar;
    QList<Bomb*> cutBomb;

};
#endif // DIALOG_H
