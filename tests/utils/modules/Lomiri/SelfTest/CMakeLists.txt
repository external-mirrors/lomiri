find_package(QmlPlugins)

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

add_library(LomiriTestQml MODULE ${LomiriTestQML_SOURCES})
target_link_libraries(LomiriTestQml ${LOMIRIGESTURES_LIBRARIES} Qt5::Core Qt5::Quick Qt5::Test)

if (MOUSETOUCHADAPTOR_LIBS_FOUND)
    target_sources(LomiriTestQml PRIVATE MouseTouchAdaptor.cpp)
    target_compile_definitions(LomiriTestQml PRIVATE LOMIRI_ENABLE_TOUCH_EMULATION)
    target_link_libraries(LomiriTestQml ${MOUSETOUCHADAPTOR_LIBS_LDFLAGS})
endif()

# To find libLomiriGestures.so
set_target_properties(LomiriTestQml PROPERTIES INSTALL_RPATH "${SHELL_PRIVATE_FULL_LIBDIR}")

add_lomiri_mock(Lomiri.SelfTest 0.1 Lomiri/SelfTest PREFIX utils TARGETS LomiriTestQml)
