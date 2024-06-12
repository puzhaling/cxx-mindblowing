cmake_minimum_required(VERSION 3.10)
project(Handbook)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Handbook
  src/main.cc 
  src/hashtable.cc 
  src/autodocs.cc
  src/redblacktree.cc
  src/start_window.cc
)

# Specify the output directory for the executable
set_target_properties(Handbook PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Manually specify include and library directories
include_directories("/home/void/fltk-1.3.9/include")
link_directories("/home/void/fltk-1.3.9/lib")

# Specify the FLTK libraries needed
set(FLTK_LIBRARIES fltk fltk_images fltk_forms)

# Link the FLTK libraries to your executable
target_link_libraries(Handbook ${FLTK_LIBRARIES})

# Find and link X11 and related libraries
find_package(X11 REQUIRED)
if (X11_FOUND)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(Handbook ${X11_LIBRARIES})
endif()

# Additional X11 libraries needed by FLTK
target_link_libraries(Handbook Xrender)

# Additional Font Libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(XFT REQUIRED xft)
pkg_check_modules(FONTCONFIG REQUIRED fontconfig)

target_link_libraries(Handbook ${XFT_LIBRARIES} ${FONTCONFIG_LIBRARIES})

# Specify directory containing your header files
include_directories("${PROJECT_SOURCE_DIR}/include")

