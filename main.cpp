#include "options.h"
#include <iomanip>
#include "hash_table.h"
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <openssl/sha.h>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

int main() {
    std::cout<<"Exersize 1 "<<std::endl;
    std::unordered_map<size_t, std::string> voters; // Для хранения хэшей и фамилий 
    int duplicates = 0; 

    std::string filename = "C:/Users/artem/OneDrive/Desktop/Study/Programming/LAB_8/surnames.txt";
    
    enrolled(filename, voters);

    std::string input;
    
    while (true) {
        std::cout << "Введите фамилии для голосования (введите 'end' для завершения): ";
        std::cin >> input;
        if (input == "end") {
            break;
        }
        unenrolled(input, voters, duplicates);
    }

    std::cout << "Количество голосующих: " << voters.size() << std::endl;
    std::cout << "Количество дубликатов: " << duplicates << std::endl;

    std::cout << "Фамилии голосующих:" << std::endl;
    for (const auto &entry : voters) {
        std::cout << entry.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Exersize 2" << std::endl;
    // Создаем хэш-таблицу
    HashTable t;

    // Добавляем несколько элементов в таблицу
    t.push("Кирпич", 145);
    t.push("Шпилька", 12000);
    t.push("Шайба", 10000);
    t.push("Гайка", 22000);
    t.push("Винт", 17000);

    int hammerPrice = t.get("Кирпич");
    std::cout << "Кирпич стоит: " << hammerPrice << std::endl; 

    // Удаляем элемент из таблицы
    t.remove("Шпилька");

    // Проверяем, есть ли в таблице элемент 
    bool examination = t.get("Шпилька") != -1;
    std::cout << "Наличие шпильки " << (examination ? "есть" : "нету") << std::endl;  

    // Проверяем, пуста ли таблица
    bool isEmpty = t.empty();
    std::cout << "Пуста ли таблица: " << (isEmpty ? "да" : "нет") << std::endl;

    // Получаем размер таблицы
    int size = t.size();
    std::cout << "Размер таблицы: " << size << std::endl;  
    
    
    std::cout<<"\nExersize 3\n";
    std::string file_name = "C:/Users/artem/OneDrive/Desktop/Study/Programming/LAB_8/photo.jpg";
    cv::Mat img = cv::imread(file_name);
    if (img.empty()) {
        std::cerr << "Ошибка чтения изображения" << std::endl;
        return 1;
    }

    // Выделяем память для буфера хэша
    unsigned char* md_buf1 = (unsigned char*)malloc(SHA256_DIGEST_LENGTH);
    unsigned char* md_buf2 = (unsigned char*)malloc(SHA256_DIGEST_LENGTH);

    // Расчет хэша для исходного изображения
    calculateSHA256(img, md_buf1);

    // Изменяем значение одного канала одного пикселя изображения
    int x, y, channel;
    std::cout << "Введите x, y: ";
    std::cin >> x >> y;
    std::cout << "Введите номер канала (0 - синий, 1 - зеленый, 2 - красный): ";
    std::cin >> channel;

    img.at<cv::Vec3b>(y, x)[channel] = 255;

    // Расчет хэша для измененного изображения
    calculateSHA256(img, md_buf2);
    
    // Сравниваем две хэш-суммы
    bool equal = memcmp(md_buf1, md_buf2, SHA256_DIGEST_LENGTH) == 0;

    // Сохраняем хэш-суммы и результат сравнения в txt-файл
    std::ofstream file("C:/Users/artem/OneDrive/Desktop/Study/Programming/LAB_8/otvet.txt");
    if (!file) {
        std::cerr << "Ошибка открытия файла для записи" << std::endl;
        return 1;
    }

    std::cout << "Хэш-сумма исходного изображения: ";
    file << "Хэш-сумма исходного изображения: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        std::cout << std::hex << int(md_buf1[i]);
        file << std::hex << int(md_buf1[i]);
    }

    
    std::cout << std::endl;
    file << std::endl;
    std::cout << "Хэш-сумма измененного изображения: ";
    file << "Хэш-сумма измененного изображения: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        std::cout << std::hex << int(md_buf2[i]);
        file << std::hex << int(md_buf2[i]);
    }

    std::cout << std::endl;
    file << std::endl;
    std::cout << "Хэш-суммы равны: " << (equal ? "да" : "нет") << std::endl;
    file << "Хэш-суммы равны: " << (equal ? "да" : "нет") << std::endl;

    file.close();

    // Очищаем память
    free(md_buf1);
    free(md_buf2);

    
    return 0;
}