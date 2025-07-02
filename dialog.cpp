//Baran Kanat 22100011013
#include "dialog.h"
#include "ui_dialog.h"
#include <QRandomGenerator>
#include <QMessageBox>




Dialog::Dialog(QString data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //degiskenler
    int controlMove = 0;
    int controlTime = 0;
    int controlBombC = 0;
    int controlBombM = 0;
    if(data == "kolay")
    {

        controlMove = 20;
        controlTime = 1000;
        controlBombC = 5000;
        controlBombM = 20;
    }
    else if(data == "orta")
    {
        controlMove = 10;
        controlTime = 600;
        controlBombC = 2500;
         controlBombM = 10;

    }
    else if(data == "zor")
    {
        controlMove = 5;
        controlTime = 600;
        controlBombC = 1500;
        controlBombM = 5;
    }
    else if(data == "imkansiz")
    {
        controlMove = 0.1;
        controlTime = 600;
        controlBombC = 250;
        controlBombM = 5;
    }
    else
    {
        controlMove = 5;
        controlTime = 600;
        controlBombC = 1500;
        controlBombM = 5;
    }

    gameTimer = 30;
    GameStatus = 0;

    connect(Game, &QTimer::timeout, this, &Dialog::GameTime);
    connect(Time, &QTimer::timeout, this, &Dialog::olusturKarpuz);
    connect(Move, &QTimer::timeout, this, &Dialog::kayanKarpuz);
    connect(Control, &QTimer::timeout, this, &Dialog::KontrolKarpuz);
    connect(Control, &QTimer::timeout, this, &Dialog::kacanKarpuz);

    connect(BombCreataTimer, &QTimer::timeout, this, &Dialog::olusturBomba);
    BombCreataTimer->start(controlBombC);
    connect(BombMoveTimer, &QTimer::timeout, this, &Dialog::kayanBomb);
    BombMoveTimer->start(controlBombM);
    connect(BombControlTimer, &QTimer::timeout, this, &Dialog::kontrolBomb);
    BombControlTimer->start(1);

    Game->start(1000);
    Control->start(1);
    Time->start(controlTime);
    Move->start(controlMove);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::olusturKarpuz()
{

    /* Dosya Okuma İşlemi */
    //Konumlar.txt Build klasörüne atmanız yeterlidir.
    QFile file("konumlar.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Dosya Hatası!", "Oyunun çalışması için gerekli konumlar.txt dosyasına ulaşılamıyor.");
        return;
    }

    QTextStream fileKonumlar(&file);
    QStringList konumlar;

    while (!fileKonumlar.atEnd())
    {
        QString line = fileKonumlar.readLine();
        konumlar.append(line);
    }

    file.close();
    /* ./Dosya Okuma İşlemi */

    int randomIndex = QRandomGenerator::global()->bounded(0, konumlar.size());
    QStringList konum = konumlar[randomIndex].split(" ");
    int x = konum[0].toInt();
    int y = konum[1].toInt();

    Karpuz *karpuz = new Karpuz(this);
    karpuz->setStyleSheet("border-image: url(':/images/images/1.png');");
    karpuz->setGeometry(x,y,100,100);
    Karpuzlar.append(karpuz);
    karpuz->show();
}

void Dialog::kayanKarpuz()
{
    for(int i = 0; i < Karpuzlar.size(); i++)
    {
        if(Karpuzlar[i]->status == false && Karpuzlar[i]->cut == false)
        {
            Karpuzlar[i]->setGeometry(Karpuzlar[i]->x(),
                                      Karpuzlar[i]->y()+1,
                                      Karpuzlar[i]->width(),
                                      Karpuzlar[i]->height());

        }
    }
}

void Dialog::KontrolKarpuz()
{
    int  i = 0;

    for(; i < Karpuzlar.size(); i++)
    {
        if(Karpuzlar[i]->status == true && Karpuzlar[i]->cut == false)
        {
            cutKarpuz.append(Karpuzlar[i]); //kesilen karpuzlara ekler
            Karpuzlar[i]->cut = true; //kesilen karpuzu tekrardan eklenmesini engeller.

            Karpuzlar[i]->setStyleSheet("border-image: url(':/images/images/2.png');");

            QTimer::singleShot(3000, [this, i]() {
                Karpuzlar[i]->hide();
            });

        }
    }

    ui->labelCut->setText(QString::number(cutKarpuz.size()));
}

void Dialog::GameTime()
{
    gameTimer--;
    if(gameTimer < 0)
    {
        // Tüm sayaçları durdur.
        Move->stop();
        Time->stop();
        Game->stop();
        Control->stop();

        BombCreataTimer->stop();
        BombMoveTimer->stop();

        /* Skorlar Dosya İşlemi */
        //Konumlar.txt Build klasörüne atmanız yeterlidir.
        QFile file("skorlar.txt");

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Dosya Hatası!", "Oyunun çalışması için gerekli skorlar.txt dosyasına ulaşılamıyor.");
            return;
        }

        QTextStream fileSkorlar(&file);
        QStringList skorlar;

        while (!fileSkorlar.atEnd())
        {
            QString line = fileSkorlar.readLine();
            skorlar.append(line);
        }

        file.close();
        /* ./Skorlar Dosya İşlemi */

        int Skor = cutKarpuz.size(); //guncel skor

        //skorlar dosyasındaki en yüksek skoru bulalım.
        int maxSkor = 0;
        for(int i = 0; i < skorlar.size(); i++)
        {
            if(skorlar[i].toInt()  > maxSkor)
            {
                maxSkor = skorlar[i].toInt();
            }
        }

        if(Skor > maxSkor)
        {
            QMessageBox::information(this,"Bilgi!",
            "Oyun Bitti! Tebrikler Maksimum Skor Sizde!\n"
            "Kesilen Karpuz Sayısı: " + QString::number(cutKarpuz.size()) +
            "\nKaçırılan Karpuz Sayısı: " + QString::number(escapeKarpuz.size()) +
            "\nMaksimum Skor: " + QString::number(maxSkor));
        }
        else
        {
            QMessageBox::information(this,"Bilgi!",
            "Oyun Bitti! Maksimum Skoru Geçemediniz\n"
            "Kesilen Karpuz Sayısı: " + QString::number(cutKarpuz.size()) +
            "\nKaçırılan Karpuz Sayısı: " + QString::number(escapeKarpuz.size()) +
            "\nMaksimum Skor: " + QString::number(maxSkor));
        }

        /* Skor Dosya Kaydetme İşlemi */
        if(!file.open(QIODevice::Append))
        {
            QMessageBox::critical(this, "Dosya Hatası!", "Oyunun çalışması için gerekli skorlar.txt dosyasına ulaşılamıyor.");
            return;
        }

        fileSkorlar << QString::number(Skor) << "\n";

        file.close();
        /*./Skor Dosya Kaydetme İşlemi */

        //Oyunu Kapat
        this->close();
    }
    else
    {
        ui->labelSure->setText(QString::number(gameTimer));
    }
}

void Dialog::kacanKarpuz()
{
    int i;

    for(i = 0; i < Karpuzlar.size(); i++)
    {
        if(Karpuzlar[i]->y() > 800 && Karpuzlar[i]->escape == false)
        {
            Karpuzlar[i]->escape = true;
            escapeKarpuz.append(Karpuzlar[i]);
            ui->labelKacanKarpuz->setText(QString::number(escapeKarpuz.size()));
        }
    }

}

void Dialog::olusturBomba()
{
    /* Dosya Okuma İşlemi */
    //Konumlar.txt Build klasörüne atmanız yeterlidir.
    QFile file("konumlar.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Dosya Hatası!", "Oyunun çalışması için gerekli konumlar.txt dosyasına ulaşılamıyor.");
        return;
    }

    QTextStream fileKonumlar(&file);
    QStringList konumlar;

    while (!fileKonumlar.atEnd())
    {
        QString line = fileKonumlar.readLine();
        konumlar.append(line);
    }

    file.close();
    /* ./Dosya Okuma İşlemi */

    int randomIndex = QRandomGenerator::global()->bounded(0, konumlar.size());
    QStringList konum = konumlar[randomIndex].split(" ");
    int x = konum[0].toInt();
    int y = konum[1].toInt();


    Bomb *bomba = new Bomb(this);
    bomba->setStyleSheet("border-image: url(':/images/images/bomb.png');");
    bomba->setGeometry(x,y,100,100);
    Bombalar.append(bomba);
    bomba->show();

}

void Dialog::kayanBomb()
{
    for(int i = 0; i < Bombalar.size(); i++)
    {
        if(Bombalar[i]->statusBomb == false && Bombalar[i]->cutBomb == false)
        {
            Bombalar[i]->setGeometry(Bombalar[i]->x(),
                                      Bombalar[i]->y()+1,
                                      Bombalar[i]->width(),
                                      Bombalar[i]->height());

        }
    }
}

void Dialog::kontrolBomb()
{
    int  i = 0;

    for(; i < Bombalar.size(); i++)
    {
        if(Bombalar[i]->statusBomb == true && Bombalar[i]->cutBomb == false)
        {
            cutBomb.append(Bombalar[i]); //kesilen bombalari ekler
            Bombalar[i]->cutBomb = true; //kesilen bombayı tekrardan eklenmesini engeller.

            Bombalar[i]->setStyleSheet("border-image: url(':/images/images/bomb2.png');");

            if(cutKarpuz.size() > 0)
            {
                cutKarpuz.pop_back();
            }
            QTimer::singleShot(3000, [this, i]() {
                Bombalar[i]->hide();
            });

        }
    }
}
