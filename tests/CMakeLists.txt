set(CMAKE_AUTOMOC ON)

add_executable(test-udisksclient
    test-udisksclient.cpp)
target_include_directories(test-udisksclient PRIVATE
    ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test-udisksclient
    Qt5::Test 
    udisks2-qt5)
add_test(test-udisksclient test-udisksclient)
