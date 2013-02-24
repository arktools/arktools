set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")

link_directories(
    ${OPENSCENEGRAPH_LIBRARY_DIRS}
    ) 

link_libraries(
    ${PLIB_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OSGPLUGIN_LIBRARIES}
    ${OPENSCENEGRAPH_LIBRARIES}
    ${OPENGL_LIBRARIES}
    )
if (WIN32)
    link_libraries(lcms lzma)
endif()

include_directories(
    ${PLIB_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${OPENSCENEGRAPH_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    )
if (APPLE)
    link_libraries(
        ${COREFOUNDATION_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COCOA_LIBRARY}
        ${CARBON_LIBRARY}
        )
elseif(UNIX)
    link_libraries(rt Xrandr)
endif()

set(ARKTOOLS_CORE_HDRS
    Joystick.hpp
    AsyncSerial.hpp
    MAVLinkParser.hpp
    utilities.hpp
    Viewer.hpp
    osgUtils.hpp
    )

set(ARKTOOLS_CORE_SRCS
    Joystick.cpp
    AsyncSerial.cpp
    MAVLinkParser.cpp
    utilities.cpp
    terrain.cpp
    Viewer.cpp
    osgUtils.cpp
    )

add_library(arktools_core SHARED
    ${ARKTOOLS_CORE_HDRS}
    ${ARKTOOLS_CORE_SRCS}
    )

install(TARGETS arktools_core DESTINATION lib COMPONENT Runtime)
install(FILES ${ARKTOOLS_CORE_HDRS} DESTINATION include/${PROJECT_NAME} COMPONENT Dev)
