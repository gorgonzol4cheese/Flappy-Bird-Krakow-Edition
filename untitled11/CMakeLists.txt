cmake_minimum_required(VERSION 3.20)
project(untitled11)

set(CMAKE_CXX_STANDARD 17)

# Добавляем путь, куда Homebrew устанавливает библиотеки на Mac
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

# Ищем SFML 3
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(untitled11 main.cpp)

# Привязываем библиотеки
target_link_libraries(untitled11 SFML::Graphics SFML::Window SFML::System)

# Копируем картинки
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})