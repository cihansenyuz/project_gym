cmake_minimum_required(VERSION 3.5)

project(desktop_application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "~/Qt/6.7.2/gcc_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        src/main.cpp

        src/gui/mainwindow.cpp
        src/gui/logindialog.cpp
        src/gui/infodialog.cpp
        src/gui/registerdialog.cpp
        src/gui/newmeasurementsdialog.cpp
        src/gui/exerciseplandialog.cpp
        src/gui/components/exercisedayview.cpp
        src/gui/components/exerciseweekview.cpp

        src/member/member.cpp
        src/member/measurement.cpp
        src/member/exercise/exercise.cpp
        src/member/exercise/strengthworkout.cpp
        src/member/exercise/cardioworkout.cpp
        src/member/exercise/dailyexerciseplan.cpp
        src/member/exercise/weeklyexerciseplan.cpp
        src/member/subscription/subscription.cpp
        src/member/subscription/payment.cpp
        src/member/subscription/paymentplan.cpp

        src/json/membermanager.cpp
        src/json/jsonparser.cpp
        src/json/jsoncontainer.cpp

        src/network/httpmanager.cpp
        src/network/networkcore.cpp
        src/network/postrequest.cpp
        src/network/getrequest.cpp
        src/network/putrequest.cpp

        inc/gui/mainwindow.h
        inc/gui/logindialog.h
        inc/gui/infodialog.h
        inc/gui/registerdialog.h
        inc/gui/newmeasurementsdialog.h
        inc/gui/exerciseplandialog.h
        inc/gui/components/exercisedayview.h
        inc/gui/components/exerciseweekview.h

        inc/member/member.h
        inc/member/measurement.h
        inc/member/exercise/exercise.h
        inc/member/exercise/strengthworkout.h
        inc/member/exercise/cardioworkout.h
        inc/member/exercise/dailyexerciseplan.h
        inc/member/exercise/weeklyexerciseplan.h
        inc/member/subscription/subscription.h
        inc/member/subscription/payment.h
        inc/member/subscription/paymentplan.h

        inc/json/membermanager.h
        inc/json/jsonparser.h
        inc/json/jsoncontainer.h

        inc/network/httpmanager.h
        inc/network/networkcore.h
        inc/network/postrequest.h
        inc/network/getrequest.h
        inc/network/putrequest.h

        ui/mainwindow.ui
        ui/logindialog.ui
        ui/infodialog.ui
        ui/registerdialog.ui
        ui/newmeasurementsdialog.ui
        ui/exerciseplandialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(desktop_application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
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

target_compile_definitions(desktop_application PRIVATE
                            #DEV_MODE
                            HOST="http://localhost:3000/"
                            #TOKEN="eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzI0NjQ3OTY2LCJleHAiOjE3MjQ2OTExNjZ9.Ew4Wxb3aJ2THurSLOKaq_eH6FjqFto0E6fA6rNQ8pPk"
                        )
target_link_libraries(desktop_application PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                                    Qt${QT_VERSION_MAJOR}::Network)

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
