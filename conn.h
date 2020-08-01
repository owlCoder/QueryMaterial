#ifndef CONN_H
#define CONN_H

#include <QtSql/QtSql>

class Conn
{
    public:
        Conn();
        bool dbOpen(QString);
        void dbClose();
        QString getDb() { return dbPutanja; }
        void setDb(QString db) { dbPutanja = db; }

    private:
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        QString dbPutanja = "";
    };

#endif // CONN_H
