/*********************************************************************************
*     File Name           :     src/protocol/wpmux.h
*     Created By          :     jonesax
*     Creation Date       :     [2016-06-01 17:40]
*     Last Modified       :     [2016-06-01 21:30]
*     Description         :      
**********************************************************************************/
#ifndef __WPMUX_H__
#define __WPMUX_H__
#include <jnxc_headers/jnx_udp_socket.h>
#include <jnxc_headers/jnx_stack.h>
#include "wpmessage.pb-c.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef enum wp_mux_state {
  E_WMS_OKAY,
  E_WMS_OKAY_EMPTY,
  E_WMS_FAIL
}wp_mux_state;

typedef struct wp_mux {
  jnx_udp_listener *listener;
  jnx_stack *out_queue;
  jnx_stack *in_queue;
}wp_mux;

wp_mux *wpprotocol_mux_create();

void wpprotocol_mux_tick(wp_mux *mux,void *args);

wp_mux_state wpprotocol_mux_push(wp_mux *mux,Wpmessage *inmsg);

wp_mux_state wpprotocol_mux_pop(wp_mux *mux, Wpmessage **omsg);

void wpprotocol_mux_destroy(wp_mux **mux);

#ifdef __cplusplus
}
#endif
#endif
