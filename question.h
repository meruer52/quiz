#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QStringList>

class Question {
public:
    Question(const QString &qText, const QStringList &answers, int correctIndex)
        : questionText(qText), answerOptions(answers), correctAnswerIndex(correctIndex) {}

    QString questionText;
    QStringList answerOptions;
    int correctAnswerIndex;
};

#endif
