add_library(QtMultimedia-qml MODULE
    plugin.cpp
    mediaplayer.cpp
    videooutput.cpp
    declarativeplaylist.cpp
    )

target_link_libraries(QtMultimedia-qml PRIVATE
    lomiri-paths
    Qt::Qml
    Qt::Quick
)

add_lomiri_mock(QtMultimedia 5.0 QtMultimedia TARGETS QtMultimedia-qml)
