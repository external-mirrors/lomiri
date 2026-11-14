qt_add_qml_module(selftestplugin
    URI Lomiri.SelfTest
    VERSION 0.1
    PLUGIN_TARGET selftestplugin
    SOURCES
        plugin.cpp
        testutil.cpp
        TouchEventSequenceWrapper.cpp
    QML_FILES
        LomiriTestCase.qml
        MouseTouchEmulationCheckbox.qml
        StageTestCase.qml
)

target_include_directories(selftestplugin PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(selftestplugin PRIVATE
    lomiri-gestures-private
    Qt::Core
    Qt::GuiPrivate
    Qt::Quick
    Qt::QuickPrivate
    Qt::Test
)

if (MOUSETOUCHADAPTOR_LIBS_FOUND)
    target_sources(selftestplugin PRIVATE MouseTouchAdaptor.cpp)
    target_compile_definitions(selftestplugin PRIVATE LOMIRI_ENABLE_TOUCH_EMULATION)
    target_link_libraries(selftestplugin PRIVATE PkgConfig::MOUSETOUCHADAPTOR_LIBS)
endif()

# To find libLomiriGestures.so
set_target_properties(selftestplugin PROPERTIES INSTALL_RPATH "${SHELL_PRIVATE_FULL_LIBDIR}")

install_qml_module(selftestplugin DESTINATION ${SHELL_INSTALL_QML}/utils)
