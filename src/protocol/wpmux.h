/*********************************************************************************
*     File Name           :     src/protocol/wpmux.h
*     Created By          :     jonesax
*     Creation Date       :     [2016-06-01 17:40]
*     Last Modified       :     [2016-06-07 10:46]
*     Description         :      
**********************************************************************************/
#ifndef __WPMUX_H__
#define __WPMUX_H__
#include <jnxc_headers/jnx_tcp_socket.h>
#include <jnxc_headers/jnx_stack.h>
#include "wpprotocol.h"
#include "wpmessage.pb-c.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef enum wp_mux_state {
  E_WMS_OKAY,
  E_WMS_OKAY_EMPTY,
  E_WMS_FAIL
}wp_mux_state;

//This gives the user a functor for controlling how the message is sent
//E.g. routing system and IP addressing is user handled
typedef void (*wpprotocol_emit_message_hook)(Wpmessage *message, 
    void *optional_emit_args);

typedef struct wp_mux {
  jnx_tcp_listener *listener;
  jnx_stack *out_queue;
  jnx_stack *in_queue;
  wpprotocol_emit_message_hook emit_hook;
  void *optional_emit_args;
}wp_mux;

wp_mux *wpprotocol_mux_create(jnx_char *port, jnx_uint8 family,
    wpprotocol_emit_message_hook hook, void *optional_emit_args);

void wpprotocol_mux_tick(wp_mux *mux);

//Once pushed user can free their message memory as a copy is made
wp_mux_state wpprotocol_mux_push(wp_mux *mux,Wpmessage *inmsg);
//When a message is popped the user will be responsibie for memory
wp_mux_state wpprotocol_mux_pop(wp_mux *mux, Wpmessage **omsg);

void wpprotocol_mux_destroy(wp_mux **mux);

#ifdef __cplusplus
}
#endif
#endif
