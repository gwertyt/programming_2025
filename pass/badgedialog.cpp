#include "badgedialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

BadgeDialog::BadgeDialog(const QString &text, QWidget *parent) : QDialog(parent) {
    this->setFixedSize(320, 200);
    this->setWindowTitle("Пропуск");
    this->setStyleSheet(
        "QDialog { background-color: #ffffff; border: 2px solid #000000; }"
        "QPushButton#btnPrint { background-color: #0076a3; color: white; font-weight: bold; border: 1px solid #005f82; min-height: 25px; }"
        "QPushButton#btnCancel { background-color: #d9534f; color: white; font-weight: bold; border: 1px solid #c9302c; min-height: 25px; }"
        );

    lblPhoto = new QLabel(this);
    lblPhoto->setFixedSize(90, 110);
    lblPhoto->setStyleSheet("border: 2px solid #000000; background-color: #f0f0f0;");
    lblPhoto->setText("👤");
    lblPhoto->setAlignment(Qt::AlignCenter);
    QFont font = lblPhoto->font();
    font.setPointSize(36);
    lblPhoto->setFont(font);

    lblText = new QLabel(text, this);
    lblText->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lblText->setStyleSheet("font-family: 'Arial'; font-size: 13px;");

    btnPrint = new QPushButton("Печать", this);
    btnPrint->setObjectName("btnPrint");
    btnCancel = new QPushButton("Отмена", this);
    btnCancel->setObjectName("btnCancel");

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(lblPhoto);
    topLayout->addWidget(lblText, 1);
    topLayout->setSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnPrint);
    btnLayout->addWidget(btnCancel);
    btnLayout->setSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(btnLayout);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(btnPrint, &QPushButton::clicked, this, &QDialog::accept);
}
