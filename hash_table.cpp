#include "hash_table.h"

// Таблица для хранения пар ключ-значение
std::vector<std::vector<std::pair<std::string, int>>> table;

int HashTable::hashh(const std::string& item) {
    int hash = 0;
    for (char c : item) {
        hash += c;
    }//ASCII на размер табл
    return hash % table.size();
};


// Конструктор по умолчанию создает пустую таблицу на 10 позиций
HashTable::HashTable() : table(10, std::vector<std::pair<std::string, int>>()) {}

void HashTable::push(const std::string& item, int price) {
    // Вычисляем индекс ячейки для данного ключа
    int index = hashh(item);
    // Добавляем пару ключ-значение в ячейку
    table[index].push_back(make_pair(item, price));
};

void HashTable::remove(const std::string& item) {
    // Вычисляем индекс ячейки для данного ключа
    int index = hashh(item);
    // Ищем пару ключ-значение в ячейке
    for (auto it = table[index].begin(); it != table[index].end(); it++) {
        if (it->first == item) {
            // Удаляем пару ключ-значение из ячейки
            table[index].erase(it);
            return;
        }
    }
};

int HashTable::get(const std::string& item) {
    // Вычисляем индекс ячейки для данного ключа
    int index = hashh(item);
    // Ищем пару ключ-значение в ячейке
    for (auto it = table[index].begin(); it != table[index].end(); it++) {
        if (it->first == item) {
            // Возвращаем цену
            return it->second;
        }
    }
    return -1;
};

bool HashTable::empty() {
    // Проверяем, пуста ли каждая ячейка таблицы
    for (const auto& cell : table) {
        if (!cell.empty()) {
            return false;
        }
    }
    return true;
};

int HashTable::size() {
    return table.size();
};
