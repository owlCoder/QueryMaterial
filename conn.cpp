#include "conn.h"

Conn::Conn()
{

}

bool Conn::dbOpen(QString put)
{
    dbPutanja = put;
    bool open = false;

    db.setDatabaseName(dbPutanja);
    if(db.open())
        open = true;

    QSqlQuery upit;
    upit.exec("PRAGMA foreign_key = ON;");

    return open;
}

void Conn::dbClose()
{
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
