cmake_minimum_required(VERSION 3.5)

project(desktop_application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/member.cpp
        src/measurement.cpp
        src/membermanager.cpp
        src/subscription.cpp
        src/exercise.cpp
        src/strengthworkout.cpp
        src/cardioworkout.cpp
        src/dailyexerciseplan.cpp
        src/weeklyexerciseplan.cpp
        src/jsonparser.cpp
        src/jsoncontainer.cpp

        inc/mainwindow.h
        inc/member.h
        inc/measurement.h
        inc/membermanager.h
        inc/subscription.h
        inc/exercise.h
        inc/strengthworkout.h
        inc/cardioworkout.h
        inc/dailyexerciseplan.h
        inc/weeklyexerciseplan.h
        inc/jsonparser.h
        inc/jsoncontainer.h

        ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(desktop_application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        members.json
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET desktop_application APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(desktop_application SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(desktop_application
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(desktop_application PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.desktop_application)
endif()
set_target_properties(desktop_application PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS desktop_application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(desktop_application)
endif()
