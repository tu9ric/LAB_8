#ifndef HASH_TABLE_H
#define  HASH_TABLE_H
#include <vector>
#include <iostream>
#include <string>

class HashTable {
private:
    // Хеш-функция для вычисления индекса ячейки для данного ключа
    int hashh(const std::string& item);
    // Таблица для хранения пар ключ-значение
    std::vector<std::vector<std::pair<std::string, int>>> table;

public:
    // Конструктор по умолчанию создает пустую таблицу на 10 позиций
    HashTable();

    // Добавление элемента в таблицу
    void push(const std::string& item, int price);

    // Удаление элемента из таблицы
    void remove(const std::string& item);

    // Поиск цены товара
    int get(const std::string& item);

    // Проверка на пустую таблицу
    bool empty();

    // Получение размера таблицы
    int size();
};


#endif