#include "iconizedlineedit.h"
#include <QStyle>
#include <QMouseEvent>

IconizedLineEdit::IconizedLineEdit(QWidget *parent)
    : QLineEdit(parent), visibilityMode(IconVisibleOnEmptyText), isClickable(false) {
    iconLabel = new QLabel(this);
    iconLabel->setCursor(Qt::ArrowCursor);
    iconLabel->installEventFilter(this);
    connect(this, &QLineEdit::textChanged, this, &IconizedLineEdit::slotTextChanged);
    updateIconPosition();
}

IconizedLineEdit::~IconizedLineEdit() {
    delete iconLabel;
}

void IconizedLineEdit::setIconPixmap(const QPixmap &pixmap) {
    iconLabel->setPixmap(pixmap.scaled(height(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    updateIconPosition();
}

void IconizedLineEdit::setIconVisibility(IconVisibilityMode mode) {
    visibilityMode = mode;
    slotTextChanged(text());
}

void IconizedLineEdit::setIconClickable(bool clickable) {
    isClickable = clickable;
    iconLabel->setCursor(clickable ? Qt::PointingHandCursor : Qt::ArrowCursor);
}

void IconizedLineEdit::resizeEvent(QResizeEvent *event) {
    QLineEdit::resizeEvent(event);
    updateIconPosition();
}

void IconizedLineEdit::slotTextChanged(const QString &text) {
    bool showIcon = false;
    switch (visibilityMode) {
    case IconAlwaysVisible:
        showIcon = true;
        break;
    case IconVisibleOnTextPresence:
        showIcon = !text.isEmpty();
        break;
    case IconVisibleOnEmptyText:
        showIcon = text.isEmpty();
        break;
    default:
        break;
    }
    iconLabel->setVisible(showIcon);
}

void IconizedLineEdit::updateIconPosition() {
    if (iconLabel->pixmap() == nullptr) return;

    int padding = 5;
    int iconSize = height() - 2 * padding;
    iconLabel->setGeometry(width() - iconSize - padding,
                           padding,
                           iconSize,
                           iconSize);

    QMargins margins;
    if (iconLabel->isVisible()) {
        margins.setRight(iconSize + padding);
    } else {
        margins.setRight(0);
    }
    setTextMargins(margins);
}

bool IconizedLineEdit::eventFilter(QObject *obj, QEvent *event) {
    if (obj == iconLabel && event->type() == QEvent::MouseButtonPress && isClickable) {
        emit iconPressed();
        return true;
    }
    return QLineEdit::eventFilter(obj, event);
}

void IconizedLineEdit::enterEvent(QEvent *event) {
    if (visibilityMode == IconVisibleOnHover) {
        iconLabel->setVisible(true);
    }
    QWidget::enterEvent(event);
}

void IconizedLineEdit::leaveEvent(QEvent *event) {
    if (visibilityMode == IconVisibleOnHover) {
        iconLabel->setVisible(false);
    }
    QWidget::leaveEvent(event);
}
