/*********************************************************************************
*     File Name           :     /home/jonesax/Work/whisper-protocol/src/protocol/wpmux.c
*     Created By          :     jonesax
*     Creation Date       :     [2016-06-01 17:45]
*     Last Modified       :     [2016-06-01 20:55]
*     Description         :      
**********************************************************************************/

#include "wpmux.h"
#include <jnxc_headers/jnx_check.h>
#include <stdlib.h>

wp_mux *wpprotocol_mux_create() {
  wp_mux *mux = malloc(sizeof(wp_mux));
  mux->listener = jnx_socket_udp_listener_create("9090",AF_INET);
  JNXCHECK(mux);
  return mux;
}
void wp_protocol_mux_message_processor(const jnx_uint8 *payload,
    jnx_size bytes_read, void *args) {

}
void wpprotocol_mux_tick(wp_mux *mux,void *args) {
  jnx_socket_udp_listener_tick(mux->listener,wp_protocol_mux_message_processor,
      args);
}
void wpprotocol_mux_destroy(wp_mux **mux) {
  JNXCHECK(*mux);
  jnx_socket_udp_listener_destroy(&(*mux)->listener);
  free(*mux);
}
