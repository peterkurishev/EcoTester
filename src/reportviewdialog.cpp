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

void ReportViewDialog::produceHtmlReport(QSqlDatabase* db, int testeeId, bool IsPassed) {
QString request = QString("select t.name, t.position, t.company, ti.name, tsts.name from testees t, tickets ti, tests tsts where t.test_id = tsts.id and t.ticket_id = ti.id and t.id=:tt");
QSqlQuery query(*db);
query.prepare(request);
query.bindValue(":tt", testeeId);
query.exec();
query.next();

QDate date = QDate::currentDate();
    QString ReportHtml = QString("<html><body><h1><font size=\"+4B\">Результаты тестирования</font></h1><font size=\"+3\">ФИО: %1<br>Должность: %2<br>Организация:%3<br>%4<br>%5<br>%6.<br><br><br>С результатами тестирования ознакомлен <br><br>____________________________ (%1)<br>Дата проведения теста: %7</font></body></html>").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString()).arg(query.value(4).toString()).arg(query.value(3).toString()).arg(IsPassed?QString("Тест пройден"):QString("Тест не пройден")).arg(date.toString("dd.MM.yyyy"));

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
    m_ui->webView->print(&prn); // Печать на принтер по умолчанию

}
