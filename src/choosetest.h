#ifndef CHOOSETEST_H
#define CHOOSETEST_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QListWidgetItem>

namespace Ui {
    class ChooseTest;
}

class ChooseTest : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ChooseTest)
public slots:
    void saveSelection(int rowID);
public:
    explicit ChooseTest(QWidget *parent = 0);
    void setDatabase(QSqlDatabase* db);
    int  getSelectedTestId() {
        return _SelectedTestId;
    }
    virtual ~ChooseTest();
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ChooseTest *m_ui;
    QSqlDatabase *_db;
    unsigned int _SelectedTestId;
};

#endif // CHOOSETEST_H
