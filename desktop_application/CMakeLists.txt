cmake_minimum_required(VERSION 3.10)

project(DesktopApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.7.0/gcc_64" "~/Qt/6.7.1/gcc_64")
find_package(Qt6 REQUIRED  COMPONENTS Core Gui)

set(PROJECT_SOURCES
    main.cpp
)

add_executable(DesktopApp ${PROJECT_SOURCES} )
target_link_libraries(DesktopApp PRIVATE Qt6::Core Qt6::Gui)
