#pragma once
#include "pch.h"
#include "Object.h"
#include "Date.h"

// Плательщик за телефонные услуги
class Payer : public Object {
private:
    int id_;  // Числовой идентификатор
    string name_;  // Фамилия и инициалы
    string phone_;  // Номер телефона
    double tariff_;  // Тариф за минуту разговора
    int discount_;  // Скидка в процентах
    int timeMin_;  // Суммарное время разговоров за месяц (в минутах)
    Date date_;  // Дата платежа

public:
    // Фабричный метод для создания плательщика с генерируемыми данными
    static Payer createFactory(int id);

    // Геттеры для доступа к полям
    int getId() const { return id_; }
    string getName() const { return name_; }
    string getPhone() const { return phone_; }
    double getTariff() const { return tariff_; }
    int getDiscount() const { return discount_; }
    int getTimeMin() const { return timeMin_; }
    Date getDate() const { return date_; }

    // Вычислить сумму платежа: время * тариф * (1 - скидка%)
    double calculateSum() const { return timeMin_ * tariff_ * (1 - discount_ / 100.0); }

    // Сеттеры для изменения полей
    void setId(int id) { id_ = id; }
    void setName(const string& name) { name_ = name; }
    void setPhone(const string& phone) { phone_ = phone; }
    void setTariff(double tariff) { tariff_ = tariff; }
    void setDiscount(int discount) { discount_ = discount; }
    void setTimeMin(int timeMin) { timeMin_ = timeMin; }
    void setDate(short d, short m, short y) { date_.setDate(d, m, y); }

    // Строковое представление объекта для вывода
    string toString() const override;
};