file(GLOB PROJECT_SOURCES ${PROJECT_DIR}/src/*.cpp)
include_directories(${PROJECT_DIR}/include)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DENGINE_BUILD_SHARED)
