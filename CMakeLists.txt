cmake_minimum_required(VERSION 3.10)
project(ultrashooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
set(RAYLIB_VERSION 4.2.0)
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
  find_package(Threads QUIET)
endif()

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
    set(SUPPORT_EVENTS_WAITING OFF CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_GIF ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_TGA ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_QOI ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_FLAC ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_FNT ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_TTF ON CACHE BOOL "" FORCE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
      set(PLATFORM "Web" CACHE STRING "" FORCE)
    endif()
    if(CMAKE_SYSTEM_NAME STREQUAL "Android")
      set(PLATFORM "Android" CACHE STRING "" FORCE)
    endif()
    #set(OPENGL_VERSION "2.1" CACHE STRING "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(ENET_VERSION 1.3.17)
find_package(Threads REQUIRED)
find_package(enet ${ENET_VERSION} QUIET) # QUIET or REQUIRED
if (NOT enet_FOUND) # If there's none, fetch and build enet
  include(FetchContent)
  FetchContent_Declare(
    enet
    URL https://github.com/lsalzman/enet/archive/refs/tags/v${ENET_VERSION}.tar.gz
  )
  FetchContent_GetProperties(enet)
  if (NOT enet_POPULATED) # Have we downloaded enet yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(enet)
    add_subdirectory(${enet_SOURCE_DIR} ${enet_BINARY_DIR})
  endif()
endif()

file (GLOB_RECURSE ultrashooter_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE ultrashooter_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (ultrashooter_INCLUDE_DIRS "")
foreach (_headerFile ${ultrashooter_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND ultrashooter_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES ultrashooter_INCLUDE_DIRS)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
  add_executable(ultrashooter WIN32 ${ultrashooter_SOURCES} ultrashooter.rc)
else()
  add_library(ultrashooter SHARED ${ultrashooter_SOURCES})
endif()
target_include_directories(ultrashooter PRIVATE ${ultrashooter_INCLUDE_DIRS})
target_include_directories(ultrashooter PRIVATE ${enet_SOURCE_DIR}/include)
target_link_libraries(ultrashooter raylib)
target_link_libraries(ultrashooter enet)
target_link_libraries(ultrashooter Threads::Threads)
if(MINGW OR UNIX AND NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_link_options(ultrashooter PRIVATE -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
endif()
if(WIN32)
  target_link_libraries(ultrashooter winmm ws2_32)
endif()
file(COPY data DESTINATION .)

# Web Configurations
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()