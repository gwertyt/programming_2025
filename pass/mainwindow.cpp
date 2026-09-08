#include "mainwindow.h"
#include "badgedialog.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->resize(450, 350);
    this->setWindowTitle("Вариант 1 Пропуска");
    this->setStyleSheet(
        "QMainWindow { background-color: #ffffff; }"
        "QListWidget { border: 3px solid #000000; font-family: 'Courier New'; font-size: 14px; font-weight: bold; background-color: #ffffff; }"
        "QPushButton#btnLoad { background-color: #a6d8e7; color: #000000; font-weight: bold; border: 2px solid #000000; font-size: 14px; min-height: 30px; }"
        );

    QWidget *centralWidget = new QWidget(this);
    listWidget = new QListWidget(centralWidget);

    btnLoad = new QPushButton("Загрузить", centralWidget);
    btnLoad->setObjectName("btnLoad");

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(listWidget);
    layout->addWidget(btnLoad, 0, Qt::AlignCenter);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    btnLoad->setFixedWidth(150);

    setCentralWidget(centralWidget);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::onLoadClicked);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
}

MainWindow::~MainWindow() {
    clearPeople();
}

void MainWindow::clearPeople() {
    qDeleteAll(people);
    people.clear();
    listWidget->clear();
}

#include "mainwindow.h"
#include "badgedialog.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>

void MainWindow::onLoadClicked() {
    clearPeople();

    QString exeDir = QCoreApplication::applicationDirPath();
    QString fullPath = exeDir + "/data.txt";

    QFile file(fullPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Положи файл data.txt вот сюда:\n" + fullPath);
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split(",");

        if (parts.size() < 7) continue;
        int code = parts[0].toInt();

        if (code == 1) {
            Date d = {parts[4].toInt(), parts[5].toInt(), parts[6].toInt()};
            people.append(new RuP(parts[1], parts[2], parts[3], d));
        } else if (code == 2) {
            Date d = {parts[5].toInt(), parts[4].toInt(), parts[6].toInt()};
            people.append(new AmP(parts[1], parts[2], parts[3], d));
        }
    }
    file.close();

    for (R* p : people) {
        listWidget->addItem(p->getDisplayText());
    }
}


void MainWindow::onItemDoubleClicked() {
    int index = listWidget->currentRow();
    if (index < 0) return;

    R* selectedPerson = people[index];
    BadgeDialog dlg(selectedPerson->getBadgeText(), this);

    if (dlg.exec() == QDialog::Accepted) {
        delete people[index];
        people.removeAt(index);
        delete listWidget->takeItem(index);
    }
}
