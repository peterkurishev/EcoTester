#include <QApplication>
#include "mainwindow.h"
#include "choosetest.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "exceptions.h"
#include <QMessageBox>
#include <QErrorMessage>
#include <QTextCodec>
#include "personaldatadialog.h"
#include "reportviewdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool IsTeachingMode = false;    // Включен ли режим обучения?

    // После нижеследующей строки можно использовать русский текст в UTF-8
//    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );

    // Открываем базу данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("customdb.db");
    bool ok = db.open();

    if (!ok) {
        // Exception or whatever
        QMessageBox::critical(0, "Ошибка БД", "Невозможно открыть базу данных");
        exit(10001);    // 10001 - ошибка открытия данных
    }

    PersonalDataDialog pd;
    unsigned int testeeId = 0;
    int rc = pd.exec();
    if(!rc) {
        exit(0);
    }

    if(pd.isTeachingMode()) {
        IsTeachingMode = pd.isTeachingMode();
    }

    if(!IsTeachingMode) {
        if(rc && pd.getName().length() > 0) {
            //Сохраняем персональные данные в testees
            QSqlQuery persData;
            persData.prepare("INSERT INTO testees (name, position, company) VALUES (:nn, :pp, :cc)");
            persData.bindValue(":nn", pd.getName());
            persData.bindValue(":pp", pd.getPosition());
            persData.bindValue(":cc", pd.getCompany());
    //        persData.bindValue(":tm", pd.isTeachingMode());
            persData.exec();
            testeeId = persData.lastInsertId().toInt();
        } else {
            // Персональные данные не введены продолжать не могу!
            QMessageBox::critical(0, "Ошибка данных", "Персональные данные не введены продолжать не могу!");
            exit(10002);    // 10002 - недостаток данных для работы
        }
    }

    if(!testeeId && !IsTeachingMode) {  // При нормальном (не обучении) режиме данные должны быть сохранены
        QMessageBox::critical(0, "Ошибка БД", "Не удалось записать информацию о тестируемом!");
        exit(10003);    // 10003 - не удалось записать информацию в testees
    }

    ChooseTest t;
    t.setDatabase(&db);
    // Если в файле с базой тестов более одного, то сначала выбираем какой
    int i = t.exec();   // Выбор теста из доступных

    if(i != 0) {
        t.close();
        int testId = t.getSelectedTestId();
        //printf("Selected id: %i\n", testId);
        MainWindow w;
        ReportViewDialog rv;
    if (!IsTeachingMode) {

        w.setTestId(testId);
        w.setTesteeId(testeeId);
        w.setDatabase(&db);

        w.setReportView(&rv);
        QString aa = QString("UPDATE testees SET test_id=%1 WHERE id=%2").arg(testId).arg(testeeId);
        db.exec(aa);
        w.showNormal();
    } else {

        w.setTeachingMode();
        w.setTestId(testId);
        w.setDatabase(&db);
        w.showNormal();
    }
    //sleep(500);
        return a.exec();
    } else {
        t.close();
    }
    return 0;
}
