cmake_minimum_required(VERSION 2.8)
set(INSTALL_PREFIX /usr)
project(whisper-protocol)

execute_process(COMMAND git submodule init)
execute_process(COMMAND git submodule update)
execute_process(COMMAND cmake . WORKING_DIRECTORY jnxlibc)
execute_process(COMMAND make . WORKING_DIRECTORY jnxlibc)
execute_process(COMMAND sudo make install . WORKING_DIRECTORY jnxlibc)
execute_process(COMMAND ./tools/generate_protobuf)

set(SOURCE "")
set(HEADERS "")

add_subdirectory(src/obj)
add_subdirectory(src/protocol)

include_directories(${PROJECT_INC_DIR}src/obj)
include_directories(${PROJECT_INC_DIR}src/protocol)

file(MAKE_DIRECTORY whisper_protocol_headers)
file(COPY ${HEADERS} DESTINATION whisper_protocol_headers)

add_library(whisper_protocol STATIC ${SOURCE})
add_library(whisper_protocols SHARED ${SOURCE})

target_link_libraries(whisper_protocol ${LINKER_LIBRARIES})
target_link_libraries(whisper_protocols ${LINKER_LIBRARIES})

install(TARGETS whisper_protocol DESTINATION ${INSTALL_PREFIX}/lib)
install(TARGETS whisper_protocols DESTINATION ${INSTALL_PREFIX}/lib)
install(DIRECTORY whisper_protocol_headers DESTINATION ${INSTALL_PREFIX}/include)
