cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

OPTION(DEFINE_DEBUG
  "Build the project using debugging code"
  OFF)
IF(DEFINE_DEBUG)
  MESSAGE("Adding Debug flag...")
  ADD_DEFINITIONS(-DDEFINE_DEBUG)
  #SET(CMAKE_BUILD_TYPE Debug)
  MESSAGE("Build type is " ${CMAKE_BUILD_TYPE})
ENDIF(DEFINE_DEBUG)

set(SHORT_NAME covid19-data)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "covid19-data")
set(VITA_TITLEID  "COVIDDATA")
set(VITA_VERSION  "02.50")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu11 -Wno-narrowing ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wno-narrowing -fpermissive ")

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(BZip2 REQUIRED)

FUNCTION(ADD_RESOURCES out_var)
  SET(result)
  FOREACH(in_f ${ARGN})
  SET(out_f "${CMAKE_CURRENT_BINARY_DIR}/${in_f}.o")
  GET_FILENAME_COMPONENT(out_dir ${out_f} DIRECTORY)
  ADD_CUSTOM_COMMAND(OUTPUT ${out_f}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${out_dir}
    COMMAND ${CMAKE_LINKER} -r -b binary -o ${out_f} ${in_f}
    DEPENDS ${in_f}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building resource ${out_f}"
    VERBATIM
    )
  LIST(APPEND result ${out_f})
  ENDFOREACH()
  SET(${out_var} "${result}" PARENT_SCOPE)
ENDFUNCTION()

file(GLOB res_files RELATIVE
  ${CMAKE_SOURCE_DIR}
  resources/head.bin
)

add_resources(vitashell_res ${res_files})

add_executable(${SHORT_NAME}
    ${vitashell_res}
    src/main.cpp
    src/images.cpp
    src/vita-keyboard.cpp
    src/controls.cpp
    src/curl-tools.cpp
    src/json-tools.cpp
    src/draw.cpp
)

target_link_libraries(${SHORT_NAME}
vita2d
ScePgf_stub
SceGxm_stub
SceCtrl_stub
SceTouch_stub
SceAppUtil_stub
SceDisplay_stub
SceLibKernel_stub
SceSysmodule_stub
SceSysmem_stub
ScePower_stub
SceCommonDialog_stub
SceRegistryMgr_stub
SceHid_stub
freetype
png
jpeg
SceAudio_stub
SceIofilemgr_stub
SceNet_stub
SceNetCtl_stub
SceHttp_stub
SceSsl_stub
SceAppMgr_stub
debugnet
pthread
jansson
${CURL_LIBRARIES}
${CURL_LIBRARIES}
${OPENSSL_LIBRARIES}
zip
ScePromoterUtil_stub
ScePvf_stub
SceIme_stub
ssl
crypto
z
m
c
${BZIP2_LIBRARIES}

)


vita_create_self(${SHORT_NAME}.self ${SHORT_NAME} UNSAFE)

vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}

  FILE font.ttf font.ttf
)