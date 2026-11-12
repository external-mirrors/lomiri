set(IndicatorsQML_SOURCES
    actionrootstate.cpp
    indicator.cpp
    indicators.h
    indicatorsmanager.cpp
    indicatorsmodel.cpp
    menucontentactivator.cpp
    modelactionrootstate.cpp
    modelprinter.cpp
    plugin.cpp
    rootstateparser.cpp
    sharedlomirimenumodel.cpp
    lomirimenumodelcache.cpp
    lomirimenumodelstack.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Platform/platform.cpp
)

add_library(IndicatorsQml SHARED
    ${IndicatorsQML_SOURCES}
)

target_compile_definitions(IndicatorsQml PRIVATE LOMIRIINDICATORS_LIBRARY)

target_link_libraries(IndicatorsQml PRIVATE
    lomiri-paths
    PkgConfig::GIO
    PkgConfig::GLIB
    PkgConfig::QMENUMODEL
    Qt::Core
    Qt::DBus
    Qt::Qml
    Qt::Quick
)

add_lomiri_plugin(Lomiri.Indicators 0.1 Lomiri/Indicators TARGETS IndicatorsQml)
