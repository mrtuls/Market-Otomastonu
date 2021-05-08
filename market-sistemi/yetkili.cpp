#include "yetkili.h"
#include "ui_yetkili.h"
#include <QMessageBox>

yetkili::yetkili(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::yetkili)
{

    ui->setupUi(this);

     MainWindow conn;

    if (!conn.connOpen())
    {
        ui->label_status->setText("Database bağlantı hatası!");
    }
    else
    {
        ui->label_status->setText("Database bağlantısı başarılı..");

    }
}

yetkili::~yetkili()
{
    delete ui;
}


class marketYetkili {

public:
    QString urunAdi,urunKodu,urunSkt,urunFiyati;

    QString getUrun_adi(){return urunAdi;}
    void setUrun_adi(QString urunismi) {urunAdi = urunismi;}

    QString getUrun_kodu(){return urunKodu;}
    void setUrun_kodu(QString urunNo) {urunKodu = urunNo;}

    QString getUrun_skt(){return urunSkt;}
    void setUrun_skt(QString sonKT) {urunSkt = sonKT;}

    QString getUrun_fiyat(){return urunFiyati;}
    void setUrun_fiyat(QString urunBedel) {urunFiyati = urunBedel;}

};

void yetkili::on_pushButton_urun_ekle_clicked()
{
    MainWindow conn;

    marketYetkili yetkili;

    //urunAdi = ui->lineEdit_urun_ismi->text();
    //urunKodu = ui->lineEdit_urun_kodu->text();
    //urunMiktari = ui->lineEdit_urun_miktar->text();
    //urunSkt = ui->lineEdit_skt->text();
    //urunFiyati = ui->lineEdit_urun_fiyati->text();

    yetkili.setUrun_adi(ui->lineEdit_urun_ismi->text());
    yetkili.setUrun_fiyat(ui->lineEdit_urun_fiyati->text());
    yetkili.setUrun_kodu(ui->lineEdit_urun_kodu->text());
    yetkili.setUrun_skt( ui->lineEdit_skt->text());

    if (!conn.connOpen())
    {
        qDebug()<<"Database bağlantı hatası";
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into Test2 (urunkodu,urunismi,skt,fiyat) values ('"+yetkili.getUrun_kodu()+"','"+yetkili.getUrun_adi()+"','"+yetkili.getUrun_skt()+"','"+yetkili.getUrun_fiyat()+"')");

    if (qry.exec())
    {
        QMessageBox::information(this, tr("Kayıt"), tr("Kayıt Başarılı"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("Hata"), qry.lastError().text());
    }

}

void yetkili::on_pushButton_urun_duzenle_clicked()
{

}

void yetkili::on_pushButton_urun_silme_clicked()
{
    MainWindow conn;
    marketYetkili yetkili;
    QString urunAdi,urunKodu,urunMiktari;
//    urunAdi = ui->lineEdit_urun_ismi->text();
    urunKodu = ui->lineEdit_urun_kodu->text();
//    urunMiktari = ui->lineEdit_urun_miktar->text();

    yetkili.setUrun_adi(ui->lineEdit_urun_ismi->text());
    yetkili.setUrun_fiyat(ui->lineEdit_urun_fiyati->text());
    yetkili.setUrun_kodu(ui->lineEdit_urun_kodu->text());
    yetkili.setUrun_skt( ui->lineEdit_skt->text());


    if (!conn.connOpen())
    {
        qDebug()<<"Database bağlantı hatası";
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from Test2 where urunkodu = '"+yetkili.getUrun_kodu()+"'");

    if (qry.exec())
    {
        QMessageBox::information(this, tr("Ürün Sime"), tr("Ürün Silinmiştir"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("Hata"), qry.lastError().text());
    }
}

void yetkili::on_pushButton_urun_listele_clicked()
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

void yetkili::on_pushButton_urun_duzenleme_clicked()
{
    MainWindow conn;

        marketYetkili yetkili;
    /*  QString urunAdi,urunKodu,urunMiktari,urunSkt,urunFiyati;
        urunAdi = ui->lineEdit_urun_ismi->text();
        urunKodu = ui->lineEdit_urun_kodu->text();
        urunMiktari = ui->lineEdit_urun_miktar->text();
        urunSkt = ui->lineEdit_skt->text();
        urunFiyati = ui->lineEdit_urun_fiyati->text();
    */

        yetkili.setUrun_adi(ui->lineEdit_urun_ismi->text());
        yetkili.setUrun_fiyat(ui->lineEdit_urun_fiyati->text());
        yetkili.setUrun_kodu(ui->lineEdit_urun_kodu->text());
        yetkili.setUrun_skt( ui->lineEdit_skt->text());

        if (!conn.connOpen())
        {
            qDebug()<<"Database bağlantı hatası";
        }

        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("update Test2 set urunkodu = '"+yetkili.getUrun_kodu()+"',urunismi='"+yetkili.getUrun_adi()+"',skt='"+yetkili.getUrun_skt()+"',fiyat='"+yetkili.getUrun_fiyat()+"' where urunkodu = '"+yetkili.getUrun_kodu()+"' ");

        if (qry.exec())
        {
            QMessageBox::information(this, tr("Düzenleme"), tr("Düzenleme Başarılı"));
            conn.connClose();
        }
        else
        {
            QMessageBox::critical(this, tr("Hata"), qry.lastError().text());
        }

}

void yetkili::on_tableView_activated(const QModelIndex &index)
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
            ui->lineEdit_urun_kodu->setText(qry.value(0).toString());
            ui->lineEdit_urun_ismi->setText(qry.value(1).toString());
            ui->lineEdit_skt->setText(qry.value(2).toString());
            ui->lineEdit_urun_fiyati->setText(qry.value(3).toString());
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("Hata"), qry.lastError().text());
    }
}
