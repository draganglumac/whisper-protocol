/*********************************************************************************
 *     File Name           :     src/protocol/wpprotocol.h
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-10 14:36]
 *     Last Modified       :     [2016-06-09 13:39]
 *     Description         :      
 **********************************************************************************/

#ifndef __WPPROTOCOL_H__
#define __WPPROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <jnxc_headers/jnx_types.h>
#include "wpmessage.pb-c.h"
typedef enum wp_generation_state {
  E_WGS_OKAY,
  E_WGS_FAIL,
  E_WGS_UNKNOWN
}wp_generation_state;

typedef enum data_type {
  E_DT_ASYMKEY,
  E_DT_SYMKEY,
  E_DT_CHAR,
  E_DT_INT
}data_type;


wp_generation_state wpprotocol_generate_message(Wpmessage **omsg,
    jnx_char *message_id, jnx_char *sender,jnx_char *recipient,
    void *data, jnx_size len, SelectedAction action);

wp_generation_state wpprotocol_generate_message_string(Wpmessage *msg, 
    jnx_char **obuffer, jnx_size *osize);

wp_generation_state wpprotocol_copy_message(Wpmessage *inmsg, Wpmessage **outmsg);
#ifdef __cplusplus
}
#endif
#endif
