cmake_minimum_required(VERSION 3.14)
project(desktop_app_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)

set (PROJECT_SOURCES
  measurements_fixture.cpp
  ../src/measurement.cpp
  ../inc/measurement.h
  member_fixture.cpp
  ../src/member.cpp
  ../inc/member.h
  ../src/subscription.cpp
  ../inc/subscription.h
)

add_executable(desktop_app_test ${PROJECT_SOURCES})
target_link_libraries(desktop_app_test PRIVATE Qt6::Core GTest::GTest GTest::Main)
add_test(Measurements_Unit_Test desktop_app_test)
