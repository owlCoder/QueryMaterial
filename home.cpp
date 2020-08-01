#include "home.h"
#include "ui_home.h"

#include <QFile>
#include <QFileDialog>
#include <QFileSelector>
#include <QMessageBox>
#include <QSqlQuery>
#include <QStandardItemModel>

#include "conn.h"

home::home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::home)
{
    ui->setupUi(this);

    // onemogući unos
    ui -> unos -> setDisabled(true);
    ui -> unos -> setStyleSheet("background-color: #5f7064; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");
    // onemogući dugme
    ui -> izvrsi -> setDisabled(true);
    ui -> izvrsi -> setStyleSheet("background-color: #5f7064; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");

    // onemogući checkboxeve
    ui -> select -> setDisabled(true);
    ui -> other  -> setDisabled(true);

    // onemoguci adresu baze QLineEdit
    ui -> adresa -> setDisabled(true);

    ui -> statusBar -> showMessage("© 2020. Query Material. Podrži projekte otvorenog koda!");
}

home::~home()
{
    delete ui;
}


void home::on_izvrsi_clicked()
{
    QString uneto = ui -> unos -> toPlainText();

    if(uneto == "")
    {
       QMessageBox::warning(this, "Upozorenje!", "<font size=4>Polje za upit je prazno!</font>");
    }
    else {
        // Tabela za prikaz informacija
        ui -> prikaz ->setDisabled(false);
        ui -> prikaz -> setStyleSheet("background-color: #25ad2a; border-style: outset; "
                                    "border-width: 2px; border-radius: 10px; border-color: beige; color: #fff;");

        if(ui -> select -> isChecked())
        {
            QString up = ui -> unos -> toPlainText();

            Conn c;
            QString adr = ui -> adresa -> text();
            QSqlQuery upit;

            c.dbOpen(adr);

            if(upit.exec(up))
            {
                window() -> resize(820, 586);

                QSqlQueryModel *modal = new QSqlQueryModel();
                modal -> setQuery(upit);
                ui -> prikaz -> setModel(modal);
            }
            else
            {
                QMessageBox::critical(this, "Greška!", "<font size=4>Traženi upit nije moguće "
                                                       "izvršiti jer se tražena tabela ne nalazi u "
                                                       "bazi podataka ili je upit sintaksno pogrešan!</font>");
            }
            c.dbClose();
        }


          if(ui -> other -> isChecked())
            {
                QString up = ui -> unos -> toPlainText();
                Conn c;
                QString adr = ui -> adresa -> text();
                QSqlQuery upit;

                c.dbOpen(adr);

                if(upit.exec(up))
                {
                    QMessageBox::information(this, "Obaveštenje", "<font size=4>Upit je uspešno izvršen!</font>");
                }
                else
                {
                    QMessageBox::critical(this, "Greška!", "<font size=4>Traženi upit nije moguće "
                                                           "izvršiti jer se tražena tabela ne nalazi u "
                                                           "bazi podataka ili je upit sintaksno pogrešan!</font>");

                }
                c.dbClose();
            }

          ui -> unos -> clear();
     }
}

void home::on_close_clicked()
{
    this -> close();
}

void home::on_select_clicked()
{
    // Prvi ček boks
    ui -> unos ->setDisabled(false);
    ui -> unos -> setStyleSheet("background-color: #124191; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");

    // dugme omogući
    ui -> izvrsi -> setDisabled(false);
    ui -> izvrsi -> setStyleSheet("background-color: #975abc; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");
}

void home::on_other_clicked()
{
    window() -> resize(820, 386);

    // Drugi ček boks
    ui -> unos ->setDisabled(false);
    ui -> unos -> setStyleSheet("background-color: #124191; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");

    // dugme omogući
    ui -> izvrsi -> setDisabled(false);
    ui -> izvrsi -> setStyleSheet("background-color: #975abc; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");
}

void home::on_browse_clicked()
{
    QString putanja = QFileDialog::getOpenFileName(this, tr("Odaberi bazu podataka"),
                                                    "C:/",
                                                   tr("Baza podataka (*.db)"));

    if( putanja != "" )
    {
    ui -> adresa -> setText(putanja);
    //ui -> adresa -> setDisabled(true);

    // omogući checkboxeve
    ui -> select -> setDisabled(false);
    ui -> other  -> setDisabled(false);
    }
}
