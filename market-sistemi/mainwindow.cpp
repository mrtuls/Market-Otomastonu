#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "yetkili.h"
#include "musteri.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!connOpen())
    {
        ui->statusbar->showMessage("Database bağlantı hatası!");
    }
    else
    {
        ui->statusbar->showMessage("Database bağlantısı başarılı..");

    }

    mus_isim = ui->lineEdit_isim_musteri->text();
    mus_soyisim = ui->lineEdit_soyisim_musteri->text();


}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_yetkili_clicked()
{
    QString yAdi,ySifre;
    yAdi = ui->lineEdit_isim_yetkili->text();
    ySifre = ui->lineEdit_sifre_yetkili->text();

    if (!connOpen())
    {
        qDebug()<<"Database bağlantı hatası";
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Test where username ='"+yAdi+"'and password = '"+ySifre+"' ");

    if (qry.exec())
    {
        int sayac=0;
        while (qry.next())
        {
            sayac++;
        }
        if (sayac==1)
        {
            QMessageBox::information(this, tr("Giriş"),tr("Giriş Başarılı") );
            connClose();
            //this->hide();

            yetkili yetki;
            yetki.setModal(true);
            yetki.exec();
        }
        if (sayac>1)
        {
           QMessageBox::information(this, tr(""),tr("") );
        }
        if (sayac<1)
        {
            QMessageBox::information(this, tr("Tekrar Deneyiniz"),tr("İsim veya şifre hatalı !") );
        }
    }





}

void MainWindow::on_pushButton_musteri_clicked()
{


    QMessageBox::information(this, tr("Hoşgeldiniz"), tr("Giriş Başarılı"));
   // ui->label_5->setText(" hosgeldin "+mus_isim+"");

    //this->hide();
    musteri mus;
    mus.setModal(true);
    mus.exec();





}
