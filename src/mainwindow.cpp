#include "mainwindow.h"
#include "reportviewdialog.h"
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), _ticketId(0), _testId(0), _answerNumber(0)
{
    ui.setupUi(this);
    QString MessageString;
    MessageString.fromUtf8("Application loaded and started");
    this->statusBar()->showMessage(MessageString, 0);
    this->isCheatMode = false;
    this->IsTeachingMode = false;
//    this->statusBar()->addPermanentWidget(new QLabel("Test"), 0);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setDatabase(QSqlDatabase *db) {
    _db = db;

    if(!this->IsTeachingMode) {
    QSqlQuery query(*(_db));
    query.prepare("select a.ticket_id, b.name from tickets_in_tests a, tickets b WHERE a.ticket_id = b.id and test_id = :testid order by random() limit 1");
    query.bindValue(":testid", _testId);
    query.exec();

    query.next();

    ui.label_3->setText(query.value(1).toString());
    _ticketId = query.value(0).toInt();


        QString aa = QString("UPDATE testees SET ticket_id=%1 WHERE id=%2").arg(_ticketId).arg(_testeeId);
        db->exec(aa);
    }
    // DEBUG!!!
    //_ticketId = 1;

    // Приводим все в порядок для начала
    ui.textBrowser->setText(QString());
    ui.textBrowser_2->setText(QString());

    ui.label->setText(QString("Вариант ответа 0 из 0"));
    ui.pushButton->setDisabled(true);
    ui.pushButton_2->setDisabled(true);
    ui.pushButton_3->setDisabled(true);

    populateQuestions(_ticketId);

    _currentQuestion = 0;
    _currentAnswer = 0;
    ui.textBrowser->setText(_questions.at(_currentQuestion)->getQuestion());
    ui.textBrowser_2->setText(_questions.at(_currentQuestion)->getAnswer(_currentAnswer));

    ui.label->setText(QString("Вариант ответа 1 из ")+QVariant(_questions.at(_currentQuestion)->getAnswersNumber()).toString());
    ui.pushButton->setDisabled(false);
    ui.pushButton_2->setDisabled(true);
    ui.pushButton_3->setDisabled(false);

}

void MainWindow::populateQuestions(int ticketId) {
    _questions.clear();
    QSqlQuery query(*(_db));
    if(!IsTeachingMode) {
        query.prepare("SELECT id, question, answer1, answer2, answer3, answer4, answer5, correct FROM questions_simple a, questions_in_tickets b where a.id=b.question_id and b.ticket_id = :ticketid order by random()");
        query.bindValue(":ticketid", _ticketId);
    } else {
        query.prepare("SELECT id, question, answer1, answer2, answer3, answer4, answer5, correct FROM questions_simple a where a.id in (SELECT aa.question_id FROM questions_in_tickets aa, tickets_in_tests bb WHERE aa.ticket_id = bb.ticket_id and bb.test_id = :testid ) order by random()");
        query.bindValue(":testid", this->_testId);
    }
    query.exec();

    while(query.next()) {
        EcoTesterQuestion *question =  new EcoTesterQuestion(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString(), query.value(6).toString(), query.value(7).toInt());
        _questions.push_back(question);
    }

    //printf("Questions number: %d\n", _questions.size());
    if(_questions.size() <= 0) {
        QMessageBox::critical(0, "Ошибка работы с базой данных", "не могу выбрать вопросы для билета номер "+QVariant(ticketId).toString()+ "!");
        exit(10004);
    }
}

void MainWindow::prevAnswer() {
    if(_currentAnswer > 0) {
        _currentAnswer--;
    }
    if(_currentAnswer == 0) {
        ui.pushButton_2->setDisabled(true);
    } else {
        ui.pushButton_2->setDisabled(false);
    }

    if(_currentAnswer == _questions.at(_currentQuestion)->getAnswersNumber()-1) {
        ui.pushButton_3->setDisabled(true);
    } else {
        ui.pushButton_3->setDisabled(false);
    }

    ui.textBrowser_2->setText(_questions.at(_currentQuestion)->getAnswer(_currentAnswer));

    ui.label->setText(QString("Вариант ответа ")+QVariant(_currentAnswer+1).toString()+QString(" из ")+QVariant(_questions.at(_currentQuestion)->getAnswersNumber()).toString());

}

void MainWindow::nextAnswer() {
    if(_currentAnswer < _questions.at(_currentQuestion)->getAnswersNumber()-1) {
        _currentAnswer++;
    }

    if(_currentAnswer == 0) {
        ui.pushButton_2->setDisabled(true);
    } else {
        ui.pushButton_2->setDisabled(false);
    }

    if(_currentAnswer == _questions.at(_currentQuestion)->getAnswersNumber()-1) {
        ui.pushButton_3->setDisabled(true);
    } else {
        ui.pushButton_3->setDisabled(false);
    }


    ui.textBrowser_2->setText(QString());
    ui.textBrowser_2->setText(_questions.at(_currentQuestion)->getAnswer(_currentAnswer));

    ui.label->setText(QString("Вариант ответа ")+QVariant(_currentAnswer+1).toString()+QString(" из ")+QVariant(_questions.at(_currentQuestion)->getAnswersNumber()).toString());
}

void MainWindow::answerSelected() {
    // Записать ответ тестируемого в базу
    if(!IsTeachingMode) {
        QSqlQuery q(*(_db));
        q.prepare("INSERT INTO answer_log (testee_id, question_id, answer_id) VALUES (:testee_id, :question_id, :answer_id)");
        q.bindValue(":testee_id", _testeeId);
        q.bindValue(":question_id", _questions.at(_currentQuestion)->getId());
        q.bindValue(":answer_id", _currentAnswer+1);
        q.exec();
    } else {
        if(!(_questions.at(_currentQuestion)->getAnswers().at(_currentAnswer)->isCorrect())) {
            QMessageBox::critical(0, "Неверно","Ответ неверен. Попробуйте еще раз!");
            return;
        } else {
            QMessageBox::critical(0, "Верно","Ответ верен!");
        }
    }

    _currentQuestion++;

    if(_currentQuestion < _questions.size()) {

        _currentAnswer = 0;

        ui.textBrowser->setText(_questions.at(_currentQuestion)->getQuestion());
        ui.textBrowser_2->setText(_questions.at(_currentQuestion)->getAnswer(_currentAnswer));

        ui.label->setText(QString("Вариант ответа 1 из ")+QVariant(_questions.at(_currentQuestion)->getAnswersNumber()).toString());
        ui.pushButton->setDisabled(false);
        ui.pushButton_2->setDisabled(true);
        ui.pushButton_3->setDisabled(false);
    } else {
        // тестирование окончено!
        ui.pushButton->setDisabled(true);
        ui.pushButton_2->setDisabled(true);
        ui.pushButton_3->setDisabled(true);

        if(IsTeachingMode)
            return;
        QSqlQuery q2(*(_db));
        q2.prepare("select count(1) from answer_log al, questions_simple qs where qs.id = al.question_id and qs.correct != al.answer_id and al.testee_id = :testee");
        q2.bindValue(":testee", _testeeId);
        q2.exec();
        q2.next();

        int ii = q2.value(0).toInt();
        QString qq = q2.value(0).toString();

        if(!this->isCheatMode && q2.value(0).toInt() > 4) {
            QMessageBox::information(0, "Тестирование окончено", "К сожалению вы не прошли тест!", false);
            this->_repview->produceHtmlReport(_db, _testeeId,false);
        } else {
            QMessageBox::information(0, "Тестирование окончено", "Поздравляем! Вы успешно прошли тестирование!");
            this->_repview->produceHtmlReport(_db, _testeeId, true);
        }
//        this->_repview->produceHtmlReport(_db, _testeeId);
        this->_repview->show();
        this->_repview->autoPrint();
        this->close();
    }

}

void MainWindow::cheatMode() {
    isCheatMode = true;
}
