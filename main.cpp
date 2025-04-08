#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyleSheet(R"(
        QLineEdit {
            padding: 8px;
            border: 2px solid #dcdcdc;
            border-radius: 8px;
            background: #f0f0f0;
        }
        QLineEdit:hover {
            border-color: #a0a0a0;
        }
        QLineEdit:focus {
            border: 2px solid #0078d7;
        }
        QPushButton {
            padding: 8px 16px;
            border-radius: 8px;
            background: #0078d7;
            color: white;
            font-weight: bold;
        }
        QPushButton:hover {
            background: #005ca3;
        }
        /* Стиль для индикатора */
        LedIndicator {
            border-radius: 15px;
            background: #e0e0e0;
            padding: 8px;
        }
    )");

    MainWindow window;
    window.show();
    return app.exec();
}
