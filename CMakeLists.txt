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
    src/Core/Exception.h
    src/Window/Exception.h
    src/Window/Window.cpp src/Window/Window.h
    src/Window/Input.cpp src/Window/Input.h
    src/Core/MatrixManager/IMatrixManager.h
    src/GameSettings.cpp src/GameSettings.h
    src/Game.cpp src/Game.h
    src/Core/Scene.cpp src/Core/Scene.h
    src/Core/Entity.h
    src/Core/Loops/ILoop.h
    src/Core/Loops/ConstSpeedVarFps.cpp src/Core/Loops/ConstSpeedVarFps.h
    src/Graphics/ShaderProgram.cpp src/Graphics/ShaderProgram.h
    src/Graphics/VertexBuffer.h
    src/Graphics/Exception.h
    src/Graphics/VertexArray.h
    src/Graphics/Uniform.h
    src/Core/Camera.cpp src/Core/Camera.h
    src/Core/Movable.cpp src/Core/Movable.h src/Core/Entity.cpp
    src/Core/Structure/Voxel.h src/Graphics/Renderable.h
    src/Core/Structure/Structure.cpp src/Core/Structure/Structure.h
    src/Core/MatrixManager/MVPMatrixManager.cpp src/Core/MatrixManager/MVPMatrixManager.h
    src/Core/MatrixManager/MVPSepMatrixManager.cpp src/Core/MatrixManager/MVPSepMatrixManager.h
    src/Core/Mesher/IMesher.h src/Core/Mesher/MonotoneMesher.cpp
    src/Core/Mesher/MonotoneMesher.h src/Core/Mesher/MeshPart.h src/Core/Mesher/MeshPart.cpp
    src/Core/GeometryManager.h src/Core/GeometryManager.cpp
    src/Graphics/Renderer/IRenderer.h src/Graphics/Renderer/ColorRenderer.cpp src/Graphics/Renderer/ColorRenderer.h)

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

add_executable(GameTest test/Game/main.cpp test/Game/TestScene.cpp test/Game/TestScene.h test/Game/CubeEntity.h)
target_link_libraries(GameTest Cubicuous)