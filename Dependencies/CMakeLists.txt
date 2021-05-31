# GLFW
file(GLOB GLFW_LIB_FILES ${DEPENDENCIES_DIR}/GLFW/lib-vc2019/*.lib)
include_directories(${DEPENDENCIES_DIR}/GLFW/include)

# GLAD
file(GLOB GLAD_SOURCES ${DEPENDENCIES_DIR}/glad/src/*.c)
include_directories(${DEPENDENCIES_DIR}/glad/include)

# STB
file(GLOB STB_SOURCES ${DEPENDENCIES_DIR}/stb/stb/*.c)
include_directories(${DEPENDENCIES_DIR}/stb)

# GLM
include_directories(${DEPENDENCIES_DIR}/glm)

set(ALL_LIB_FILES 
    ${GLFW_LIB_FILES}
    )

set(ALL_LIB_SOURCES
    ${GLAD_SOURCES}
    ${STB_SOURCES}
    )
