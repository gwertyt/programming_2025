#ifndef FOOD_H
#define FOOD_H

#include <QString>
#include <QJsonObject>
#include <QRegularExpression>

class Food {
public:
    QString name;
    QString description;
    int hungerValue;
    double price;
    double weight;

    Food() : hungerValue(-1), price(-1.0), weight(-1.0) {}
    Food(QString n, QString d, int h, double p, double w)
        : name(n), description(d), hungerValue(h), price(p), weight(w) {}

    bool isValid() const {
        if (name.trimmed().isEmpty() || description.trimmed().isEmpty()) return false;
        if (hungerValue <= 0 || price <= 0.0 || weight <= 0.0) return false;

        QRegularExpression regName("^[A-ZА-ЯЁ][a-zа-яёA-Za-zА-Яа-яЁё\\s\\d-]*$");
        return regName.match(name).hasMatch();
    }

    QJsonObject toJsonObject() const {
        QJsonObject json;
        json["name"] = name;
        json["description"] = description;
        json["hungerValue"] = hungerValue;
        json["price"] = price;
        json["weight"] = weight;
        return json;
    }

    static Food fromJsonObject(const QJsonObject &json) {
        Food f;
        if (json.contains("name") && json["name"].isString()) f.name = json["name"].toString();
        if (json.contains("description") && json["description"].isString()) f.description = json["description"].toString();
        if (json.contains("hungerValue")) f.hungerValue = json["hungerValue"].toInt();
        if (json.contains("price")) f.price = json["price"].toDouble();
        if (json.contains("weight")) f.weight = json["weight"].toDouble();
        return f;
    }
};

#endif // FOOD_H
