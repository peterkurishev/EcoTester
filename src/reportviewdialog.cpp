#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include "reportviewdialog.h"
#include "ui_reportviewdialog.h"
#include <QSqlQuery>
#include <QDate>

ReportViewDialog::ReportViewDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ReportViewDialog)
{
    m_ui->setupUi(this);
}

ReportViewDialog::~ReportViewDialog()
{
    delete m_ui;
}

void ReportViewDialog::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ReportViewDialog::produceHtmlReport(QSqlDatabase* db, int testeeId, bool IsPassed, int percentage) {
    QString request = QString("select t.name, t.position, t.company, ti.name, tsts.name from testees t, \
            tickets ti, tests tsts where t.test_id = tsts.id and t.ticket_id = ti.id and t.id=:tt");

    QString answers_log_request = QString("SELECT qs.question, al.answer_id, qs.answer1, qs.answer2, qs.answer3, qs.answer4, qs.answer5, qs.correct \
                                          FROM answer_log al, questions_simple qs \
                                          WHERE al.testee_id = :tt and al.question_id = qs.id");


    QSqlQuery query(*db);
    QSqlQuery query2(*db);
    query.prepare(request);
    query.bindValue(":tt", testeeId);
    query.exec();
    query.next();

    query2.prepare(answers_log_request);
    query2.bindValue(":tt", testeeId);
    query2.exec();

    QString answers;

    while (query2.next()) {
        answers = answers + QString("<strong>Вопрос: %1</strong><br>Ответ: %2%3").arg(query2.value(0).toString()).arg(query2.value(query2.value(1).toInt()+1).toString()).arg( query2.value(1).toInt() == query2.value(7)? QString("<br>"): QString("<br>Верный: %1<br>").arg(query2.value(query2.value(7).toInt()+1).toString()));
    }



QDate date = QDate::currentDate();
QString ReportHtml = QString("<html><body style=\"max-width: 80%; font-size: x-small;\"><h4>Результаты тестирования</h1>ФИО: %1<br>Должность: %2<br>Организация:%3<br>%4<br>%5<br>%6.<br><br><br>С результатами тестирования ознакомлен <br><br>____________________________ (%1)<br>Дата проведения теста: %7<br>%8</body></html>").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString()).arg(query.value(4).toString()).arg(query.value(3).toString()).arg(IsPassed?QString("Тест пройден (%1%)").arg(percentage):QString("Тест не пройден (%1%)").arg(percentage)).arg(date.toString("dd.MM.yyyy")).arg(answers);

    m_ui->webView->setHtml(ReportHtml);
}

void ReportViewDialog::printHtml() {
    QPrinter prn;
    //m_ui->webView->print(&prn); // Печать на принтер по умолчанию
    QPrintDialog printDialog(&prn, this);
 if (printDialog.exec() == QDialog::Accepted) {
     m_ui->webView->print(&prn);
 }
}

void ReportViewDialog::autoPrint() {
    QPrinter prn;
//    prn.PageRange = QPrinter::AllPages;
    prn.setPageSize(QPrinter::A4);
    prn.setPageMargins(10,10,10,10, QPrinter::Millimeter);
    m_ui->webView->print(&prn); // Печать на принтер по умолчанию

}
