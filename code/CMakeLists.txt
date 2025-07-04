add_library(precompiled INTERFACE)
target_precompile_headers(precompiled INTERFACE precomp.h)

find_package(FLTK CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    app/App.cpp
    app/App.h
    common/notifier.cpp
    common/notifier.h
    common/property_ids.h
    common/Entity.h
    common/game_map.h
    model/entity_model.cpp
    model/entity_model.h
    model/object.cpp
    model/object.h
    view/MainWindow.cpp
    view/MainWindow.h
    view/widgets/GameWidget.cpp
    view/widgets/GameWidget.h
    view/widgets/GameStateWidget.cpp
    view/widgets/GameStateWidget.h
    view_model/entity_view_model.cpp
    view_model/entity_view_model.h
    view_model/game_view_model.cpp
    view_model/game_view_model.h
    precomp.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fltk
    fltk_forms
    fltk_images
    nlohmann_json::nlohmann_json
    precompiled
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/level1.json
    ${CMAKE_CURRENT_BINARY_DIR}/level1.json
    COPYONLY
)