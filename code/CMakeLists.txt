# 预编译头
add_library(precompiled INTERFACE)
target_precompile_headers(precompiled INTERFACE precomp.h)

# 核心逻辑库
add_library(core_logic STATIC
    common/notifier.cpp
    model/entity_model.cpp
    model/object.cpp
)
target_include_directories(core_logic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(core_logic PUBLIC nlohmann_json::nlohmann_json)


# 主程序可执行文件
add_executable(${PROJECT_NAME}
    main.cpp
    app/App.cpp
    view/MainWindow.cpp
    view/widgets/GameWidget.cpp
    view/widgets/GameStateWidget.cpp
    view_model/entity_view_model.cpp
    view_model/game_view_model.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
# 修正: 使用 vcpkg 提示的全小写 fltk 目标
target_link_libraries(${PROJECT_NAME} PRIVATE
    core_logic
    fltk
    fltk_forms
    fltk_images
    precompiled
)


# 配置文件
configure_file(
    model/level1.json
    ${CMAKE_BINARY_DIR}/level1.json
    COPYONLY
)


# # --- 测试部分 ---
# enable_testing()

# add_executable(level_devil_tests
#     tests/entity_model_test.cpp
# )

# # 修正: 使用 vcpkg 输出中提示的 GTest::gtest 和 GTest::gtest_main 目标
# target_link_libraries(level_devil_tests PRIVATE
#     core_logic
#     GTest::gtest
#     GTest::gtest_main
# )

# add_test(NAME level_devil_tests COMMAND level_devil_tests)