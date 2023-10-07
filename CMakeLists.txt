# CMakeList.txt : CMake project for Barbaria, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Barbaria")

include_directories("C:/Program Files/glew/include")
include_directories("C:/Program Files/glfw3/include")
link_directories("C:/Program Files/glfw3/Lib")
link_directories("C:/Program Files/glew/lib/Release/x64")

set(glm_DIR "C:/Program Files/glm/cmake/glm")
find_package(glm REQUIRED)


# Add source to this project's executable.
add_executable (Barbaria "Barbaria.h" "Barbaria.cpp" "Game/Game.cpp" "Game/Game.h" "Game/World/Block.h" "Game/World/Chunk.h" "Game/World/Player.h" "Game/World/World.h" "Game/World/game_textures.h" "Game/World/Block.cpp" "Game/World/Chunk.cpp" "Game/World/Player.cpp" "Game/World/World.cpp" "Game/World/game_textures.cpp" "Game/Controllers/Controller.cpp" "Game/Controllers/fps_controller.cpp" "Game/Controllers/Controller.h" "Game/Controllers/fps_controller.h" "Utils/math_utils.h" "Utils/math_utils.cpp" "Engine/Engine.cpp" "Engine/Engine.h" "Engine/Object/Object.h" "Engine/Object/Texture.h" "Engine/Object/voxel_render.h" "Engine/Object/Object.cpp" "Engine/Object/Texture.cpp" "Engine/Object/voxel_render.cpp" "Engine/Rendering/Camera.h" "Engine/Rendering/Shader.h" "Engine/Rendering/View.h" "Engine/Rendering/Camera.cpp" "Engine/Rendering/Shader.cpp" "Engine/Rendering/View.cpp" "Engine/Window/Input.cpp" "Engine/Window/Window.cpp" "Engine/Window/Input.h" "Engine/Window/Window.h" "Lib/stb_image.h")
target_link_libraries(Barbaria glew32 glfw3 opengl32 glm::glm)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Barbaria PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
