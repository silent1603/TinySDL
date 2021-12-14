cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
CACHE STRING "Vcpkg toolchain file")

project(TinySDL)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
 
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if (MSVC)
  if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg.exe")
  MESSAGE(STATUS "INSTALL VCPKG")
  execute_process(COMMAND "./vcpkg/bootstrap-vcpkg.bat"
  RESULT_VARIABLE CMD_ERROR
  OUTPUT_FILE CMD_OUTPUT)
  MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
  MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})
  endif()
elseif(UNIX)
  if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg")
    MESSAGE(STATUS "INSTALL VCPKG")
    execute_process(COMMAND "./vcpkg/bootstrap-vcpkg.sh"
    RESULT_VARIABLE CMD_ERROR
    OUTPUT_FILE CMD_OUTPUT)
    MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
    MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})
  endif()
endif()

set(RELEASE_PATH "${PROJECT_SOURCE_DIR}/release")
set(DEBUG_PATH "${PROJECT_SOURCE_DIR}/debug")

find_package(SDL2 CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(glm CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")

#message(STATUS ${SDL2_DIR})
#message(STATUS ${asio_DIR})

set(PROJECT_PATH ${CMAKE_SOURCE_DIR}/tinysdl)
set(SRC_PATH ${PROJECT_PATH}/src)
set(SHADER_PATH ${PROJECT_PATH}/shaders)
set(RESOURCE_PATH ${PROJECT_PATH}/resources)

file(GLOB_RECURSE PROJECT_SOURCES ${SRC_PATH}/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS ${SRC_PATH}/*.hpp)
file(GLOB_RECURSE PROJECT_SHADERS ${SHADER_PATH}/*.comp ${SHADER_PATH}/*.frag ${SHADER_PATH}/*.geom ${SHADER_PATH}/*.vert)
file(GLOB_RECURSE PROJECT_RESOURCES ${RESOURCE_PATH}/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt Readme.md .gitattributes .gitignore .gitmodules LICENSE)

add_subdirectory(tinysdl)


source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SHADERS})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SOURCES})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_HEADERS})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_RESOURCES})
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${PROJECT_CONFIGS})

add_executable(TinySDL ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_SHADERS} ${RESOURCE_PATH})

set_property(TARGET TinySDL PROPERTY CXX_STANDARD 11)



target_include_directories(TinySDL PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(TinySDL PRIVATE ${STB_INCLUDE_DIRS}) 

target_link_libraries(TinySDL PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static 
                                        PRIVATE asio asio::asio 
                                        PRIVATE box2d::box2d 
                                        PRIVATE Catch2::Catch2 Catch2::Catch2WithMain 
                                        PRIVATE EnTT::EnTT 
                                        PRIVATE glad::glad
                                        PRIVATE imgui::imgui 
                                        PRIVATE imguizmo::imguizmo 
                                        PRIVATE nlohmann_json nlohmann_json::nlohmann_json
                                        PRIVATE SDL2::SDL2_image 
                                        PRIVATE SDL2::SDL2_mixer 
                                        PRIVATE SDL2::SDL2_ttf 
                                        PRIVATE spdlog::spdlog spdlog::spdlog_header_only 
                                        PRIVATE glm::glm 
                                        PRIVATE ${LUA_LIBRARIES}  
)

if (MSVC)
    
elseif(UNIX AND NOT APPLE)
  target_link_libraries(TinySDL PRIVATE X11 X11-xcb Xext xcb xkbcommon GL udev Xrandr)
endif()

add_custom_command(TARGET TinySDL POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy_directory 
                      ${CMAKE_SOURCE_DIR}/tinysdl/resources ${RELEASE_PATH}/resources 
                    COMMAND ${CMAKE_COMMAND} -E copy_directory 
                      ${CMAKE_SOURCE_DIR}/tinysdl/shaders ${RELEASE_PATH}/shaders
)

set_target_properties(TinySDL PROPERTIES 
           ARCHIVE_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           LIBRARY_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           RUNTIME_OUTPUT_DIRECTORY "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_PATH}" 
)
