#include "mainwindow.h"
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20); // Отступы
    layout->setSpacing(15); // Расстояние между элементами

    // Логин
    usernameEdit = new IconizedLineEdit(this);
    usernameEdit->setPlaceholderText("Логин");
    usernameEdit->setIconPixmap(QPixmap(":/user.png"));
    usernameEdit->setIconVisibility(IconizedLineEdit::IconAlwaysVisible);
    QRegExpValidator *userValidator = new QRegExpValidator(QRegExp("[A-Za-z0-9]+"), this);
    usernameEdit->setValidator(userValidator);

    // Пароль
    passwordEdit = new IconizedLineEdit(this);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setIconPixmap(QPixmap(":/lock.png"));
    passwordEdit->setIconVisibility(IconizedLineEdit::IconAlwaysVisible);
    passwordEdit->setEchoMode(QLineEdit::Password);
    QRegExpValidator *passValidator = new QRegExpValidator(QRegExp(".{6,}"), this);
    passwordEdit->setValidator(passValidator);

    // Путь к файлу
    imagePathEdit = new IconizedLineEdit(this);
    imagePathEdit->setPlaceholderText("Выберите файл...");
    imagePathEdit->setIconPixmap(QPixmap(":/folder.png"));
    imagePathEdit->setIconClickable(true);
    connect(imagePathEdit, &IconizedLineEdit::iconPressed, this, &MainWindow::chooseImage);

    // Кнопка "Обзор"
    QPushButton *browseButton = new QPushButton("Обзор", this);
    connect(browseButton, &QPushButton::clicked, this, &MainWindow::chooseImage);

    // Индикатор
    ledIndicator = new LedIndicator(this);
    ledIndicator->setText("Статус");
    ledIndicator->setTristate(true);

    // Показ изображения
    imageDisplay = new QLabel(this);
    imageDisplay->setAlignment(Qt::AlignCenter);
    imageDisplay->setStyleSheet("border: 1px solid #cccccc;");
    imageDisplay->setFixedHeight(200); // Фиксированная высота для изображения

    // Добавление виджетов в layout
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(imagePathEdit);
    layout->addWidget(browseButton);
    layout->addWidget(ledIndicator);
    layout->addWidget(imageDisplay);

    // Сигналы для валидации
    connect(usernameEdit, &QLineEdit::textChanged, this, &MainWindow::validateInput);
    connect(passwordEdit, &QLineEdit::textChanged, this, &MainWindow::validateInput);
    connect(imagePathEdit, &QLineEdit::textChanged, this, &MainWindow::validateInput);
}

void MainWindow::validateInput() {
    bool valid =
        usernameEdit->hasAcceptableInput() &&
        passwordEdit->hasAcceptableInput() &&
        imagePathEdit->hasAcceptableInput();

    ledIndicator->setState(valid ? LedIndicator::On : LedIndicator::Off);
}

void MainWindow::chooseImage() {
    QString path = QFileDialog::getOpenFileName(
        this,
        "Выберите файл",
        "",
        "Изображения (*.png *.jpg *.bmp)"
        );

    if (path.isEmpty()) {
        ledIndicator->setState(LedIndicator::Off);
        return;
    }

    // Проверка формата файла
    if (!path.endsWith(".png", Qt::CaseInsensitive) &&
        !path.endsWith(".jpg", Qt::CaseInsensitive) &&
        !path.endsWith(".bmp", Qt::CaseInsensitive)) {
        ledIndicator->setState(LedIndicator::Off);
        return;
    }

    imagePathEdit->setText(path);
    ledIndicator->setState(LedIndicator::Intermediate);
    QTimer::singleShot(2000, [this]() {
        ledIndicator->setState(LedIndicator::Off);
    });

    // Загрузка и отображение изображения
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        pixmap = pixmap.scaled(imageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imageDisplay->setPixmap(pixmap);
    } else {
        imageDisplay->clear();
        ledIndicator->setState(LedIndicator::Off);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    if (imageDisplay && imageDisplay->pixmap() && !imageDisplay->pixmap()->isNull()) {
        QPixmap scaledPixmap = imageDisplay->pixmap()->scaled(
            imageDisplay->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );
        imageDisplay->setPixmap(scaledPixmap);
    }
}
