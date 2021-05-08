#ifndef MUSTERI_H
#define MUSTERI_H

#include <QDialog>
#include "mainwindow.h"



namespace Ui {
class musteri;
}

class musteri : public QDialog
{
    Q_OBJECT

public:
    explicit musteri(QWidget *parent = nullptr);
    ~musteri();

private slots:
    void on_pushButton_mus_liste_clicked();

    void on_pushButton_hesapla_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::musteri *ui;
};

#endif // MUSTERI_H
