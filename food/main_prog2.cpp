#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include "food.h"

class Prog2Window : public QMainWindow {
    QTableWidget *tableCorrect, *tableErrors;
    QPushButton *btnLoadJson;
    QTabWidget *tabWidget;

public:
    Prog2Window() {
        this->setWindowTitle("Программа 2: Вывод данных");
        this->resize(600, 450);
        this->setStyleSheet(
            "QMainWindow { background-color: #ffffff; }"
            "QTableWidget { border: 2px solid #000000; font-family: 'Arial'; }"
            "QPushButton { background-color: #ffffff; border: 2px solid #000000; font-weight: bold; min-height: 35px; }"
            );

        QWidget *central = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(central);

        tabWidget = new QTabWidget(central);

        tableCorrect = createTable();
        tableErrors = createTable();

        // Красим ячейки таблицы ошибок в светло-красный цвет через стили
        tableErrors->setStyleSheet("QTableWidget::item { background-color: #ffcdd2; }");

        tabWidget->addTab(tableCorrect, "Корректные");
        tabWidget->addTab(tableErrors, "Ошибки");

        btnLoadJson = new QPushButton("Загрузить .json", central);

        mainLayout->addWidget(tabWidget);
        mainLayout->addWidget(btnLoadJson, 0, Qt::AlignCenter);
        btnLoadJson->setFixedWidth(180);

        setCentralWidget(central);

        connect(btnLoadJson, &QPushButton::clicked, this, &Prog2Window::processJson);
    }

private:
    QTableWidget* createTable() {
        QTableWidget *t = new QTableWidget(this);
        t->setColumnCount(5);
        t->setHorizontalHeaderLabels({"Название", "Описание", "Голод", "Цена", "Вес"});
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования по ТЗ
        return t;
    }

    void fillTable(QTableWidget *table, const QVector<Food> &list) {
        table->setRowCount(0);
        for (int i = 0; i < list.size(); ++i) {
            table->insertRow(i);
            table->setItem(i, 0, new QTableWidgetItem(list[i].name));
            table->setItem(i, 1, new QTableWidgetItem(list[i].description));
            table->setItem(i, 2, new QTableWidgetItem(list[i].hungerValue < 0 ? "—" : QString::number(list[i].hungerValue)));
            table->setItem(i, 3, new QTableWidgetItem(list[i].price < 0 ? "—" : QString::number(list[i].price, 'f', 2)));
            table->setItem(i, 4, new QTableWidgetItem(list[i].weight < 0 ? "—" : QString::number(list[i].weight, 'f', 2)));
        }
    }

    void processJson() {
        QString path = QFileDialog::getOpenFileName(this, "Открыть JSON", "", "JSON файлы (*.json)");
        if (path.isEmpty()) return;

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) return;

        QJsonArray arr = QJsonDocument::fromJson(file.readAll()).array();
        file.close();

        QVector<Food> correctList;
        QVector<Food> errorList;

        for (int i = 0; i < arr.size(); ++i) {
            Food f = Food::fromJsonObject(arr[i].toObject());
            if (f.isValid()) {
                correctList.append(f);
            } else {
                errorList.append(f);
            }
        }

        std::sort(correctList.begin(), correctList.end(), [](const Food &a, const Food &b) {
            return a.name > b.name;
        });

        fillTable(tableCorrect, correctList);
        fillTable(tableErrors, errorList);

        if (!errorList.isEmpty()) {
            QJsonArray errArr;
            for (const Food &f : errorList) errArr.append(f.toJsonObject());

            QFile errFile(QFileInfo(path).absolutePath() + "/errors_out.json");
            if (errFile.open(QIODevice::WriteOnly)) {
                errFile.write(QJsonDocument(errArr).toJson());
                errFile.close();
            }
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Prog2Window w;
    w.show();
    return a.exec();
}
