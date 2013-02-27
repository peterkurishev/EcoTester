#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // using SQLITE driver
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("customdb.db");

    if (db.open()) {
        // Try to locate the contacts database.
        // If it is not available create it.
//        if (db.tables().indexOf("contacts") == -1) {
//            QSqlQuery query(db);
//            query.prepare("CREATE TABLE contacts (name VARCHAR(32), phone VARCHAR(16))");
//            query.exec();
//                qCritical() << query.lastError();
//        }
    } else {
//        qCritical() << db.lastError();
    }

    MainWindow w(&db);
    w.show();
    
    return a.exec();
}
