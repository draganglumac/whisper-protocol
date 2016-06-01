/*********************************************************************************
 *     File Name           :     src/protocol/wpprotocol.h
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-10 14:36]
 *     Last Modified       :     [2016-06-01 20:54]
 *     Description         :      
 **********************************************************************************/

#ifndef __WPPROTOCOL_H__
#define __WPPROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <jnxc_headers/jnx_types.h>
#include "wpmessage.pb-c.h"
typedef enum wp_message_state {
  E_WMS_OKAY,
  E_WMS_FAIL,
  E_WMS_UNKNOWN
}wp_message_state;

typedef enum data_type {
  E_DT_ASYMKEY,
  E_DT_SYMKEY,
  E_DT_CHAR,
  E_DT_INT
}data_type;


wp_message_state wpprotocol_generate_message_proto(jnx_char **obuffer, jnx_size *osize,
    char *sender,char *recipient,
    void *data, jnx_size len, SelectedAction action);

#ifdef __cplusplus
}
#endif
#endif
