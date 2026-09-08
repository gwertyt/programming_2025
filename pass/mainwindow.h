#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVector>
#include "person.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onLoadClicked();
    void onItemDoubleClicked();
private:
    QListWidget *listWidget;
    QPushButton *btnLoad;
    QVector<R*> people;
    void clearPeople();
};

#endif // MAINWINDOW_H
