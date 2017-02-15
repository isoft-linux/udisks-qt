set(CMAKE_AUTOMOC ON)
add_definitions(-std=c++11)

add_executable(test-udisksclient
    test-udisksclient.cpp)
target_include_directories(test-udisksclient PRIVATE
    ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test-udisksclient
    Qt5::Test 
    udisks2-qt5)
add_test(test-udisksclient test-udisksclient)

set(testudisksclientgui_SRC
    test-udisksclient-gui.cpp
)

qt5_add_dbus_interface(testudisksclientgui_SRC ${CMAKE_CURRENT_SOURCE_DIR}/org.isoftlinux.OSProber.xml osprober)

add_executable(test-udisksclient-gui
    ${testudisksclientgui_SRC})
target_include_directories(test-udisksclient-gui PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(test-udisksclient-gui
    Qt5::Test 
    Qt5::Widgets
    udisks2-qt5)
add_test(test-udisksclient-gui test-udisksclient-gui)
