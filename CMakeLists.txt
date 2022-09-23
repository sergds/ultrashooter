cmake_minimum_required(VERSION 3.10)
project(ultrashooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
set(RAYLIB_VERSION 4.2.0)
find_package(Threads REQUIRED)
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
    set(DSUPPORT_FILEFORMAT_TGA ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_QOI ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_FLAC ON CACHE BOOL "" FORCE)
    set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "" FORCE)
    set(OPENGL_VERSION "2.1" CACHE STRING "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
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

add_executable(ultrashooter WIN32 ${ultrashooter_SOURCES} ultrashooter.rc)
target_link_options(ultrashooter PRIVATE -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
target_include_directories(ultrashooter PRIVATE ${ultrashooter_INCLUDE_DIRS})
target_include_directories(ultrashooter PRIVATE third_party/enet/include)
target_link_libraries(ultrashooter raylib)
target_link_libraries(ultrashooter Threads::Threads)
if(WIN32)
  target_link_libraries(ultrashooter wsock32 ws2_32)
endif()
file(COPY data DESTINATION .)