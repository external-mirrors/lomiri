set(LIB_NAME "lomiri-private")
set(SOVERSION 0)
set(VERSION ${SOVERSION}.0.0)

project(lib${LIB_NAME})

set(lib${LIB_NAME}_SRCS
    abstractdbusservicemonitor.cpp
    lomiridbusobject.cpp
    lomiridbusvirtualobject.cpp
    wmpolicyinterface.cpp
    )

add_library(${LIB_NAME} SHARED
    ${lib${LIB_NAME}_SRCS}
    )

set_target_properties(${LIB_NAME} PROPERTIES
    VERSION ${VERSION}
    SOVERSION ${SOVERSION}
    )

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIB_NAME} PRIVATE Qt::DBus)

# install library
install(TARGETS ${LIB_NAME}
     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
