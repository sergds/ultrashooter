cmake_minimum_required(VERSION 3.10)
project(ultrashooter LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

#========== Add CPM package manager =================
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
set(CPM_VERSION 0.34.3)

if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
   message(STATUS "Downloading CPM.cmake")
   file(DOWNLOAD
https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_VERSION}/CPM.cmake
${CPM_DOWNLOAD_LOCATION})
endif(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
include(${CPM_DOWNLOAD_LOCATION}) 

#========== Newer CPM Deps =================
CPMAddPackage(
        NAME WolfSSL
        GITHUB_REPOSITORY wolfSSL/wolfssl
        GIT_TAG v5.3.0-stable # Latest WolfSSL Didn't built using CMake
        OPTIONS
        "WOLFSSL_OPENSSLEXTRA ON"
        "BUILD_SHARED_LIBS OFF"
        "WOLFSSL_EXAMPLES OFF"
        "WOLFSSL_CRYPT_TESTS OFF"
        "WOLFSSL_SP_MATH_ALL OFF" # SP Math doesn't build with CMake currently...
)
#if (WolfSSL_ADDED)
#    set(WolfSSL_INCLUDE_DIR "${WolfSSL_SOURCE_DIR}/wolfssl")
#    #target_include_directories(WolfSSL INTERFACE ${WolfSSL_INCLUDE_DIR})
#    #target_include_directories(WolfSSL INTERFACE ${WolfSSL_INCLUDE_DIR})
#endif() 

#CPMAddPackage(
#        NAME openssl-cmake
#        GITHUB_REPOSITORY janbar/openssl-cmake
#        GIT_TAG master
#        OPTIONS
#        "WITH_APPS OFF"
#)
#if (openssl-cmake_ADDED)
#    set(OPENSSL_INCLUDE_DIR "${openssl-cmake_BINARY_DIR}/include")
#    target_include_directories(ssl INTERFACE ${OPENSSL_INCLUDE_DIR})
#    target_include_directories(crypto INTERFACE ${OPENSSL_INCLUDE_DIR})
#endif() 
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
CPMAddPackage(
        NAME curl
        VERSION 7.67.0
        URL https://github.com/curl/curl/releases/download/curl-7_67_0/curl-7.67.0.tar.gz
        OPTIONS
        "CMAKE_USE_LIBSSH2 OFF"
        "BUILD_CURL_EXE OFF"
        "BUILD_SHARED_LIBS OFF"
        "HTTP_ONLY ON"
        "BUILD_TESTING OFF"
        "CURL_ENABLE_SSL ON"
        "CURL_USE_WOLFSSL OFF"
        "ZLIB_FOUND OFF"
        "USE_ZLIB OFF"
        "CURL_USE_OPENSSL OFF"
        "CMAKE_USE_OPENSSL OFF"
        "CURL_DISABLE_TESTS ON"
        "WolfSSL_INCLUDE_DIRS" ${WolfSSL_INCLUDE_DIR}
        "WolfSSL_LIBRARIES" WolfSSL
) 
endif()
CPMAddPackage(
  NAME nlohmann_json
  VERSION 3.11.2
  URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.2.zip
  OPTIONS
    "JSON_BuildTests OFF"
)

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
  add_compile_options("-DANDROID -DPLATFORM_ANDROID -D__ANDROID_API__=29")
  add_link_options("-Wall -Wa,--noexecstack -Wformat -Werror=format-security -no-canonical-prefixes")
  set_source_files_properties(${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c PROPERTIES LANGUAGE C)
  add_library(ultrashooter SHARED ${ultrashooter_SOURCES} ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
  find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              log-lib

              # Specifies the name of the NDK library that
              # CMake needs to locate.
              log )

endif()
# You need to link static libraries against your shared native library.
# Web Configurations
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    add_link_options("--preload-file ${CMAKE_SOURCE_DIR}/data")
    add_link_options("-s USE_GLFW=3 -s ASYNCIFY -s USE_PTHREADS=1 -s EXPORTED_RUNTIME_METHODS=ccall  ")
endif()
target_link_libraries(ultrashooter ${log-lib} )
target_include_directories(ultrashooter PRIVATE ${ultrashooter_INCLUDE_DIRS})
target_include_directories(ultrashooter PRIVATE ${enet_SOURCE_DIR}/include)
target_link_libraries(ultrashooter raylib)
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
target_link_libraries(ultrashooter enet)
target_link_libraries(ultrashooter wolfssl)
target_link_libraries(ultrashooter libcurl)
endif()
target_link_libraries(ultrashooter Threads::Threads)
target_link_libraries(ultrashooter nlohmann_json)
execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
if(GIT_HASH)
  target_compile_definitions(ultrashooter PUBLIC GITHASH=${GIT_HASH})
endif()

if(MINGW OR UNIX AND NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_link_options(ultrashooter PRIVATE -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
endif()
if(WIN32)
  target_link_libraries(ultrashooter winmm ws2_32)
endif()
file(COPY data DESTINATION .)

#if( supported )
    #message(STATUS "IPO / LTO enabled")
    #set_property(TARGET ultrashooter PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#else()
#    message(STATUS "IPO / LTO not supported: <${error}>")
#endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()