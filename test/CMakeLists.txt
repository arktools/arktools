include_directories(${CMAKE_SOURCE_DIR}/src)
link_libraries(arktools_core)

add_executable(osgTest
    osgTest.cpp
    )

add_test(OsgTest ${CMAKE_CURRENT_BINARY_DIR}/osgTest ${CMAKE_SOURCE_DIR}/data)
