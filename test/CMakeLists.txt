include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
    )

link_libraries(arktools_core)

add_executable(car car.cpp)
add_test(car ${CMAKE_CURRENT_BINARY_DIR}/car ${CMAKE_SOURCE_DIR}/data)
