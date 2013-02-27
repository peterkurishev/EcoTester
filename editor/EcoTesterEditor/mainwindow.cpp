#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

MainWindow::MainWindow(QSqlDatabase *database, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = database;

  tests_model = new QSqlTableModel(this, *db);
  tests_model->setTable("tests");
  tests_model->setHeaderData(1, Qt::Horizontal, tr("Name"));
  tests_model->setEditStrategy(QSqlTableModel::OnFieldChange);
  tests_model->select();
  ui->testsList->setModel(tests_model );
  ui->testsList->setModelColumn(1);

  ticketsModel = new QSqlTableModel(this, *db);
  ticketsModel->setTable("tickets");
  ticketsModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
  ticketsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
  ticketsModel->select();
  ui->ticketsList->setModel(ticketsModel);
  ui->ticketsList->setModelColumn(1);

  question_model = new QSqlTableModel(this, *db);
  question_model->setTable("questions_simple");
  ui->questionsList->setModel(question_model);
  ui->questionsList->setModelColumn(1);
  question_model->setHeaderData(1, Qt::Horizontal, tr("Name"));
  question_model->setEditStrategy(QSqlTableModel::OnFieldChange);
  question_model->select();

  questionMapper = new QDataWidgetMapper(this);

  questionMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  questionMapper->setModel(question_model);
  questionMapper->setItemDelegate(new QSqlRelationalDelegate(this));
  questionMapper->addMapping(ui->questionText, 1);
  questionMapper->addMapping(ui->answer1Text, 2);
  questionMapper->addMapping(ui->answer2Text, 3);
  questionMapper->addMapping(ui->answer3Text, 4);
  questionMapper->addMapping(ui->answer4Text, 5);
  questionMapper->addMapping(ui->answer5Text, 6);
  questionMapper->addMapping(ui->correctAnswer, 7);

}

MainWindow::~MainWindow()
{
  delete ui;
  delete questionMapper;
}

void MainWindow::on_testsList_clicked(const QModelIndex &index)
{
  ticketsModel->setFilter(QString("id in (SELECT ticket_id FROM tickets_in_tests WHERE test_id=%1)").arg(index.sibling(index.row(), 0).data().toInt()));
}

void MainWindow::on_questionsList_clicked(const QModelIndex &index)
{
  questionMapper->setCurrentIndex(index.row());
}

void MainWindow::on_ticketsList_clicked(const QModelIndex &index)
{
  question_model->setFilter(QString("id in (SELECT question_id FROM questions_in_tickets WHERE ticket_id=%1)").arg(index.sibling(index.row(),0).data().toInt()));
}

void MainWindow::on_toolButton_6_clicked()
{
    QModelIndex index = ui->testsList->currentIndex();
    int row = index.row();
    tests_model->removeRow(row);
    ui->testsList->setCurrentIndex(index.sibling(index.row()-1,0));
    tests_model->select();

}

void MainWindow::on_toolButton_5_clicked()
{
    tests_model->insertRow(ui->testsList->currentIndex().row()-1);
    tests_model->select();
}

void MainWindow::on_ticketsList_activated(const QModelIndex &index)
{
    question_model->setFilter(QString("id in (SELECT question_id FROM questions_in_tickets WHERE ticket_id=%1)").arg(index.sibling(index.row(),0).data().toInt()));
}
