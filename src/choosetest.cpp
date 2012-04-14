#include "choosetest.h"
#include "ui_choosetest.h"
#include <QSqlQuery>
#include <QErrorMessage>

ChooseTest::ChooseTest(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ChooseTest)
{
    m_ui->setupUi(this);
    _SelectedTestId = 0;

}

void ChooseTest::setDatabase(QSqlDatabase* db)
{
    this->_db = db;

    QSqlQuery query(*(_db));
    query.exec("SELECT name, id FROM tests");
    while (query.next()) {
        QString test = query.value(0).toString();
        int id = query.value(1).toInt();
        QListWidgetItem* item = new QListWidgetItem(test, m_ui->listWidget);
        item->setData(Qt::UserRole, QVariant(id));
    }
}

ChooseTest::~ChooseTest()
{
    delete m_ui;
}

void ChooseTest::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ChooseTest::saveSelection(int rowID) {
    this->_SelectedTestId = m_ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
}
