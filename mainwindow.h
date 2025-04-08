    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "iconizedlineedit.h"
#include "ledindicator.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected: // <-- Важно: объявление должно быть в секции protected
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void validateInput();
    void chooseImage();

private:
    IconizedLineEdit *usernameEdit;
    IconizedLineEdit *passwordEdit;
    IconizedLineEdit *imagePathEdit;
    LedIndicator *ledIndicator;
    QVBoxLayout *layout;
    QLabel *imageDisplay;
};

#endif
