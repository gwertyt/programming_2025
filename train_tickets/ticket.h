#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include <QFile>
#include <QTextStream>

class Ticket {
public:
    QString from;
    QString to;
    QString dateTime;
    QString seat;
    bool extraBaggage;
    QString services;

    Ticket(QString f, QString t, QString dt, QString s, bool bag, QString serv)
        : from(f), to(t), dateTime(dt), seat(s), extraBaggage(bag), services(serv) {}

    bool saveToFile(const QString &filename = "result.txt") {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            QTextStream out(&file);
            out << "--- Билет ---\n";
            out << "Откуда: " << from << "\n";
            out << "Куда: " << to << "\n";
            out << "Дата/Время: " << dateTime << "\n";
            out << "Место: " << seat << "\n";
            out << "Доп. багаж: " << (extraBaggage ? "Да" : "Нет") << "\n";
            out << "Услуги: " << (services.isEmpty() ? "Нет" : services) << "\n";
            out << "-------------\n\n";
            file.close();
            return true;
        }
        return false;
    }
};

#endif // TICKET_H
