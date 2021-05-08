#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public :
    QString mus_isim ;
    QString mus_soyisim;

    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb =  QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/monster/OneDrive/Masaüstü/db/mydb.db");

        if (!mydb.open())
          {  qDebug()<<("Database bağlantı hatası!");
        return false;
        }

        else
         {   qDebug()<<("Database bağlantısı başarılı..");
        return true;
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_yetkili_clicked();

    void on_pushButton_musteri_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
