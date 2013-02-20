#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "ui_mainwindow.h"
#include <QQueue>
#include "domain.h"
#include "reportviewdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void prevAnswer();
    void nextAnswer();
    void answerSelected();
    void cheatMode();
public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~MainWindow();
    void setDatabase(QSqlDatabase* db);
    void setReportView(ReportViewDialog* rvd) {
        _repview = rvd;
    }
private:
    Ui::MainWindowClass ui;
    QSqlDatabase *_db;
    int _ticketId;
    int _testId;
    int _answerNumber;
    int _testeeId;
    bool isCheatMode;
    QQueue<EcoTesterQuestion*> _questions;  // Очередь вопросов
    int _currentQuestion;   // Куски состояния
    int _currentAnswer;
    ReportViewDialog* _repview;
    bool  IsTeachingMode;
public:
    void setTestId(int id) {
        _testId = id;
    }

    void setTesteeId(int id) {
        _testeeId = id;
    }

    void populateQuestions(int ticketId);

    void setTeachingMode() {
        this->IsTeachingMode = true;
    }
};

#endif // MAINWINDOW_H
