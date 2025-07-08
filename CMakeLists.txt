cmake_minimum_required(VERSION 3.14)
project(Moutous)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find SDL2 ---
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# --- Find SDL2_ttf ---
find_library(SDL2_TTF_LIB SDL2_ttf HINTS /usr/lib/x86_64-linux-gnu)
if(NOT SDL2_TTF_LIB)
    message(FATAL_ERROR "SDL2_ttf not found! Run: sudo apt install libsdl2-ttf-dev")
endif()

# --- Source files ---
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(main ${SOURCES})

# --- Includes ---
target_include_directories(main PRIVATE
    includes
    ${SDL2_INCLUDE_DIRS}
    /usr/include/SDL2
)

# --- Link libraries ---
target_link_libraries(main PRIVATE
    ${SDL2_LIBRARIES}
    SDL2main
    ${SDL2_TTF_LIB}
)

# --- Copy misc/ directory (fixed) ---
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:main>/misc
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/misc 
        $<TARGET_FILE_DIR:main>/misc
    COMMENT "Copying misc files..."
)

# Alternative: Uncomment if POST_BUILD fails
file(COPY ${CMAKE_SOURCE_DIR}/misc DESTINATION ${CMAKE_BINARY_DIR})