
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include "question.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartQuiz();
    void handleAnswer(int index);
    void onTimeout();

private:
    Ui::MainWindow *ui;

    QVector<Question> questions;
    int currentQuestionIndex;
    int score;
    QString userName;

    QTimer *timer;
    int timeRemaining;

    void setupQuestions();
    void displayQuestion();
    void finishQuiz();
};

#endif
