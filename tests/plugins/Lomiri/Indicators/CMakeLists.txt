set(INDICATORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../plugins/Lomiri/Indicators)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

macro(indicator_test TEST)
    set(multi_value_keywords ADDITIONAL_CPPS ADDITIONAL_LIBS)
    cmake_parse_arguments(test "" "" "${multi_value_keywords}" ${ARGN})

    add_executable(${TEST}Exec
            ${TEST}Test.cpp
            ${test_ADDITIONAL_CPPS}
        )
    target_include_directories(${TEST}Exec PRIVATE
        ${INDICATORS_DIR}
        ${TEST_DIR}/mocks/QMenuModel.1
    )
    target_link_libraries(${TEST}Exec PRIVATE
        ${test_ADDITIONAL_LIBS}
        lomiri-paths
        PkgConfig::GIO
        PkgConfig::GLIB
        PkgConfig::QMENUMODEL
        Qt::Core
        Qt::DBus
        Qt::Gui
        Qt::Qml
        Qt::Test
        Qt::Widgets
    )
    install(TARGETS ${TEST}Exec
        DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Lomiri/Indicators"
        )
    add_lomiri_unittest(${TEST} ${TEST}Exec)
endmacro(indicator_test)

indicator_test(IndicatorsManager ADDITIONAL_LIBS indicators)
indicator_test(IndicatorsModel ADDITIONAL_LIBS indicators)
indicator_test(MenuContentActivator ADDITIONAL_CPPS ${INDICATORS_DIR}/menucontentactivator.cpp)
indicator_test(LomiriMenuModelStack ADDITIONAL_CPPS ${TEST_DIR}/mocks/QMenuModel.1/ayatanamenumodel.cpp ${INDICATORS_DIR}/lomirimenumodelstack.cpp)
indicator_test(RootActionState ADDITIONAL_LIBS indicators)
indicator_test(SharedLomiriMenuModel ADDITIONAL_LIBS indicators)
