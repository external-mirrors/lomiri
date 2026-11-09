include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

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
add_definitions(-DLOMIRIINDICATORS_LIBRARY)

add_library(IndicatorsQml SHARED
    ${IndicatorsQML_SOURCES}
)

target_link_libraries(IndicatorsQml PRIVATE
    PkgConfig::GIO
    PkgConfig::GLIB
    PkgConfig::QMENUMODEL
    Qt::Core
    Qt::DBus
    Qt::Qml
    Qt::Quick
)

add_lomiri_plugin(Lomiri.Indicators 0.1 Lomiri/Indicators TARGETS IndicatorsQml)
