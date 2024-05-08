find_package(QmlPlugins)

add_definitions(-DQT_NO_KEYWORDS)

pkg_check_modules(LOMIRIGESTURES REQUIRED LomiriGestures)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

include_directories(
    SYSTEM
    ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
    ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
    ${LOMIRIGESTURES_INCLUDE_DIRS}
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)

set(LomiriTestQML_SOURCES
    testutil.cpp
    plugin.cpp
    TouchEventSequenceWrapper.cpp
)

if (ENABLE_TOUCH_EMULATION)
    set(LomiriTestQML_SOURCES ${LomiriTestQML_SOURCES} ${CMAKE_SOURCE_DIR}/src/MouseTouchAdaptor.cpp)
endif()

add_library(LomiriTestQml MODULE ${LomiriTestQML_SOURCES})
target_link_libraries(LomiriTestQml ${LOMIRIGESTURES_LIBRARIES} Qt5::Core Qt5::Quick Qt5::Test)

if (ENABLE_TOUCH_EMULATION)
    target_link_libraries(LomiriTestQml ${MOUSETOUCHADAPTOR_LIBS_LDFLAGS})
endif()

# To find libLomiriGestures.so
set_target_properties(LomiriTestQml PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${SHELL_PRIVATE_LIBDIR}")

# Substitute QtMir.Application version. However, since export_qmlfiles() can't
# find QML files in multiple places, all QML files have to be copied over.
file(GLOB QMLFILES
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*.qml
    ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
)
foreach(FILE ${QMLFILES})
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${FILE}
        ${CMAKE_CURRENT_BINARY_DIR}/processed/${FILE}
        @ONLY
    )
endforeach()


add_lomiri_mock(Lomiri.SelfTest 0.1 Lomiri/SelfTest
    SEARCH_PATH ${CMAKE_CURRENT_BINARY_DIR}/processed
    PREFIX utils TARGETS LomiriTestQml)
