#include "ledindicator.h"
#include <QPainter>

LedIndicator::LedIndicator(QWidget *parent)
    : QWidget(parent), currentState(Off), tristate(false) {
    setMinimumSize(30, 30);
}

QString LedIndicator::text() const {
    return currentText;
}

void LedIndicator::setText(const QString &text) {
    currentText = text;
    update();
}

LedIndicator::State LedIndicator::state() const {
    return currentState;
}

void LedIndicator::setState(State state) {
    if (!tristate && state == Intermediate) {
        state = Off; // Если тристейт отключен, промежуточное состояние игнорируется
    }
    if (currentState == state)
        return;

    currentState = state;
    update(); // Обновление отрисовки
    emit stateChanged(state);
}

void LedIndicator::setTristate(bool enabled) {
    tristate = enabled;
}

void LedIndicator::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor color;
    switch (currentState) {
    case On: color = Qt::green; break;
    case Off: color = Qt::red; break;
    case Intermediate: color = Qt::yellow; break;
    }

    int radius = qMin(width(), height()) / 2 - 2;
    painter.drawEllipse(QRect(2, 2, 2 * radius, 2 * radius));
    painter.setBrush(color);
    painter.drawEllipse(QRect(3, 3, 2 * radius - 2, 2 * radius - 2));

    if (!currentText.isEmpty()) {
        painter.setPen(Qt::black);
        painter.drawText(rect().adjusted(2 * radius + 5, 0, 0, 0),
                         Qt::AlignVCenter | Qt::AlignLeft,
                         currentText);
    }
}
