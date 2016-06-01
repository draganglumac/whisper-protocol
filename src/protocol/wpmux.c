/*********************************************************************************
*     File Name           :     /home/jonesax/Work/whisper-protocol/src/protocol/wpmux.c
*     Created By          :     jonesax
*     Creation Date       :     [2016-06-01 17:45]
*     Last Modified       :     [2016-06-01 21:36]
*     Description         :      
**********************************************************************************/

#include "wpmux.h"
#include <jnxc_headers/jnx_check.h>
#include <stdlib.h>

wp_mux *wpprotocol_mux_create() {
  wp_mux *mux = malloc(sizeof(wp_mux));
  mux->listener = jnx_socket_udp_listener_create("9090",AF_INET);
  mux->out_queue = jnx_stack_create();
  mux->in_queue = jnx_stack_create();
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

  for(int x=0;x<(*mux)->out_queue->count; ++x) {
 
  }
  for(int x=0;x<(*mux)->in_queue->count; ++x) {
  
  }
  jnx_stack_destroy(&(*mux)->out_queue);
  jnx_stack_destroy(&(*mux)->in_queue);
  free(*mux);
}
wp_mux_state wpprotocol_mux_push(wp_mux *mux,Wpmessage *inmsg) {
  JNXCHECK(mux);
  if(inmsg == NULL) {
    return E_WMS_FAIL;
  }
  jnx_stack_push(mux->in_queue, inmsg); 
  return E_WMS_OKAY;
}
wp_mux_state wpprotocol_mux_pop(wp_mux *mux, Wpmessage **omsg) {
  
  if(!jnx_stack_is_empty(mux->out_queue)) {
    Wpmessage *msg = jnx_stack_pop(mux->out_queue);
    if(!msg) {
      return E_WMS_FAIL;
    }
    *omsg = msg;
    return E_WMS_OKAY;
  }
  return E_WMS_OKAY_EMPTY;
}
