cmake_minimum_required(VERSION 3.13)

project(prueba-qt5)

# Find the QtWidgets library
find_package(Qt5Widgets)

add_executable(ejercicio_1 ejercicio_1.cpp)
add_executable(ejercicio_2 ejercicio_2.cpp)
add_executable(ejercicio_3 ejercicio_3.cpp)
add_executable(ejercicio_4 ejercicio_4.cpp)
add_executable(ejercicio_5 ejercicio_5.cpp)
add_executable(ejercicio_6 ejercicio_6.cpp)
add_executable(ejercicio_7 ejercicio_7.cpp)
add_executable(ejercicio_8 ejercicio_8.cpp)
add_executable(ejercicio_9 ejercicio_9.cpp)
add_executable(ejercicio_10 ejercicio_10.cpp)
add_executable(ejercicio_11 ejercicio_11.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(ejercicio_1 Qt5::Widgets)
target_link_libraries(ejercicio_2 Qt5::Widgets)
target_link_libraries(ejercicio_3 Qt5::Widgets)
target_link_libraries(ejercicio_4 Qt5::Widgets)
target_link_libraries(ejercicio_5 Qt5::Widgets)
target_link_libraries(ejercicio_6 Qt5::Widgets)
target_link_libraries(ejercicio_7 Qt5::Widgets)
target_link_libraries(ejercicio_8 Qt5::Widgets)
target_link_libraries(ejercicio_9 Qt5::Widgets)
target_link_libraries(ejercicio_10 Qt5::Widgets)
target_link_libraries(ejercicio_11 Qt5::Widgets)
