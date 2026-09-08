#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QFileDialog>
#include "food.h"

class Prog1Window : public QMainWindow {
    QLineEdit *editName, *editDesc, *editHunger, *editPrice, *editWeight;
    QPushButton *btnFromTxt, *btnOk;

public:
    Prog1Window() {
        this->setWindowTitle("Программа 1: Новый объект");
        this->setFixedSize(400, 250);
        this->setStyleSheet(
            "QMainWindow { background-color: #ffffff; }"
            "QLineEdit { border: 2px solid #000000; padding: 3px; font-weight: bold; }"
            "QPushButton { border: 2px solid #000000; font-weight: bold; min-height: 30px; }"
            "QPushButton#btnFromTxt { background-color: #d1c4e9; }"
            "QPushButton#btnOk { background-color: #f8bbd0; }"
            );

        QWidget *central = new QWidget(this);
        QGridLayout *gl = new QGridLayout();

        editName = new QLineEdit(central);
        editDesc = new QLineEdit(central);
        editHunger = new QLineEdit(central);
        editPrice = new QLineEdit(central);
        editWeight = new QLineEdit(central);

        gl->addWidget(new QLabel("Название:", central), 0, 0); gl->addWidget(editName, 0, 1);
        gl->addWidget(new QLabel("Описание:", central), 1, 0); gl->addWidget(editDesc, 1, 1);
        gl->addWidget(new QLabel("Голод (ед):", central), 2, 0); gl->addWidget(editHunger, 2, 1);
        gl->addWidget(new QLabel("Цена:", central), 3, 0);     gl->addWidget(editPrice, 3, 1);
        gl->addWidget(new QLabel("Вес:", central), 4, 0);      gl->addWidget(editWeight, 4, 1);

        btnFromTxt = new QPushButton("из .txt", central); btnFromTxt->setObjectName("btnFromTxt");
        btnOk = new QPushButton("Ok", central);           btnOk->setObjectName("btnOk");

        QVBoxLayout *rightBtns = new QVBoxLayout();
        rightBtns->addWidget(btnFromTxt);
        rightBtns->addWidget(btnOk);
        rightBtns->addStretch();

        QHBoxLayout *mainLayout = new QHBoxLayout(central);
        mainLayout->addLayout(gl, 1);
        mainLayout->addLayout(rightBtns);

        setCentralWidget(central);

        connect(btnFromTxt, &QPushButton::clicked, this, &Prog1Window::loadFromTxt);
        connect(btnOk, &QPushButton::clicked, this, &Prog1Window::saveToJson);
    }

private:
    void loadFromTxt() {
        QString path = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
        if (path.isEmpty()) return;

        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            editName->setText(in.readLine().trimmed());
            editDesc->setText(in.readLine().trimmed());
            editHunger->setText(in.readLine().trimmed());
            editPrice->setText(in.readLine().trimmed());
            editWeight->setText(in.readLine().trimmed());
            file.close();
        }
    }

    void saveToJson() {
        Food f(editName->text(), editDesc->text(), editHunger->text().toInt(),
               editPrice->text().toDouble(), editWeight->text().toDouble());

        if (!f.isValid()) {
            QMessageBox::warning(this, "Ошибка", "Данные некорректны или не заполнены!");
            return;
        }

        QString path = QFileDialog::getSaveFileName(this, "Сохранить JSON", "result.json", "JSON файлы (*.json)");
        if (path.isEmpty()) return;

        QJsonArray jsonArray;
        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) {
            jsonArray = QJsonDocument::fromJson(file.readAll()).array();
            file.close();
        }

        jsonArray.append(f.toJsonObject());

        if (file.open(QIODevice::WriteOnly)) {
            file.write(QJsonDocument(jsonArray).toJson());
            file.close();
            QMessageBox::information(this, "Успех", "Объект успешно добавлен в JSON файл!");
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Prog1Window w;
    w.show();
    return a.exec();
}
