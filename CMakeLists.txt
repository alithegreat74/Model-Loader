cmake_minimum_required(VERSION 3.5.0)

project(ModelLoader)

set(Thirdparty_Dir "${CMAKE_SOURCE_DIR}/Thirdparty")
set(Source_Dir "${CMAKE_SOURCE_DIR}/src")
#Getting the source files
file(GLOB_RECURSE SRC_FILES "${Source_Dir}/*.cpp")

include_directories(
	"${Thirdparty_Dir}/Glad/include"
	"${Source_Dir}"
)


# Add GLFW as a subdirectory
add_subdirectory("${Thirdparty_Dir}/GLFW")
add_subdirectory("${Thirdparty_Dir}/GLM")
# Create the executable
add_executable(ModelLoader "${Thirdparty_Dir}/Glad/src/glad.c" ${SRC_FILES} main.cpp)

# Link GLFW library
target_link_libraries(ModelLoader PRIVATE glm glfw ${CMAKE_DL_LIBS})

