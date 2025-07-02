//Baran Kanat 22100011013
/*
Ekstra Fonksiyon: Burasi acilis ekranina attir. Acilis ekraninda maksimum skor gosterilir ve oyun
modu secilir.
*/
#include "dialogstart.h"
#include "ui_dialogstart.h"

#include <QPainter>
#include <QMessageBox>

extern QString data;

DialogStart::DialogStart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogStart)
{
    ui->setupUi(this);
    //ui->labelBack->lower();
    setStyleSheet("DialogStart { background-image:url(:/images/images/background.png); background-repeat: no-repeat; }");
    ui->labelSkor->setText(QString::number(maxSkor()));

}

DialogStart::~DialogStart()
{
    delete ui;
}

QString DialogStart::getData()
{
    return data;
}


void DialogStart::on_pushButtonKolay_clicked()
{
    data = "kolay";
    this->close();
}


void DialogStart::on_pushButtonOrta_clicked()
{
    data = "orta";
    this->close();
}


void DialogStart::on_pushButtonZor_clicked()
{
    data = "zor";
    this->close();
}


void DialogStart::on_pushButtoimkansiz_clicked()
{
    data = "imkansiz";
    this->close();
}

int DialogStart::maxSkor()
{
    /* Skorlar Dosya İşlemi */
        QFile file("skorlar.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Dosya Hatası!", "Oyunun çalışması için gerekli skorlar.txt dosyasına ulaşılamıyor.");
        return 0;
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

    //skorlar dosyasındaki en yüksek skoru bulalım.
    int maxSkor = 0;
    for(int i = 0; i < skorlar.size(); i++)
    {
        if(skorlar[i].toInt()  > maxSkor)
        {
            maxSkor = skorlar[i].toInt();
        }
    }

    return maxSkor;
}

