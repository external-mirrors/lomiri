# Some tests need to link this as a library while also including
# it as a QML module, so only build it as a single shared library.
add_library(mockqmenumodelplugin SHARED plugin.cpp)
qt_add_qml_module(mockqmenumodelplugin
    URI QMenuModel
    VERSION 1.0
    PLUGIN_TARGET mockqmenumodelplugin
    SOURCES
        actiondata.h
        actionstateparser.cpp
        ayatanamenumodel.cpp
        dbus-enums.h
    QML_FILES
        AyatanaMenuAction.qml
        QDBusActionGroup.qml
)

target_include_directories(mockqmenumodelplugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(mockqmenumodelplugin PRIVATE Qt::Core Qt::Quick)

install_qml_module(mockqmenumodelplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
