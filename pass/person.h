#ifndef PERSON_H
#define PERSON_H

#include <QString>

struct Date {
    int day;
    int month;
    int year;
    QString toString() const {
        return QString("%1.%2.%3")
        .arg(day, 2, 10, QChar('0'))
            .arg(month, 2, 10, QChar('0'))
            .arg(year, 4, 10, QChar('0'));
    }
};

class R {
protected:
    QString firstName;
    QString lastName;
    Date birthDate;
public:
    R(QString f, QString l, Date d) : firstName(f), lastName(l), birthDate(d) {}
    virtual ~R() {}
    virtual QString getDisplayText() const {
        return lastName + " " + firstName + " - " + birthDate.toString();
    }
    virtual QString getBadgeText() const {
        return "<b>" + lastName + "</b><br>" + firstName + "<br><br><span style='color:#555;'>" + birthDate.toString() + "</span>";
    }
};

class RuP : public R {
private:
    QString patronymic;
public:
    RuP(QString l, QString f, QString p, Date d) : R(f, l, d), patronymic(p) {}
    QString getDisplayText() const override {
        QString full = lastName + " " + firstName;
        if (!patronymic.isEmpty()) full += " " + patronymic;
        return full.leftJustified(32, ' ') + birthDate.toString();
    }
    QString getBadgeText() const override {
        return "<p style='font-size:16px; margin:0; line-height:1.2;'>"
               "<b>" + lastName + "</b><br>" +
               firstName + "<br>" +
               patronymic + "</p><br>" +
               "<span style='font-family:monospace; color:#444; font-size:14px;'>дд.мм.гггг<br><b>" + birthDate.toString() + "</b></span>";
    }
};

class AmP : public R {
private:
    QString middleName;
public:
    AmP(QString f, QString m, QString l, Date d) : R(f, l, d), middleName(m) {}
    QString getDisplayText() const override {
        QString full = firstName + " " + middleName + " " + lastName;
        return full.leftJustified(32, ' ') + birthDate.toString();
    }
    QString getBadgeText() const override {
        QString formattedDate = QString("%1-%2-%3")
        .arg(birthDate.month, 2, 10, QChar('0'))
            .arg(birthDate.day, 2, 10, QChar('0'))
            .arg(birthDate.year, 4, 10, QChar('0'));
        return "<p style='font-size:16px; margin:0; line-height:1.2;'>" +
               firstName + "<br>" +
               "<i>" + middleName + "</i><br>" +
               "<b>" + lastName + "</b></p><br>" +
               "<span style='font-family:monospace; color:#444; font-size:14px;'>мм-дд-гггг<br><b>" + formattedDate + "</b></span>";
    }
};

#endif // PERSON_H
