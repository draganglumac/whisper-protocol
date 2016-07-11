cmake_minimum_required(VERSION 2.8)
set(INSTALL_PREFIX /usr)
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
set(jnxlibc_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/jnxlibc_install_files")
set(jnxlibc_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${jnxlibc_INSTALL_DIR} -DIGNORE_VERSION=1)

ExternalProject_Add(jnxlibc-project
  PREFIX ${jnxlibc_PREFIX}
  GIT_REPOSITORY https://github.com/AlexsJones/jnxlibc.git
  INSTALL_DIR ${jnxlibc_INSTALL_DIR}
  CMAKE_ARGS ${jnxlibc_CMAKE_ARGS}
  BUILD_COMMAND make
  )

file(MAKE_DIRECTORY whisper_protocol_headers)
file(COPY ${HEADERS} DESTINATION whisper_protocol_headers)

add_definitions("-fPIC")

add_library(whisper-protocol STATIC ${SOURCE})
add_library(whisper-protocols SHARED ${SOURCE})

include_directories(${install_dir}/include/jnxc_headers)

target_link_libraries(whisper-protocol  ${LINKER_LIBRARIES} jnxc)
target_link_libraries(whisper-protocols  ${LINKER_LIBRARIES} jnxcs)

install(TARGETS whisper-protocol DESTINATION ${INSTALL_PREFIX}/lib)
install(TARGETS whisper-protocols DESTINATION ${INSTALL_PREFIX}/lib)
install(DIRECTORY whisper_protocol_headers DESTINATION ${INSTALL_PREFIX}/include)
