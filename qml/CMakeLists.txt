file(GLOB_RECURSE QML_JS_FILES
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*.qml
    ${CMAKE_CURRENT_SOURCE_DIR}/*.js
    ${CMAKE_CURRENT_SOURCE_DIR}/*.png
    ${CMAKE_CURRENT_SOURCE_DIR}/*.sci
    ${CMAKE_CURRENT_SOURCE_DIR}/*.svg
    ${CMAKE_CURRENT_SOURCE_DIR}/qmldir)

foreach(FILE ${QML_JS_FILES})
    if (${FILE} MATCHES "\.qml$")
        configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/${FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/${FILE}
            @ONLY)
    else ()
        configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/${FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/${FILE}
            COPYONLY)
    endif ()

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${FILE}
        DESTINATION ${SHELL_APP_DIR}
    )
endforeach()
