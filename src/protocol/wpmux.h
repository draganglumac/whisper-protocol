/*********************************************************************************
*     File Name           :     src/protocol/wpmux.h
*     Created By          :     jonesax
*     Creation Date       :     [2016-06-01 17:40]
*     Last Modified       :     [2016-06-01 18:07]
*     Description         :      
**********************************************************************************/
#ifndef __WPMUX_H__
#define __WPMUX_H__
#include <jnxc_headers/jnx_udp_socket.h>
#include <jnxc_headers/jnx_stack.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum wp_mux_state {
  E_WMS_OKAY,
  E_WMS_FAIL
}wp_mux_state;

typedef struct wp_mux {
  jnx_udp_listener *listener;
  
}wp_mux;

wp_mux *wpprotocol_mux_create();

void wpprotocol_mux_tick(wp_mux *mux,void *args);

void wpprotocol_mux_destroy(wp_mux **mux);

#ifdef __cplusplus
}
#endif
#endif
