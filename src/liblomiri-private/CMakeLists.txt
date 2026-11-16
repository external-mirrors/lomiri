add_library(lomiri-private SHARED
    abstractdbusservicemonitor.cpp
    lomiridbusobject.cpp
    lomiridbusvirtualobject.cpp
    wmpolicyinterface.cpp
)

set_target_properties(lomiri-private PROPERTIES
    VERSION 0.0.0
    SOVERSION 0
)

target_include_directories(lomiri-private PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lomiri-private PRIVATE Qt::DBus)

install(TARGETS lomiri-private LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
