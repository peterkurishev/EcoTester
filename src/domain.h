#include <QString>
#include <QList>
#ifndef DOMAIN_H
#define DOMAIN_H

class EcoTesterAnswer {
    QString _answer;
    bool _isCorrect;
public:
    EcoTesterAnswer(QString answer, bool isCorrect) {
        _answer = answer;
        _isCorrect = isCorrect;
    }

    bool isCorrect() {
        return _isCorrect;
    }

    QString getAnswer() {
        return _answer;
    }
};

class EcoTesterQuestion {
    int _id;
    int _currentAnswer;
    QString _question;
    QList<EcoTesterAnswer*> _answers;
public:

    ~EcoTesterQuestion() {
        // Удаление ответов
    }

    int NumberOfAnswers() {
        return _answers.size();
    }

    QList<EcoTesterAnswer*> getAnswers() {
        return _answers;
    }

    QString getQuestion() {
        return _question;
    }

    QString getAnswer(int num) {
        return _answers.at(num)->getAnswer();
    }

    bool isAnswerCorrect(int num) {
        return _answers.at(num)->isCorrect();
    }

    int getId() {
        return _id;
    }


    EcoTesterQuestion(int id, QString question, QString answer1, QString answer2, QString answer3, QString answer4, QString answer5, int correct) {
        _id = id;
        _question = question;
        if(answer1.length() > 0) {
             EcoTesterAnswer *a = new EcoTesterAnswer(answer1, correct==1?true:false);
             _answers.push_back(a);
        } else {
            return; // Бред. assertion сюда!
        }
        if(answer2.length() > 0) {
             EcoTesterAnswer *a = new EcoTesterAnswer(answer2, correct==2?true:false);
             _answers.push_back(a);
        } else {
            return; // Бред. assertion сюда!
        }
        if(answer3.length() > 0) {
             EcoTesterAnswer *a = new EcoTesterAnswer(answer3, correct==3?true:false);
             _answers.push_back(a);
        } else {
            return; // Бред. assertion сюда!
        }
        if(answer4.length() > 0) {
             EcoTesterAnswer *a = new EcoTesterAnswer(answer4, correct==4?true:false);
             _answers.push_back(a);
        } else {
            return; // Бред. assertion сюда!
        }
        if(answer5.length() > 0) {
             EcoTesterAnswer *a = new EcoTesterAnswer(answer5, correct==5?true:false);
             _answers.push_back(a);
        } else {
            return; // Бред. assertion сюда!
        }
    }

    int getAnswersNumber() {
        return _answers.count();
    }
};

#endif // DOMAIN_H
