add_library(MockAccountsService-qml MODULE
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/Greeter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/PromptsModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/UsersModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
    AccountsService.cpp
    plugin.cpp
    )

target_include_directories(MockAccountsService-qml PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/IntegratedLightDM
    ${CMAKE_SOURCE_DIR}/plugins/Utils
)

target_link_libraries(MockAccountsService-qml PRIVATE
    lomiri-paths
    MockLightDM
    Intl::Intl
    Qt::DBus
    Qt::Qml
)

add_lomiri_mock(AccountsService 0.1 AccountsService
    TARGETS MockAccountsService-qml
    )
