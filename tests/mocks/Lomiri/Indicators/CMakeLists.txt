qt_add_qml_module(mockindicatorsplugin
    URI Lomiri.Indicators
    VERSION 0.1
    PLUGIN_TARGET mockindicatorsplugin
    SOURCES
        fakeindicatorsmodel.cpp
        fakelomirimenumodelcache.cpp
        fakeplugin.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators/indicators.h
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators/lomirimenumodelcache.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators/lomirimenumodelstack.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators/menucontentactivator.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators/modelprinter.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators/sharedlomirimenumodel.cpp
    QML_FILES
        ActionRootState.qml
        fakeindicatorsmodeldata.js
        IndicatorsModel.qml
        ModelActionRootState.qml
)

target_include_directories(mockindicatorsplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Indicators)

target_compile_definitions(mockindicatorsplugin PRIVATE LOMIRIINDICATORS_LIBRARY)

target_link_libraries(mockindicatorsplugin PRIVATE
    mockqmenumodelplugin
    Qt::Core
    Qt::Qml
    Qt::Quick
)

set_target_properties(mockindicatorsplugin PROPERTIES
    INSTALL_RPATH "${SHELL_INSTALL_QML}/mocks/QMenuModel"
)

install_qml_module(mockindicatorsplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
