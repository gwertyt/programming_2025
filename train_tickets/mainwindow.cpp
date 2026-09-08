#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticket.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onResetClicked() {
    ui->editFrom->clear();
    ui->editTo->clear();
    ui->editDateTime->clear();
    ui->editSeat->clear();

    ui->radioBagYes->setAutoExclusive(false);
    ui->radioBagNo->setAutoExclusive(false);
    ui->radioBagYes->setChecked(false);
    ui->radioBagNo->setChecked(false);
    ui->radioBagYes->setAutoExclusive(true);
    ui->radioBagNo->setAutoExclusive(true);

    ui->chkFood->setChecked(false);
    ui->chkTaxi->setChecked(false);
    ui->chkVip->setChecked(false);
    ui->chkFood->setChecked(false);
    ui->chkTaxi->setChecked(false);
    ui->chkVip->setChecked(false);
}

void MainWindow::onSaveClicked() {
    QRegularExpression regCity("^[A-ZА-ЯЁ][a-zа-яё]+$");

    if (!regCity.match(ui->editFrom->text()).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Несоответствие в поле: Откуда");
        return;
    }
    if (!regCity.match(ui->editTo->text()).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Несоответствие в поле: Куда");
        return;
    }

    QRegularExpression regDateTime("^\\d{2}\\.\\d{2}\\.\\d{4}/\\d{2}:\\d{2}$");
    if (!regDateTime.match(ui->editDateTime->text()).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Несоответствие в поле: Дата и время");
        return;
    }

    QRegularExpression regSeat("^([1-5][A-D]|([6-9]|[1-2]\\d|30)[A-F])$");
    if (!regSeat.match(ui->editSeat->text()).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Несоответствие в поле: Место");
        return;
    }

    QStringList servicesList;
    if (ui->chkFood->isChecked()) servicesList << "Питание";
    if (ui->chkTaxi->isChecked()) servicesList << "Такси";
    if (ui->chkVip->isChecked())  servicesList << "VIP зал";
    QString servicesStr = servicesList.join(", ");

    Ticket ticket(
        ui->editFrom->text(),
        ui->editTo->text(),
        ui->editDateTime->text(),
        ui->editSeat->text(),
        ui->radioBagYes->isChecked(),
        servicesStr
        );

    if (ticket.saveToFile()) {
        QString path = QFileInfo("result.txt").absoluteFilePath();
        QMessageBox::information(this, "Успех", "Данные сохранены!\nПуть к файлу:\n" + path);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось записать файл.");
    }

}
