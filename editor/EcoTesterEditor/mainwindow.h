#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QSqlTableModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase* db;
    
public:
    explicit MainWindow(QSqlDatabase *db=0, QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_testsList_clicked(const QModelIndex &index);

    void on_questionsList_clicked(const QModelIndex &index);

    void on_ticketsList_clicked(const QModelIndex &index);

    void on_toolButton_6_clicked();

    void on_toolButton_5_clicked();

    void on_ticketsList_activated(const QModelIndex &index);

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QDataWidgetMapper *questionMapper;
    QSqlTableModel* ticketsModel;
    QSqlTableModel *question_model;
    QSqlTableModel *tests_model;
};

#endif // MAINWINDOW_H
