#ifndef DIALOGSTART_H
#define DIALOGSTART_H
//Baran Kanat 22100011013
#include <QDialog>
#include <QList>
#include <QFile>
#include <QTextStream>

namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget *parent = nullptr);
    ~DialogStart();

public slots:
    QString getData();

private slots:
    void on_pushButtonKolay_clicked();

    void on_pushButtonOrta_clicked();

    void on_pushButtonZor_clicked();

    void on_pushButtoimkansiz_clicked();

    int maxSkor();

private:
    Ui::DialogStart *ui;
    QString data = "";

};

#endif // DIALOGSTART_H
