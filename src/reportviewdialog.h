#ifndef REPORTVIEWDIALOG_H
#define REPORTVIEWDIALOG_H

#include <QtGui/QDialog>
#include <QSqlDatabase>
#include <QPrinter>
//#include <Q

namespace Ui {
    class ReportViewDialog;
}

class ReportViewDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ReportViewDialog)
public:
    explicit ReportViewDialog(QWidget *parent = 0);
    virtual ~ReportViewDialog();
    void produceHtmlReport(QSqlDatabase* db, int testeeId, bool IsPassed=true);
    void autoPrint();

public slots:
    void printHtml();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ReportViewDialog *m_ui;
};

#endif // REPORTVIEWDIALOG_H
