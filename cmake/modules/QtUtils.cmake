# Minimal Qt5 compatibility helper for qt_add_qml_module()
if(QT_VERSION_MAJOR EQUAL 5)
    function(qt_add_qml_module target)
        cmake_parse_arguments(PARSE_ARGV 1 arg
            "" "URI;VERSION;PLUGIN_TARGET" "SOURCES;QML_FILES"
        )

        # Create relevant targets / add sources
        if(arg_SOURCES)
            if(arg_PLUGIN_TARGET STREQUAL target)
                if(TARGET ${target})
                    # Case 1: plugin == backing target and it exists as shared library
                    target_sources(${target} PRIVATE ${arg_SOURCES})
                else()
                    # Case 2: plugin == backing target and it doesn't exist
                    add_library(${target} MODULE ${arg_SOURCES})
                endif()
            else()
                if(TARGET ${arg_PLUGIN_TARGET} AND NOT TARGET ${target})
                    # Case 3: plugin != backing target, plugin exists as MODULE, backing target doesn't
                    add_library(${target} STATIC ${arg_SOURCES})
                    target_link_libraries(${arg_PLUGIN_TARGET} PRIVATE ${target})
                endif()
            endif()
        elseif(NOT TARGET ${target})
            # Case 4: QML module without plugin for Qt5. We need to create a
            # dummy to get the info about QML files to install_qml_module().
            add_custom_target(${target})
            set(arg_PLUGIN_TARGET)
        endif()

        # Copy qmldir / QML files to the build dir.
        # Assuming files are not placed in subdirectories.
        configure_file(qmldir qmldir COPYONLY)
        foreach(file IN LISTS arg_QML_FILES)
            configure_file(${file} ${file} COPYONLY)
        endforeach()

        # Save properties for install_qml_module()
        string(REPLACE "." "/" target_path ${arg_URI})
        set_target_properties(${target} PROPERTIES
            QT5_QML_PLUGIN_TARGET "${arg_PLUGIN_TARGET}"
            QT5_QML_TARGET_PATH ${target_path}
            QT5_QML_QMLDIR ${CMAKE_CURRENT_BINARY_DIR}/qmldir
            QT5_QML_FILES "${arg_QML_FILES}"
        )
    endfunction()
endif()

# Installs a QML module created with qt_add_qml_module()
function(install_qml_module target)
    cmake_parse_arguments(PARSE_ARGV 1 arg "" "DESTINATION" "")

    if(QT_VERSION_MAJOR EQUAL 5)
        get_target_property(plugin_target ${target} QT5_QML_PLUGIN_TARGET)
        get_target_property(target_path ${target} QT5_QML_TARGET_PATH)
        get_target_property(qmldir ${target} QT5_QML_QMLDIR)
        get_target_property(qml_files ${target} QT5_QML_FILES)
        set(typeinfo)
    else()
        qt_query_qml_module(${target}
            PLUGIN_TARGET plugin_target
            TARGET_PATH target_path
            QMLDIR qmldir
            TYPEINFO typeinfo
        )
        set(qml_files)
    endif()

    set(install_dir "${arg_DESTINATION}/${target_path}")
    if(plugin_target)
        install(TARGETS ${plugin_target} DESTINATION "${install_dir}")
    endif()
    install(FILES ${qmldir} ${typeinfo} ${qml_files} DESTINATION "${install_dir}")
endfunction()
