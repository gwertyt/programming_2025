#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QCryptographicHash>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    registeredLogins << "admin" << "user123" << "coder";
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    this->setWindowTitle("Регистрация пользователя");
    this->resize(500, 420);

    this->setStyleSheet(
        "QMainWindow { background-color: #2c3e50; }"
        "QLabel { color: #ecf0f1; font-size: 13px; font-weight: bold; }"
        "QLineEdit { background-color: #34495e; color: #ffffff; border: 2px solid #bdc3c7; border-radius: 4px; padding: 4px; font-size: 13px; }"
        "QLineEdit:focus { border: 2px solid #3498db; }"
        "QCheckBox { color: #ecf0f1; font-weight: bold; }"
        "QPushButton#btnRegister { background-color: #2ecc71; color: white; border-radius: 6px; font-size: 14px; font-weight: bold; min-height: 35px; }"
        "QPushButton#btnRegister:hover { background-color: #27ae60; }"
        "QPushButton#btnLoadPhoto { background-color: #95a5a6; color: white; border-radius: 4px; font-weight: bold; }"
        );

    QWidget *central = new QWidget(this);

    lblPhoto = new QLabel(central);
    lblPhoto->setFixedSize(110, 130);
    lblPhoto->setStyleSheet("border: 2px dashed #bdc3c7; background-color: #1a252f;");
    lblPhoto->setText("Фото");
    lblPhoto->setAlignment(Qt::AlignCenter);

    btnLoadPhoto = new QPushButton("Загрузить", central);
    btnLoadPhoto->setObjectName("btnLoadPhoto");
    btnLoadPhoto->setFixedWidth(110);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(lblPhoto);
    leftLayout->addWidget(btnLoadPhoto);
    leftLayout->addStretch();

    editName = new QLineEdit(central);
    editLastName = new QLineEdit(central);
    editNickname = new QLineEdit(central);
    editIdKey = new QLineEdit(central);
    editEmail = new QLineEdit(central);
    editPassword = new QLineEdit(central);
    editPassword->setEchoMode(QLineEdit::Password);

    editName->installEventFilter(this);
    editLastName->installEventFilter(this);
    editNickname->installEventFilter(this);
    editIdKey->installEventFilter(this);
    editEmail->installEventFilter(this);
    editPassword->installEventFilter(this);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("Имя"), 0, 0); gridLayout->addWidget(editName, 0, 1);
    gridLayout->addWidget(new QLabel("Фамилия"), 1, 0); gridLayout->addWidget(editLastName, 1, 1);
    gridLayout->addWidget(new QLabel("Никнейм"), 2, 0); gridLayout->addWidget(editNickname, 2, 1);
    gridLayout->addWidget(new QLabel("ID-Key"), 3, 0); gridLayout->addWidget(editIdKey, 3, 1);
    gridLayout->addWidget(new QLabel("Почта"), 4, 0); gridLayout->addWidget(editEmail, 4, 1);
    gridLayout->addWidget(new QLabel("Пароль"), 5, 0); gridLayout->addWidget(editPassword, 5, 1);

    chkEurope = new QCheckBox("Европа", central);
    chkAsia = new QCheckBox("Азия", central);
    chkAmerica = new QCheckBox("Америка", central);

    QHBoxLayout *serversLayout = new QHBoxLayout();
    serversLayout->addWidget(chkEurope);
    serversLayout->addWidget(chkAsia);
    serversLayout->addWidget(chkAmerica);

    btnRegister = new QPushButton("Регистрация", central);
    btnRegister->setObjectName("btnRegister");
    btnRegister->setFixedWidth(140);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QVBoxLayout *serversGroup = new QVBoxLayout();
    serversGroup->addWidget(new QLabel("Сервера:"));
    serversGroup->addLayout(serversLayout);

    bottomLayout->addLayout(serversGroup);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnRegister, 0, Qt::AlignBottom);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(leftLayout);
    topLayout->addSpacing(15);
    topLayout->addLayout(gridLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    setCentralWidget(central);

    connect(btnLoadPhoto, &QPushButton::clicked, this, &MainWindow::onLoadPhoto);
    connect(btnRegister, &QPushButton::clicked, this, &MainWindow::onRegister);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(watched);
        if (lineEdit) {
            lineEdit->clear();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::onLoadPhoto() {
    QString path = QFileDialog::getOpenFileName(this, "Выбрать фото", "", "Изображения (*.png *.jpg *.jpeg)");
    if (!path.isEmpty()) {
        photoPath = path;
        QPixmap pix(path);
        lblPhoto->setPixmap(pix.scaled(lblPhoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QString MainWindow::encryptPassword(const QString &pass) {
    QByteArray hash = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

void MainWindow::onRegister() {
    QRegularExpression regName("^[A-ZА-ЯЁ][a-zа-яё]+$");
    QRegularExpression regLogin("^[a-zA-Z0-9_-]{3,15}$");
    QRegularExpression regEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpression regId("^A\\d{3}-\\d{2}A-A$");

    if (!regName.match(editName->text()).hasMatch()) { QMessageBox::warning(this, "Ошибка", "Неверный формат Имени!"); return; }
    if (!regName.match(editLastName->text()).hasMatch()) { QMessageBox::warning(this, "Ошибка", "Неверный формат Фамилии!"); return; }
    if (!regLogin.match(editNickname->text()).hasMatch()) { QMessageBox::warning(this, "Ошибка", "Никнейм должен быть от 3 до 15 символов латиницей!"); return; }
    if (!regId.match(editIdKey->text()).hasMatch()) { QMessageBox::warning(this, "Ошибка", "ID-Key должен соответствовать формату A111-11A-A!"); return; }
    if (!regEmail.match(editEmail->text()).hasMatch()) { QMessageBox::warning(this, "Ошибка", "Некорректный Email!"); return; }
    if (editPassword->text().length() < 4) { QMessageBox::warning(this, "Ошибка", "Пароль слишком короткий!"); return; }

    QString nick = editNickname->text().trimmed();
    if (registeredLogins.contains(nick)) {
        QMessageBox::critical(this, "Ошибка", "Указанный логин уже занят!");
        return;
    }

    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QDir accountsDir(desktopPath + "/Accounts");
    if (!accountsDir.exists()) accountsDir.mkpath(".");

    QDir userDir(accountsDir.absolutePath() + "/" + nick);
    if (!userDir.exists()) userDir.mkpath(".");

    QString savedPhotoName = userDir.absolutePath() + "/avatar.png";
    if (!photoPath.isEmpty()) {
        QFile::copy(photoPath, savedPhotoName);
    } else {
        QPixmap defaultPix(lblPhoto->size());
        defaultPix.fill(Qt::gray);
        defaultPix.save(savedPhotoName, "PNG");
    }

    QJsonObject json;
    json["name"] = editName->text();
    json["lastName"] = editLastName->text();
    json["nickname"] = nick;
    json["idKey"] = editIdKey->text();
    json["email"] = editEmail->text();

    QJsonArray servers;
    if (chkEurope->isChecked()) servers.append("Европа");
    if (chkAsia->isChecked()) servers.append("Азия");
    if (chkAmerica->isChecked()) servers.append("Америка");
    json["servers"] = servers;

    QFile jsonFile(userDir.absolutePath() + "/info.json");
    if (jsonFile.open(QIODevice::WriteOnly)) {
        jsonFile.write(QJsonDocument(json).toJson());
        jsonFile.close();
    }

    QFile txtFile(userDir.absolutePath() + "/credentials.txt");
    if (txtFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&txtFile);
        QString encryptedPass = encryptPassword(editPassword->text());
        out << editEmail->text() << "/" << encryptedPass;
        txtFile.close();
    }

    QMessageBox::information(this, "Успех", "Регистрация успешно завершена!\nПапка создана на Рабочем столе.");
    registeredLogins.append(nick);
}
