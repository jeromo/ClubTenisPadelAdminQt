#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QtDebug>



QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("club");
    db.setHostName("127.0.0.1");
    db.setUserName("club");
    db.setPassword("club");
    db.setPort(3306);

    if (!db.open())
        return db.lastError();

    return QSqlError();
}

#endif // INITDB_H
