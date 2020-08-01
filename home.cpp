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

    ui -> prikaz -> setDisabled(true);
    ui -> prikaz -> setStyleSheet("background-color: #5f7064; border-style: outset; "
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

    // sakri error
    ui -> error -> hide();
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
       ui -> error -> setText("Unesi i ne glumi!");
    }
    // Tabela za prikaz informacija
    ui -> prikaz ->setDisabled(false);
    ui -> prikaz -> setStyleSheet("background-color: #25ad2a; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");

    if(ui -> select -> isChecked())
    {
        QString up = ui -> unos -> toPlainText();

        Conn c;
        QString adr = ui -> adresa -> text();
        QSqlQuery upit;

        c.dbOpen(adr);

        if(!upit.exec(up))
        {
            QSqlQueryModel *modal = new QSqlQueryModel();
            modal -> setQuery(upit);
            ui -> prikaz -> setModel(modal);

             // qDebug() << upit.lastError();
        }
        else
        {
            ui -> error -> show();

           ui -> error -> setText("\n\nTRAŽENI UPIT NIJE MOGUĆE "
                                  "IZVRŠITI JER SE TRAŽENA TABELA NE NALAZI U BAZI PODATAKA ILI JE UPIT SINTAKSNO POGREŠAN!");

        }
        c.dbClose();
    }

        if(ui -> other -> isChecked())
        {
            QString up = ui -> unos -> toPlainText();
            up.replace("\\n", " ");

            Conn c;
            QString adr = ui -> adresa -> text();
            QSqlQuery upit;

            c.dbOpen(adr);

            if(upit.exec(up) == true)
            {
                QMessageBox::information(this, "Obaveštenje", "Upit je uspešno izvršen!\n\n"
                                                              "Dev code:" + upit.lastQuery());
            }
            else
            {
                QMessageBox::critical(this, "Greška!", "TRAŽENI UPIT NIJE MOGUĆE "
                                                       "IZVRŠITI JER SE TRAŽENA TABELA NE NALAZI U "
                                                       "BAZI PODATAKA ILI JE UPIT SINTAKSNO POGREŠAN!");

            }
            c.dbClose();
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
