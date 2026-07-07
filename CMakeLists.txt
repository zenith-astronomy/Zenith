cmake_minimum_required(VERSION 3.16)

project(Zenith VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_library(CFITSIO_LIBRARY cfitsio REQUIRED)

qt_standard_project_setup()

qt_add_executable(Zenith
    src/main.cpp
    src/MainWindow.h
    src/MainWindow.cpp

    src/dialogs/AboutZenithDialog.h
    src/dialogs/AboutZenithDialog.cpp
    src/dialogs/AboutQtDialog.h
    src/dialogs/AboutQtDialog.cpp
)

target_link_libraries(Zenith PRIVATE
	Qt6::Widgets
	${CFITSIO_LIBRARY}
)
