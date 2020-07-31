#include "home.h"
#include "ui_home.h"

#include <QFile>
#include <QFileDialog>
#include <QFileSelector>
#include <QStandardItemModel>

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
        //
    }
    // Tabela za prikaz informacija
    ui -> prikaz ->setDisabled(false);
    ui -> prikaz -> setStyleSheet("background-color: #25ad2a; border-style: outset; "
                                "border-width: 2px; border-radius: 10px; border-color: beige; padding: 6px; color: #fff;");

    if(ui -> select -> isChecked())
    {
        return;
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
    ui -> adresa -> setDisabled(true);

    // omogući checkboxeve
    ui -> select -> setDisabled(false);
    ui -> other  -> setDisabled(false);
    }
}
