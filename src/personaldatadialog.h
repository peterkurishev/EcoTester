#ifndef PERSONALDATADIALOG_H
#define PERSONALDATADIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class PersonalDataDialog;
}

class PersonalDataDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(PersonalDataDialog)
public:
    explicit PersonalDataDialog(QWidget *parent = 0);
    virtual ~PersonalDataDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::PersonalDataDialog *m_ui;
public:
    QString getName();
    QString getCompany();
    QString getPosition();
    bool isTeachingMode();  // В режиме "обучения" не происходит записи и выдачи результатов, а просто тестируемый гоняется по списку вопросов по всем тестам в случайном порядке.
};

#endif // PERSONALDATADIALOG_H
