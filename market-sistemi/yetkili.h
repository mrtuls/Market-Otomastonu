#ifndef YETKILI_H
#define YETKILI_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class yetkili;
}

class yetkili : public QDialog
{
    Q_OBJECT

public:

    MainWindow conn;
    explicit yetkili(QWidget *parent = nullptr);
    ~yetkili();

private slots:
    void on_pushButton_urun_ekle_clicked();

    void on_pushButton_urun_duzenle_clicked();

    void on_pushButton_urun_silme_clicked();

    void on_pushButton_urun_listele_clicked();

    void on_pushButton_urun_duzenleme_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::yetkili *ui;
};

#endif // YETKILI_H
