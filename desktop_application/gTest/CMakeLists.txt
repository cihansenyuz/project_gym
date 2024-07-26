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
  ../src/member/measurement.cpp
  ../inc/member/measurement.h
  exercise_fixture.cpp
  ../src/member/exercise/exercise.cpp
  ../inc/member/exercise/exercise.h
  ../src/member/exercise/cardioworkout.cpp
  ../inc/member/exercise/cardioworkout.h
  ../src/member/exercise/strengthworkout.cpp
  ../inc/member/exercise/strengthworkout.h
  dailyexerciseplan_fixture.cpp
  ../src/member/exercise/dailyexerciseplan.cpp
  ../inc/member/exercise/dailyexerciseplan.h
  ../src/member/exercise/cardioworkout.cpp
  ../inc/member/exercise/cardioworkout.h
  ../src/member/exercise/strengthworkout.cpp
  ../inc/member/exercise/strengthworkout.h
  weeklyexerciseplan_fixture.cpp
  ../src/member/exercise/weeklyexerciseplan.cpp
  ../inc/member/exercise/weeklyexerciseplan.h
  subscription_fixture.cpp
  ../src/member/subscription.cpp
  ../inc/member/subscription.h
  member_fixture.cpp
  ../src/member/member.cpp
  ../inc/member/member.h
  payment_fixture.cpp
  ../src/member/payment.cpp
  ../inc/member/payment.h
  paymentplan_fixture.cpp
  ../src/member/paymentplan.cpp
  ../inc/member/paymentplan.h
)

add_executable(desktop_app_test ${PROJECT_SOURCES})
target_link_libraries(desktop_app_test PRIVATE Qt6::Core GTest::GTest GTest::Main)
add_test(All_Unit_Test desktop_app_test)
