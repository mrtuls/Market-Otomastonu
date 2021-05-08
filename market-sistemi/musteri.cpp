#include "musteri.h"
#include "ui_musteri.h"
#include <QMessageBox>

musteri::musteri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::musteri)
{
    ui->setupUi(this);

    ui->lineEdit_urun_ismi->setReadOnly(true);
    ui->lineEdit_genel->setReadOnly(true);
    ui->lineEdit_toplam_tutar->setReadOnly(true);
    ui->lineEdit_adet_fiyat->setReadOnly(true);



}

musteri::~musteri()
{
    delete ui;


}



void musteri::on_pushButton_mus_liste_clicked()
{
    MainWindow conn;

    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("select * from Test2 ");



    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();


    qDebug()<<(modal->rowCount());
}

void musteri::on_pushButton_hesapla_clicked()
{

    int ucret,toplamucret=0,eklencek,adet;
        adet = ui->lineEdit_adet->text().toInt();
        ucret=ui->lineEdit_adet_fiyat->text().toInt();
        eklencek=ui->lineEdit_toplam_tutar->text().toInt();


        toplamucret=(adet*ucret)+eklencek;


        ui->lineEdit_genel->setText(QString::number(ucret));
        ui->lineEdit_toplam_tutar->setText(QString::number(toplamucret));

}

void musteri::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();

    MainWindow conn;



    if (!conn.connOpen())
    {
        qDebug()<<"Database bağlantı hatası";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Test2 where urunkodu= '"+val+"' or urunismi = '"+val+"' or skt = '"+val+"'or fiyat = '"+val+"'");

    if (qry.exec())
    {
        while (qry.next()) {
            ui->lineEdit_urun_ismi->setText(qry.value(1).toString());
            ui->lineEdit_adet_fiyat->setText(qry.value(3).toString());


        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("Hata"), qry.lastError().text());
    }
}
