project(CGCenter)

INCLUDE_DIRECTORIES( BEFORE
  src/3rdparty
  src/3rdparty/imgui/include
  src/3rdparty/glew/include
  src/app
  src/runtime
  src/runtime/ui
  src/runtime/geometry
  src/runtime/light
  src/runtime/renderpass
)

SET(BASE_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(GLEW_LIBRARY_PATH "${BASE_LIBRARY_PATH}/glew/Release/x64")
    SET(GLFW_LIBRARY_PATH "${BASE_LIBRARY_PATH}/glfw/x64")
    SET(ASSIMP_LIBRARY_PATH "${BASE_LIBRARY_PATH}/assimp/x64")
else()
    SET(GLEW_LIBRARY_PATH "${BASE_LIBRARY_PATH}/glew/Release/Win32")
    SET(GLFW_LIBRARY_PATH "${BASE_LIBRARY_PATH}/glfw/x86")
    SET(ASSIMP_LIBRARY_PATH "${BASE_LIBRARY_PATH}/assimp/x86")
endif()
LINK_DIRECTORIES("${GLEW_LIBRARY_PATH}")
LINK_DIRECTORIES("${GLFW_LIBRARY_PATH}")
LINK_DIRECTORIES("${ASSIMP_LIBRARY_PATH}")
link_libraries("opengl32.lib" "glew32.lib" "glfw3.lib" "assimp-vc142-mt.lib" "IrrXML.lib" "zlibstatic.lib")


file(GLOB SOURCE
    ./src/3rdparty/imgui/src/*.cpp
    ./src/app/*.cpp
    ./src/runtime/*.cpp
    ./src/runtime/light/*.cpp
    ./src/runtime/renderpass/*.cpp
    ./src/runtime/geometry/*.cpp
    ./src/runtime/ui/*.cpp
)

file(GLOB HEADERS
    ./src/3rdparty/imgui/src/*.h
    ./src/app/*.h
    ./src/runtime/*.h
    ./src/runtime/light/*.h
    ./src/runtime/renderpass/*.h
    ./src/runtime/geometry/*.h
    ./src/runtime/ui/*.h
)
SET(EXECUTABLE_OUTPUT_PATH ./build)
add_executable(CGCenter ${SOURCE} ${HEADERS})