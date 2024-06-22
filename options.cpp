#include "options.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <openssl/engine.h>
#include <openssl/sha.h>
#include <openssl/evp.h>


size_t hashFunction(const std::string &name) {
    // Инициализация значения хэша
    size_t hash = 131;
    for (char c : name) {
        // Для каждого символа в строке умножаем текущее значение хэша на 131 и добавляем hash и ASCII-значение символа.
        hash = (((hash * 131)+ hash ) + c);
    }
    return hash;
}

void enrolled(const std::string &filename, std::unordered_map<size_t, std::string> &voters) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        size_t hash_value = hashFunction(line);
        if (voters.find(hash_value) == voters.end()) { 
            // Если нет, то добавляем фамилию в список 
            voters.insert({hash_value, line});
        }
    }
}


void unenrolled(const std::string &surname, std::unordered_map<size_t, std::string> &voters, int &duplicates) {
    size_t hash_value = hashFunction(surname);
    if (voters.find(hash_value) == voters.end()) {
        voters.insert({hash_value, surname});  // Добавление пары (хэш, фамилия)
    } else {
        duplicates++;
    }
}

void calculateSHA256(const cv::Mat& img, unsigned char* md_buf)
{
    // Вычисляем хэш-сумму по алгоритму SHA256 для исходного изображения
    //функция, которая создает новый контекст хэширования. 
    EVP_MD_CTX* ctx1 = EVP_MD_CTX_new();
    //Инициализация контекста хэширования
    EVP_DigestInit_ex(ctx1, EVP_sha256(), nullptr);
    //вычисление длины данных
    size_t len = img.total() * img.elemSize();
    //обновление контекста хэширования
    EVP_DigestUpdate(ctx1, img.data, len);
    //финализация хэширования(вычисляет окончательную сумму) 
    EVP_DigestFinal_ex(ctx1, md_buf, nullptr);
    // Очищаем память
    EVP_MD_CTX_free(ctx1);
};