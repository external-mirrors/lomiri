find_package(QmlPlugins)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

include_directories(
    SYSTEM
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)

set(LomiriTestQML_SOURCES
    testutil.cpp
    plugin.cpp
    TouchEventSequenceWrapper.cpp
)

add_library(LomiriTestQml MODULE ${LomiriTestQML_SOURCES})

target_link_libraries(LomiriTestQml PRIVATE
    PkgConfig::LOMIRIGESTURES
    Qt::Core
    Qt::GuiPrivate
    Qt::Quick
    Qt::QuickPrivate
    Qt::Test
)

if (MOUSETOUCHADAPTOR_LIBS_FOUND)
    target_sources(LomiriTestQml PRIVATE MouseTouchAdaptor.cpp)
    target_compile_definitions(LomiriTestQml PRIVATE LOMIRI_ENABLE_TOUCH_EMULATION)
    target_link_libraries(LomiriTestQml PRIVATE PkgConfig::MOUSETOUCHADAPTOR_LIBS)
endif()

# To find libLomiriGestures.so
set_target_properties(LomiriTestQml PROPERTIES INSTALL_RPATH "${SHELL_PRIVATE_FULL_LIBDIR}")

add_lomiri_mock(Lomiri.SelfTest 0.1 Lomiri/SelfTest PREFIX utils TARGETS LomiriTestQml)
