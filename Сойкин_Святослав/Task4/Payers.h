#pragma once
#include "pch.h"
#include "Payer.h"

// Коллекция плательщиков за телефонные услуги
class Payers {
private:
    list<Payer> list_;  // Список плательщиков
    int nextId_ = 1;  // Счётчик для автоинкремента id

public:
    Payers();

    // Управление плательщиками
    void addPayer();  // Добавить нового плательщика в список
    void deleteById(int id);  // Удалить плательщика по id
    void changePayer(int id);  // Изменить данные плательщика (кроме id)

    // Отбор (фильтрация) плательщиков
    list<Payer> selectByPhone(const string& phone) const;  // По номеру телефона
    list<Payer> selectByName(const string& name) const;  // По фамилии и инициалам
    list<Payer> selectByTariff(double tariff) const;  // По тарифу
    list<Payer> selectByDiscount(int discount) const;  // По скидке (%)
    list<Payer> selectByDate(const Date& date) const;  // По дате платежа
    list<Payer> selectBySumRange(double low, double high) const;  // По диапазону суммы (отсортированы по телефону)

    // Аналитика
    double totalPayments() const;  // Полная сумма всех платежей

    // Сортировка списка
    void sortById();  // По идентификатору
    void sortByName();  // По фамилии
    void sortByPhone();  // По номеру телефона
    void sortBySumDescending();  // По сумме (убывание)
    void sortByTimeDescending();  // По времени разговоров (убывание)

    const list<Payer>& getList() const { return list_; }

    // Сохранение/загрузка в локальный формат
    void saveToCSV(const string& fname) const;  // Сохранить в CSV файл
    void loadFromCSV(const string& fname);  // Загрузить из CSV файла
};