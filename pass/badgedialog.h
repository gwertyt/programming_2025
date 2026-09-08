#ifndef BADGEDIALOG_H
#define BADGEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class BadgeDialog : public QDialog {
    Q_OBJECT
public:
    explicit BadgeDialog(const QString &text, QWidget *parent = nullptr);
private:
    QLabel *lblPhoto;
    QLabel *lblText;
    QPushButton *btnPrint;
    QPushButton *btnCancel;
};

#endif // BADGEDIALOG_H
