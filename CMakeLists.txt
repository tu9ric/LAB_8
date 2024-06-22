cmake_minimum_required(VERSION 3.5) # Минимальная версия CMake
project(multifile)

# Добавляем все исходные файлы проекта
set(SOURCE_FILES main.cpp options.cpp hash_table)
# Создаем исполняемый файл с именем соответствующим имени проекта
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenCV REQUIRED) # Поиск пакета OpenCV
find_package(OpenSSL REQUIRED) # Поиск пакета OPENSSL
target_link_libraries(multifile ${OpenCV_LIBS}) # Линковка с библиотеками OpenCV
target_link_libraries(multifile ${OPENSSL_LIBRARIES}) # Линковка с библиотеками OPENSSL

