cmake_minimum_required(VERSION 3.11)

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
    
add_executable(TinySDL tinysdl/src/main.cpp)

add_subdirectory(tinysdl)

set_property(TARGET TinySDL PROPERTY CXX_STANDARD 11)

target_include_directories(TinySDL PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(TinySDL PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static 
                                        PRIVATE asio asio::asio 
                                        PRIVATE box2d::box2d 
                                        PRIVATE Catch2::Catch2 Catch2::Catch2WithMain 
                                        PRIVATE EnTT::EnTT 
                                        PRIVATE glad::glad
                                        PRIVATE imgui::imgui 
                                        PRIVATE imguizmo::imguizmo 
                                        PRIVATE nlohmann_json
                                        PRIVATE SDL2::SDL2_image 
                                        PRIVATE SDL2::SDL2_mixer 
                                        PRIVATE SDL2::SDL2_ttf 
                                        PRIVATE spdlog::spdlog 
                                        PRIVATE glm::glm 
                                        PRIVATE ${LUA_LIBRARIES}  
)

if (MSVC)
    # warning level 4 and all warnings as errors
    
elseif(UNIX AND NOT APPLE)
  target_link_libraries(TinySDL PRIVATE X11 X11-xcb Xext xcb xkbcommon)
endif()