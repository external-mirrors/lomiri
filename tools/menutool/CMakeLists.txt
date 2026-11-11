add_executable(menutool
    menutool.cpp
    )

target_link_libraries(menutool PRIVATE lomiri-paths Qt::Qml Qt::Quick)
