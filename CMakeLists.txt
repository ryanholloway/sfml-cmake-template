cmake_minimum_required(VERSION 3.16)

set(projectExecutableName "SfmlTemplate" CACHE STRING "Executable/project name (override with -DprojectExecutableName=MyApp)")

project(${projectExecutableName} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Fetch SFML 3.0.0 from GitHub
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(sfml)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect sources from src/
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${projectExecutableName} ${PROJECT_SOURCES})

# Link required SFML components (graphics, window, system)
target_link_libraries(${projectExecutableName} PRIVATE sfml-graphics sfml-window sfml-system)

# Ensure assets are copied to build dir after build - support multi-config generators
if (EXISTS "${CMAKE_SOURCE_DIR}/assets")
  add_custom_command(TARGET ${projectExecutableName} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${projectExecutableName}>/assets"
    COMMAND ${CMAKE_COMMAND} -E echo "Copying assets -> $<TARGET_FILE_DIR:${projectExecutableName}>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_SOURCE_DIR}/assets"
      "$<TARGET_FILE_DIR:${projectExecutableName}>/assets"
    COMMENT "Copying assets to output directory"
  )
else()
  message(WARNING "Assets directory '${CMAKE_SOURCE_DIR}/assets' not found; skipping copy step.")
endif()