#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentQuestionIndex(0),
    score(0),
    timeRemaining(30)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartQuiz);

    connect(ui->answerButton1, &QPushButton::clicked, [this]() { handleAnswer(0); });
    connect(ui->answerButton2, &QPushButton::clicked, [this]() { handleAnswer(1); });
    connect(ui->answerButton3, &QPushButton::clicked, [this]() { handleAnswer(2); });
    connect(ui->answerButton4, &QPushButton::clicked, [this]() { handleAnswer(3); });

    setupQuestions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupQuestions()
{
    questions.append(Question("Какой язык программирования используется в Qt?", {"C++", "Python", "Java", "C#"}, 0));
    questions.append(Question("Какой сигнал используется для таймера в Qt?", {"signal()", "timeout()", "start()", "stop()"}, 1));
    questions.append(Question("Что означает OOP?", {"Object Oriented Programming", "Open Operational Protocol", "Only Open Programs", "None of these"}, 0));
    questions.append(Question("Как называется база данных, которая встроена в Qt?",
                              {"SQLite", "PostgreSQL", "MySQL", "MongoDB"}, 0));

    questions.append(Question("Какая функция используется для запуска основного цикла приложения в Qt?",
                              {"exec()", "run()", "start()", "main()"}, 0));

    questions.append(Question("Что обозначает сигнал в Qt?",
                              {"Сообщение между объектами", "Тип переменной", "Таймер", "Массив"}, 0));

    questions.append(Question("Какой формат файлов используется для хранения интерфейса в Qt Designer?",
                              {".ui", ".qt", ".xml", ".json"}, 0));

    questions.append(Question("Какой метод используется для подключения сигналов и слотов в Qt?",
                              {"connect()", "link()", "bind()", "signal()"}, 0));

    questions.append(Question("Какой класс в Qt используется для работы с временем?",
                              {"QTimer", "QDateTime", "QClock", "QTime"}, 1));

    questions.append(Question("Что такое QWidget в Qt?",
                              {"Базовый класс для всех виджетов",
                               "Класс для работы с окнами",
                               "Класс для работы с базой данных",
                               "Событие"}, 0));

    questions.append(Question("Какой метод отвечает за отображение окна приложения?",
                              {"show()", "display()", "open()", "render()"}, 0));

    questions.append(Question("Как называется система компоновки в Qt?",
                              {"QLayout", "QArrange", "QCompose", "QAlign"}, 0));

    questions.append(Question("Какой класс используется для создания кнопок в Qt?",
                              {"QPushButton", "QButton", "QClick", "QControl"}, 0));
}

void MainWindow::onStartQuiz()
{
    userName = ui->nameLineEdit->text();
    if (userName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя для начала!");
        return;
    }

    currentQuestionIndex = 0;
    score = 0;
    timeRemaining = 30;

    ui->scoreLabel->setText("Счёт: 0");
    timer->start(1000);

    displayQuestion();
}

void MainWindow::displayQuestion()
{
    if (currentQuestionIndex >= questions.size()) {
        finishQuiz();
        return;
    }

    const Question &q = questions[currentQuestionIndex];
    ui->questionLabel->setText(q.questionText);
    ui->answerButton1->setText(q.answerOptions[0]);
    ui->answerButton2->setText(q.answerOptions[1]);
    ui->answerButton3->setText(q.answerOptions[2]);
    ui->answerButton4->setText(q.answerOptions[3]);

    ui->timeLabel->setText("Осталось времени: 30");
    timeRemaining = 30;
}

void MainWindow::handleAnswer(int index)
{
    const Question &q = questions[currentQuestionIndex];

    if (index == q.correctAnswerIndex) {
        score++;
        ui->scoreLabel->setText("Счёт: " + QString::number(score));
    }

    currentQuestionIndex++;
    displayQuestion();
}

void MainWindow::onTimeout()
{
    timeRemaining--;

    if (timeRemaining <= 0) {
        currentQuestionIndex++;
        displayQuestion();
    } else {
        ui->timeLabel->setText("Осталось времени: " + QString::number(timeRemaining));
    }
}

void MainWindow::finishQuiz()
{
    timer->stop();
    QMessageBox::information(this, "Тест завершен",
                             userName + ", вы ответили правильно на " + QString::number(score) + " вопросов из " + QString::number(questions.size()));
}
