cmake_minimum_required(VERSION 3.2)
project(Cubicuous)

#Basic flags for CMAKE building
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

#Find all the libraries we need
find_package (OpenGL REQUIRED)

if (NOT WIN32)
  set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
  set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
  find_package (glfw3 REQUIRED)
  find_package (GLM REQUIRED)
  find_package (GLEW REQUIRED STATIC)
endif (NOT WIN32)
if (APPLE)
  include_directories(/usr/local/include)
  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVID_LIBRARY CoreVideo REQUIRED)
endif (APPLE)

#Add the library its self
add_library(Cubicuous ${SOURCE_FILES}
    src/Debugging/Logger.cpp src/Debugging/Logger.h
    src/Window/Window.cpp src/Window/Window.h
    src/Window/Input.cpp src/Window/Input.h
    src/Core/Scene.h
    src/Core/Entity.cpp src/Core/Entity.h
    src/Core/ILoop.h
    src/Core/Loops/ConstSpeedVarFps.cpp src/Core/Loops/ConstSpeedVarFps.h
    src/Game.cpp src/Game.h
    src/Graphics/Shader.h src/Graphics/ShaderManager.cpp src/Graphics/ShaderManager.h)

#Link the libraries to the exe
target_link_libraries (Cubicuous
          ${GLFW3_LIBRARY}
          ${OPENGL_LIBRARIES}
          ${GLEW_LIBRARY}
          ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY})

if (WIN32)
  target_link_libraries (Cubicuous
          ${OPENGL_LIBRARIES} glew32 glfw3 opengl32)
endif (WIN32)
if (UNIX AND NOT APPLE)
  target_link_libraries (Cubicuous
          ${OPENGL_LIBRARIES}
          ${GLFW3_LIBRARY}
          ${GLEW_LIBRARY}
          Xxf86vm pthread Xrandr Xinerama Xi Xcursor)
endif (UNIX AND NOT APPLE)

if (APPLE)
target_link_libraries (Cubicuous
          ${OPENGL_LIBRARIES}
          ${GLFW3_LIBRARY}
          ${GLEW_LIBRARY})
endif (APPLE)

#Test targets
add_executable(WindowTest test/Window/main.cpp)
target_link_libraries(WindowTest Cubicuous)

add_executable(GameTest test/Game/main.cpp)
target_link_libraries(GameTest Cubicuous)