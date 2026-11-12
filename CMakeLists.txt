cmake_minimum_required(VERSION 3.28)
project(lomiri VERSION 0.6.2 LANGUAGES C CXX)

option (ENABLE_UBUNTU_ACCOUNTSSERVICE "Build with Ubuntu's fork of accountsservice" OFF)

set(SHELL_APP lomiri)
set(GREETER_APP lomiri-greeter)

set (DESKTOP_FILE_SHELL "${SHELL_APP}.desktop")
set (DESKTOP_FILE_GREETER "${GREETER_APP}.desktop")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# Instruct CMake to run moc and rcc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Make sure we have all the needed symbols
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,defs")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,defs")

set(QT_VERSION_MAJOR 5)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Concurrent Core DBus Gui Network Qml Quick Sql Svg Test Widgets Xml
)

find_package(Intl REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(APPLICATION_API REQUIRED IMPORTED_TARGET lomiri-shell-application=28)
pkg_check_modules(CONNECTIVITY REQUIRED IMPORTED_TARGET lomiri-connectivity-qt1)
pkg_check_modules(DEVICEINFO REQUIRED IMPORTED_TARGET deviceinfo)
pkg_check_modules(GD4 REQUIRED IMPORTED_TARGET gnome-desktop-4)
pkg_check_modules(GEONAMES REQUIRED IMPORTED_TARGET geonames>=0.2)
pkg_check_modules(GIO REQUIRED IMPORTED_TARGET gio-2.0>=2.32 gio-unix-2.0)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0>=2.32)
pkg_check_modules(GSETTINGS_QT REQUIRED IMPORTED_TARGET gsettings-qt)
pkg_check_modules(LAL REQUIRED IMPORTED_TARGET lomiri-app-launch-0>=0.1.5)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)
pkg_check_modules(LIBLIGHTDM REQUIRED IMPORTED_TARGET liblightdm-qt5-3)
pkg_check_modules(LIBSYSTEMD REQUIRED IMPORTED_TARGET libsystemd)
pkg_check_modules(LIBUDEV REQUIRED IMPORTED_TARGET libudev)
pkg_check_modules(LIBUSERMETRICSOUTPUT REQUIRED IMPORTED_TARGET libusermetricsoutput-1)
pkg_check_modules(LOMIRIGESTURES REQUIRED IMPORTED_TARGET LomiriGestures)
pkg_check_modules(LOMIRISCHEMA REQUIRED IMPORTED_TARGET lomiri-schemas>=0.1.13)
pkg_check_modules(MIRAL REQUIRED IMPORTED_TARGET miral>=3.0)
pkg_check_modules(MIROIL REQUIRED IMPORTED_TARGET miroil)
pkg_check_modules(NOTIFICATIONS_API REQUIRED IMPORTED_TARGET lomiri-shell-notifications=3)
pkg_check_modules(PAM REQUIRED IMPORTED_TARGET pam)
pkg_check_modules(QMENUMODEL REQUIRED IMPORTED_TARGET qmenumodel)
pkg_check_modules(QTMIRSERVER REQUIRED IMPORTED_TARGET qt5mir2server>=0.6.0)
pkg_check_modules(SYSTEMD systemd)

# Interface library making the private lomiri gestures headers available
add_library(lomiri-gestures-private INTERFACE)
target_include_directories(lomiri-gestures-private SYSTEM INTERFACE
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)
target_link_libraries(lomiri-gestures-private INTERFACE PkgConfig::LOMIRIGESTURES)

add_compile_definitions(
    QT_NO_KEYWORDS
    QT_STRICT_ITERATORS
    QT_USE_QSTRINGBUILDER
)

# Standard install paths
include(GNUInstallDirs)

set(SHELL_APP_FULL_DIR ${CMAKE_INSTALL_FULL_DATADIR}/lomiri)
set(SHELL_PRIVATE_FULL_LIBDIR ${CMAKE_INSTALL_FULL_LIBDIR}/lomiri)
set(SHELL_PRIVATE_FULL_LIBEXECDIR ${CMAKE_INSTALL_FULL_LIBEXECDIR}/lomiri)

# Convention for where lomiri's own QML plugins install to and get loaded
# from; other packages implementing a shell interface (e.g. qtmir,
# lomiri-notifications) install their QML plugins here too.
set(SHELL_INSTALL_QML ${CMAKE_INSTALL_FULL_LIBDIR}/lomiri/qml)

execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=plugin_private_module_dir LomiriSystemSettings OUTPUT_VARIABLE LOMIRI_SYSTEM_SETTINGS_PRIVATE_PLUGINDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
if(LOMIRI_SYSTEM_SETTINGS_PRIVATE_PLUGINDIR STREQUAL "")
    message(FATAL_ERROR "Could not determine LomiriSystemSettings private plugin installation dir.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-permissive -pedantic -Wall -Wextra")

set (CMAKE_CXX_STANDARD 20)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "relwithdebinfo")
    option(Werror "Treat warnings as errors" ON)
else()
    option(Werror "Treat warnings as errors" OFF)
endif()

if (Werror)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

set(MOCK_INDICATOR_SERVICE_APP lomiri-mock-indicator-service)

# add subdirectories to build
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(qml)

# Tests
set(NO_TESTS OFF CACHE BOOL "Disable tests.")
if (NOT NO_TESTS)
    include(CTest)
    add_subdirectory(tests)
else()
    message(STATUS "Tests disabled")
endif()

set(DISPLAYED_DISTRO_NAME "" CACHE STRING
    "The distro name displayed in first-run wizard and other places. If not set, will read /etc/os-release")
add_subdirectory(plugins)
add_subdirectory(data)
add_subdirectory(po)
add_subdirectory(doc)
