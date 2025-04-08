#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>

class LedIndicator : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)

public:
    enum State { Off, On, Intermediate };
    Q_ENUM(State)

    explicit LedIndicator(QWidget *parent = nullptr);
    QString text() const;
    void setText(const QString &text);
    State state() const;
    void setState(State state);
    void setTristate(bool enabled);

signals:
    void stateChanged(State state);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString currentText;
    State currentState = Off; // Инициализация начального состояния
    bool tristate = false;
};

#endif // LEDINDICATOR_H
