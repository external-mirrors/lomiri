add_definitions(-D_DEFAULT_SOURCE=1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

set(
  XCURSOR_SOURCES

  xcursor.c
)

add_library(
  xcursorloader-static STATIC

  ${XCURSOR_SOURCES}
)

target_include_directories(xcursorloader-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
