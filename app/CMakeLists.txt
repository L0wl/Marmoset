cmake_minimum_required(VERSION 3.30)
project(MarmosetBridgeApp)

add_executable(MarmosetBridgeApp
    main.cpp
    cmd/CommandlineParser.cpp
)

target_link_libraries(MarmosetBridgeApp PUBLIC -static)
target_link_libraries(MarmosetBridgeApp PUBLIC MarmosetCore)
set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    target_compile_options(MarmosetBridgeApp PRIVATE /MD)
endif ()

add_custom_command(TARGET MarmosetBridgeApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:MarmosetCore> $<TARGET_FILE_DIR:MarmosetBridgeApp>
)