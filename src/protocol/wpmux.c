/*********************************************************************************
 *     File Name           :     /home/jonesax/Work/whisper-protocol/src/protocol/wpmux.c
 *     Created By          :     jonesax
 *     Creation Date       :     [2016-06-01 17:45]
 *     Last Modified       :     [2016-06-07 10:34]
 *     Description         :      
 **********************************************************************************/

#include "wpmux.h"
#include <jnxc_headers/jnx_check.h>
#include <jnxc_headers/jnx_log.h>
#include <stdlib.h>

wp_mux *wpprotocol_mux_create(jnx_char *port, jnx_uint8 family,
    wpprotocol_emit_message_hook hook) {
  wp_mux *mux = malloc(sizeof(wp_mux));
  mux->listener = jnx_socket_tcp_listener_create(port,family,100);
  mux->out_queue = jnx_stack_create();
  mux->in_queue = jnx_stack_create();
  if(hook)
    mux->emit_hook = hook;
  JNXCHECK(mux);

  return mux;
}
void wp_protocol_mux_message_processor(const jnx_uint8 *payload,
    jnx_size bytes_read, int connected_socket, void *args) {
  wp_mux *mux = (wp_mux*)args;
  JNXLOG(LDEBUG,"Attempting to unpack incoming message...");
  Wpmessage *msg = wpmessage__unpack(NULL,bytes_read,payload);
  if(msg) {
    jnx_stack_push(mux->out_queue,msg);
  }else {
    JNXLOG(LDEBUG,"Malformed input message, discarding...");
  }
}
void wpprotocol_mux_tick(wp_mux *mux) {
  jnx_socket_tcp_listener_tick(mux->listener,wp_protocol_mux_message_processor,
      mux);
  if(mux->emit_hook) {
    if(!jnx_stack_is_empty(mux->in_queue)) {
      Wpmessage *msg = jnx_stack_pop(mux->in_queue);
      //emit one message
      mux->emit_hook(msg);
    } 
  } 
  JNXLOG(LDEBUG,"Tick"); 
}
void wpprotocol_mux_destroy(wp_mux **mux) {
  JNXCHECK(*mux);
  jnx_socket_tcp_listener_destroy(&(*mux)->listener);
  //Remove incoming messages
  Wpmessage *o;
  while(!(E_WMS_OKAY_EMPTY == wpprotocol_mux_pop(*mux,&o))) {
    if(o == NULL) {
      break;
    }
    wpmessage__free_unpacked(o,NULL);
  }
  //Remove outgoing messages
  while(!jnx_stack_is_empty((*mux)->out_queue)) {
    o = jnx_stack_pop((*mux)->out_queue);
    wpmessage__free_unpacked(o,NULL);
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

  Wpmessage *deepcopy = NULL;
  wpprotocol_copy_message(inmsg,&deepcopy);
  if(!deepcopy) {
    JNXLOG(LERROR,"Copy message failed!");
    return E_WMS_FAIL;
  }

  jnx_stack_push(mux->in_queue, deepcopy); 
  return E_WMS_OKAY;
}
wp_mux_state wpprotocol_mux_pop(wp_mux *mux, Wpmessage **omsg) {

  if(!jnx_stack_is_empty(mux->out_queue)) {
    Wpmessage *msg = jnx_stack_pop(mux->out_queue);
    if(!msg) {
      JNXLOG(LWARN,"No message to pop");
      return E_WMS_FAIL;
    }
    *omsg = msg;
    return E_WMS_OKAY;
  }
  JNXLOG(LWARN,"Message out queue empty");
  return E_WMS_OKAY_EMPTY;
}
