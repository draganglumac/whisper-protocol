/*********************************************************************************
*     File Name           :     src/protocol/wpprotocol.h
*     Created By          :     anon
*     Creation Date       :     [2015-12-10 14:36]
*     Last Modified       :     [2015-12-17 10:12]
*     Description         :      
**********************************************************************************/

#ifndef __WPPROTOCOL_H__
#define __WPPROTOCOL_H__
#include "wpmessage.pb-c.h"
typedef enum wp_state {
  E_WP_OKAY,
  E_WP_FAIL,
  E_WP_UNKNOWN
}wp_state;

typedef enum data_type {
  E_DT_ASYMKEY,
  E_DT_SYMKEY,
  E_DT_CHAR,
  E_DT_INT
}data_type;


wp_state wpprotocol_generate_message(Wpmessage **message, char *sender, 
    char *recipient); 

wp_state wpprotocol_generate_action(Wpaction **action);

wp_state wpprotocol_generate_contextdata(Wpcontextdata **context, void *data, data_type type);
#endif

