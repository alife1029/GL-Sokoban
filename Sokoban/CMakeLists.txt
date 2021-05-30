file(GLOB PROJECT_SOURCES ${PROJECT_DIR}/*cpp)
include_directories(${ENGINE_DIR}/include)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} Engine)
