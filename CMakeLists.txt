# Declare the minimum required CMake version

cmake_minimum_required(VERSION 3.24.1)
project(Project1)
set(APPLICATION_LIBRARY SudokuLib)

set(CMAKE_CXX_STANDARD 17)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

set(SOURCE_FILES
    main.cpp
    SudokuApp.cpp
    SudokuApp.h
    pch.h
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

add_subdirectory(Tests)

