cmake_minimum_required(VERSION 3.28)
project(lomiri VERSION 0.6.2 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

option(ENABLE_UBUNTU_ACCOUNTSSERVICE "Build with Ubuntu's fork of accountsservice" OFF)
option(CMAKE_COMPILE_WARNING_AS_ERROR "Treat warnings as errors" OFF)
option(WITH_MIR2 "Build against Mir 2" OFF)
set(DISPLAYED_DISTRO_NAME "" CACHE STRING "Shown in the first-run wizard, falls back to /etc/os-release")

include(CTest)
include(GNUInstallDirs)

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
pkg_check_modules(NOTIFICATIONS_API REQUIRED IMPORTED_TARGET lomiri-shell-notifications=3)
pkg_check_modules(PAM REQUIRED IMPORTED_TARGET pam)
pkg_check_modules(QMENUMODEL REQUIRED IMPORTED_TARGET qmenumodel)
pkg_check_modules(SYSTEMD systemd)

if (WITH_MIR2)
    pkg_check_modules(QTMIRSERVER REQUIRED IMPORTED_TARGET qt5mir2server>=0.6.0)
    pkg_check_modules(MIRAL REQUIRED IMPORTED_TARGET miral>=3.0)
    pkg_check_modules(MIROIL REQUIRED IMPORTED_TARGET miroil)
else()
    pkg_check_modules(QTMIRSERVER REQUIRED IMPORTED_TARGET qt5mir1server>=0.6.0)
    pkg_search_module(MIRAL REQUIRED IMPORTED_TARGET mir1al miral<3.0)
endif()

# Interface library making the private lomiri gestures headers available
add_library(lomiri-gestures-private INTERFACE)
target_include_directories(lomiri-gestures-private SYSTEM INTERFACE
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)
target_link_libraries(lomiri-gestures-private INTERFACE PkgConfig::LOMIRIGESTURES)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_link_options(LINKER:--no-undefined)
add_compile_options(-Wall -Wextra -pedantic)
add_compile_definitions(
    QT_NO_KEYWORDS
    QT_STRICT_ITERATORS
    QT_USE_QSTRINGBUILDER
)

set(SHELL_APP lomiri)
set(GREETER_APP lomiri-greeter)
set(DESKTOP_FILE_SHELL "${SHELL_APP}.desktop")
set(DESKTOP_FILE_GREETER "${GREETER_APP}.desktop")

set(SHELL_APP_FULL_DIR ${CMAKE_INSTALL_FULL_DATADIR}/lomiri)
set(SHELL_PRIVATE_FULL_LIBDIR ${CMAKE_INSTALL_FULL_LIBDIR}/lomiri)
set(SHELL_PRIVATE_FULL_LIBEXECDIR ${CMAKE_INSTALL_FULL_LIBEXECDIR}/lomiri)
set(SHELL_INSTALL_QML ${CMAKE_INSTALL_FULL_LIBDIR}/lomiri/qml)

add_subdirectory(data)
add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(plugins)
add_subdirectory(po)
add_subdirectory(qml)
add_subdirectory(src)
add_subdirectory(tools)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
