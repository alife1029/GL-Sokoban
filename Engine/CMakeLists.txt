file(GLOB PROJECT_SOURCES 
    ${PROJECT_DIR}/src/*.cpp
    ${PROJECT_DIR}/src/Application/*.cpp
    ${PROJECT_DIR}/src/Graphics/*.cpp
    )

include_directories(${PROJECT_DIR}/include)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${ALL_LIB_SOURCES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIB_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DENGINE_BUILD_SHARED)

if(MSVC)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/GLShaders/
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/GLShaders/)
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/GLShaders/
                ${CMAKE_CURRENT_BINARY_DIR}/GLShaders/)
endif()
