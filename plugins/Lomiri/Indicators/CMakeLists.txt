add_library(indicatorsplugin MODULE plugin.cpp)
qt_add_qml_module(indicators STATIC
    URI Lomiri.Indicators
    VERSION 0.1
    PLUGIN_TARGET indicatorsplugin
    SOURCES
        actionrootstate.cpp
        indicator.cpp
        indicators.h
        indicatorsmanager.cpp
        indicatorsmodel.cpp
        lomirimenumodelcache.cpp
        lomirimenumodelstack.cpp
        menucontentactivator.cpp
        modelactionrootstate.cpp
        modelprinter.cpp
        rootstateparser.cpp
        sharedlomirimenumodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Platform/platform.cpp
)

target_compile_definitions(indicators PRIVATE LOMIRIINDICATORS_LIBRARY)

target_link_libraries(indicators
    PUBLIC
        PkgConfig::QMENUMODEL
        Qt::Core
        Qt::DBus
        Qt::Qml
        Qt::Quick
    PRIVATE
        lomiri-paths
        PkgConfig::GIO
        PkgConfig::GLIB
)

install_qml_module(indicators DESTINATION ${SHELL_INSTALL_QML})
