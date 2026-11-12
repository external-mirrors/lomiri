set(
  XCURSOR_SOURCES

  xcursor.c
)

add_library(
  xcursorloader-static STATIC

  ${XCURSOR_SOURCES}
)

target_include_directories(xcursorloader-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(xcursorloader-static PRIVATE _DEFAULT_SOURCE=1)
