#---- BUILD TEST ----

project(test)

add_executable(test main.cpp)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/engine)
target_link_libraries(test engine)

if (WIN32)
    target_link_libraries(test gdi32 user32 kernel32)
endif (WIN32)