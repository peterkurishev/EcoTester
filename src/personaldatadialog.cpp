#include "personaldatadialog.h"
#include "ui_personaldatadialog.h"

PersonalDataDialog::PersonalDataDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::PersonalDataDialog)
{
    m_ui->setupUi(this);
}

PersonalDataDialog::~PersonalDataDialog()
{
    delete m_ui;
}

void PersonalDataDialog::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString PersonalDataDialog::getName() {
    return m_ui->nameEdit->text();
}
QString PersonalDataDialog::getCompany() {
    return m_ui->companyEdit->text();
}
QString PersonalDataDialog::getPosition() {
    return m_ui->positionEdit->text();
}

bool PersonalDataDialog::isTeachingMode() {
    return m_ui->checkBox->isChecked();
}
