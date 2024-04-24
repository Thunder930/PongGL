# CMakeLists.txt for main project

# Set main project name
set(PROJECT_NAME Pong)

# Minimum required CMake version
cmake_minimum_required(VERSION 3.0)

# Project name and languages
project(${PROJECT_NAME} LANGUAGES C CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C standard to C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Find OpenGL library
find_package(OpenGL REQUIRED)

# Add GLFW and GLEW subdirectories
add_subdirectory(external/glfw)
add_subdirectory(external/glew/build/cmake)

# Disable unnecessary GLFW build components
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Set output directories for GLFW
set_target_properties(glfw PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# GLEW header and source files
file(GLOB_RECURSE GLEW_HEADER_FILES "external/glew/include/*.h")
file(GLOB_RECURSE GLEW_SOURCE_FILES "external/glew/src/*.c")

# Project header and source files
file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

# Organize header files in a virtual "Header Files" folder
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER_FILES})

# Link GLFW libraries
target_include_directories(${PROJECT_NAME} PRIVATE external/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES})

# Link GLEW libraries
target_include_directories(${PROJECT_NAME} PRIVATE external/glew/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glew_s)

# Organize GLEW targets in their own folder
set_target_properties(glew PROPERTIES FOLDER "GLEW")
set_target_properties(glew_s PROPERTIES FOLDER "GLEW")
set_target_properties(glewinfo PROPERTIES FOLDER "GLEW")
set_target_properties(visualinfo PROPERTIES FOLDER "GLEW")

# Link OpenGL libraries
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY})

# Set the main project as the startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
