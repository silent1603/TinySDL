get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(PROJECT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_PATH}/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS ${PROJECT_PATH}/*.hpp)

source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SOURCES})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_HEADERS})

add_executable(${ProjectId} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set_property(TARGET ${ProjectId} PROPERTY CXX_STANDARD 11)

target_include_directories(${ProjectId} PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(${ProjectId} PRIVATE ${STB_INCLUDE_DIRS}) 

target_link_libraries(${ProjectId} PRIVATE SDL2::SDL2 SDL2::SDL2main 
                                        PRIVATE asio asio::asio 
                                        PRIVATE box2d::box2d 
                                        PRIVATE Catch2::Catch2  
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
  target_link_libraries(${ProjectId} PRIVATE SDL2::SDL2-static Catch2::Catch2WithMain)
  # target_link_libraries(${ProjectId} PRIVATE X11 X11-xcb Xext xcb xkbcommon )
endif()

set_target_properties(${ProjectId} PROPERTIES 
           ARCHIVE_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           LIBRARY_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           RUNTIME_OUTPUT_DIRECTORY "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_PATH}" 
)
