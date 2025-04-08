#ifndef ICONIZEDLINEEDIT_H
#define ICONIZEDLINEEDIT_H

#include <QLineEdit>
#include <QLabel>

class IconizedLineEdit : public QLineEdit {
    Q_OBJECT

public:
    enum IconVisibilityMode {
        IconAlwaysVisible,
        IconVisibleOnHover,
        IconVisibleOnTextPresence,
        IconVisibleOnEmptyText,
        IconAlwaysHidden
    };

    explicit IconizedLineEdit(QWidget *parent = nullptr);
    ~IconizedLineEdit();

    void setIconPixmap(const QPixmap &pixmap);
    void setIconVisibility(IconVisibilityMode mode);
    void setIconClickable(bool clickable);

signals:
    void iconPressed();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void slotTextChanged(const QString &text);
    void updateIconPosition();

private:
    QLabel *iconLabel;
    IconVisibilityMode visibilityMode;
    bool isClickable;
};

#endif
