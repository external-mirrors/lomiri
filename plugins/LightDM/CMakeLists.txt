set(QMLPLUGIN_SRC
    ../Utils/lomirisortfilterproxymodelqml.cpp
    DBusGreeter.cpp
    DBusGreeterList.cpp
    Greeter.cpp
    plugin.cpp
    PromptsModel.cpp
    SessionsModel.cpp
    UsersModel.cpp
)

add_subdirectory(FullLightDM)
add_subdirectory(IntegratedLightDM)
