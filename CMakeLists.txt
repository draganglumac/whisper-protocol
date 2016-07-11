cmake_minimum_required(VERSION 2.8)
include(ExternalProject)
project(whisper-protocol)
set(CMAKE_C_FLAGS "-std=c99")
execute_process(COMMAND ./tools/generate_protobuf)
set(SOURCE "")
set(HEADERS "")
add_subdirectory(src/obj)
add_subdirectory(src/protocol)
include_directories(${PROJECT_INC_DIR}src/obj)
include_directories(${PROJECT_INC_DIR}src/protocol)

set(jnxlibc_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/jnxlibc")
set(jnxlibc_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
set(jnxlibc_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${jnxlibc_INSTALL_DIR} -DIGNORE_VERSION=1)

ExternalProject_Add(jnxlibc-project
  PREFIX ${jnxlibc_PREFIX}
  GIT_REPOSITORY https://github.com/AlexsJones/jnxlibc.git
  INSTALL_DIR ${jnxlibc_INSTALL_DIR}
  CMAKE_ARGS ${jnxlibc_CMAKE_ARGS}
  BUILD_COMMAND make
  INSTALL_COMMAND sudo make install
  )

file(MAKE_DIRECTORY whisper_protocol_headers)
file(COPY ${HEADERS} DESTINATION whisper_protocol_headers)

add_definitions("-fPIC")

add_library(jnxlibc SHARED IMPORTED)
add_library(jnxlibcs STATIC IMPORTED)

set_property(TARGET jnxlibc PROPERTY IMPORTED_LOCATION ${jnxlibc_INSTALL_DIR}/lib/libjnxc.so)
set_property(TARGET jnxlibcs PROPERTY IMPORTED_LOCATION ${jnxlibc_INSTALL_DIR}/lib/libjnxcs.a)

add_library(whisper-protocol SHARED ${SOURCE})
add_library(whisper-protocols STATIC ${SOURCE})

add_dependencies(whisper-protocol jnxlibc-project)

target_link_libraries(whisper-protocol  ${LINKER_LIBRARIES} jnxlibc)
target_link_libraries(whisper-protocols  ${LINKER_LIBRARIES} jnxlibcs)

install(TARGETS whisper-protocol DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS whisper-protocols DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY whisper_protocol_headers DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
