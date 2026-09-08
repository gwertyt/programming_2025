#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QStringList>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onLoadPhoto();
    void onRegister();

private:
    QLineEdit *editName, *editLastName, *editNickname, *editIdKey, *editEmail, *editPassword;
    QLabel *lblPhoto;
    QPushButton *btnLoadPhoto, *btnRegister;
    QCheckBox *chkEurope, *chkAsia, *chkAmerica;

    QString photoPath;
    QStringList registeredLogins;

    void setupUi();
    QString encryptPassword(const QString &pass);
};

#endif // MAINWINDOW_H
