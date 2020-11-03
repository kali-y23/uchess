cmake_minimum_required(VERSION 3.16.2)

project(utaglib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH=/usr/local/Cellar/qt/5.15.1/)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(TARGET uchess)
set(SOURCES main.cpp gamewindow.cpp graphicsview.cpp qfigure.cpp)
set(CHESS figures/gamemanager.cpp
          figures/abstractfigure.cpp
          figures/knight.cpp
          figures/pawn.cpp
          figures/rook.cpp
          figures/bishop.cpp
          figures/queen.cpp
          figures/king.cpp)

qt5_add_resources(SOURCES ../resources/resources.qrc)

include_directories(figures)

add_executable(${TARGET} ${SOURCES} ${CHESS})

target_include_directories(${TARGET} PUBLIC ${Qt5Widgets_INCLUDE_DIRS})
target_link_libraries(${TARGET} PRIVATE Qt5::Widgets)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)