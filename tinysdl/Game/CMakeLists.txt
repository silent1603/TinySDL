Project(Game)

set(PROJECT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Pong")

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_PATH}/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS ${PROJECT_PATH}/*.hpp)

source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SOURCES})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_HEADERS})

add_executable(Game ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set_property(TARGET Game PROPERTY CXX_STANDARD 11)

target_include_directories(Game PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(Game PRIVATE ${STB_INCLUDE_DIRS}) 

target_link_libraries(Game PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static 
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
  target_link_libraries(Game PRIVATE X11 X11-xcb Xext xcb xkbcommon)
endif()

set_target_properties(Game PROPERTIES 
           ARCHIVE_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           LIBRARY_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           RUNTIME_OUTPUT_DIRECTORY "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_PATH}" 
)