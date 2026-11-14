########## tst_DragHandle

add_executable(DragHandleTestExec tst_DragHandle.cpp)

target_compile_definitions(DragHandleTestExec PRIVATE TEST_DIR="qmltests/Components")

target_link_libraries(DragHandleTestExec PRIVATE
    gesturesplugin
    lomiri-gestures-private
    lomiri-paths
    Qt::Core
    Qt::Gui
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
    Qt::Test
)

install(TARGETS DragHandleTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/qmltests/Components"
    )
set_target_properties(DragHandleTestExec PROPERTIES
    INSTALL_RPATH "${SHELL_INSTALL_QML}/Lomiri/Gestures:${SHELL_PRIVATE_FULL_LIBDIR}"
    )

add_lomiri_uitest(DragHandle DragHandleTestExec)
add_manual_qml_test(. DragHandle IMPORT_PATHS ${LOMIRI_IMPORT_PATHS})
add_lomiri_qmltest_data(. tst_DragHandle.qml)
add_lomiri_qmltest_data(. tst_DragHandle)

########## tst_EdgeDragEvaluator
add_executable(EdgeDragEvaluatorTestExec tst_EdgeDragEvaluator.cpp)

target_compile_definitions(EdgeDragEvaluatorTestExec PRIVATE TEST_DIR="qmltests/Components")

target_link_libraries(EdgeDragEvaluatorTestExec PRIVATE
    gesturesplugin
    lomiri-gestures-private
    lomiri-paths
    Qt::Core
    Qt::Gui
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
    Qt::Test
)

install(TARGETS EdgeDragEvaluatorTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/qmltests/Components"
    )
set_target_properties(EdgeDragEvaluatorTestExec PROPERTIES
    INSTALL_RPATH "${SHELL_INSTALL_QML}/Lomiri/Gestures:${SHELL_PRIVATE_FULL_LIBDIR}"
    )

add_lomiri_uitest(EdgeDragEvaluator EdgeDragEvaluatorTestExec)
add_lomiri_qmltest_data(. tst_EdgeDragEvaluator.qml)
