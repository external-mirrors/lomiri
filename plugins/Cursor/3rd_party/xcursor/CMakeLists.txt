add_library(xcursorloader-static STATIC xcursor.c)

target_include_directories(xcursorloader-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(xcursorloader-static PRIVATE _DEFAULT_SOURCE=1)
