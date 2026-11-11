add_executable(tst-wizard-pagelist
    tst_pagelist.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/PageList.cpp
)
target_include_directories(tst-wizard-pagelist PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Wizard)
target_link_libraries(tst-wizard-pagelist PRIVATE lomiri-paths Qt::Core Qt::Qml Qt::Test)
install(TARGETS tst-wizard-pagelist
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Wizard"
)
add_lomiri_unittest(WizardPageList tst-wizard-pagelist ENVIRONMENT WIZARD_TESTING=1)

add_executable(tst-wizard-system
    tst_system.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/System.cpp
)
target_include_directories(tst-wizard-system PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Wizard)
target_link_libraries(tst-wizard-system PRIVATE Qt::Core Qt::DBus Qt::Qml Qt::Test)
install(TARGETS tst-wizard-system
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Wizard"
)
add_lomiri_unittest(WizardSystem tst-wizard-system)
