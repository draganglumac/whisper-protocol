/*********************************************************************************
 *     File Name           :     /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-10 14:38]
 *     Last Modified       :     [2016-02-01 08:54]
 *     Description         :      
 **********************************************************************************/

#include "wpprotocol.h"
#include <jnxc_headers/jnxcheck.h>
#include <jnxc_headers/jnxguid.h>
#include <jnxc_headers/jnxlog.h>

wp_state wpprotocol_generate_message(Wpmessage **message, char *sender, 
    char *recipient) {
  if(sender == NULL || recipient == NULL) {
    return E_WP_FAIL;
  }
  Wpmessage m = WPMESSAGE__INIT;
  *message = &m;
  jnx_guid g;
  jnx_guid_create(&g);
  char *idstr;
  jnx_guid_to_string(&g, &idstr);
  int len = strlen(idstr);
  (*message)->id = malloc(len + 1);
  memcpy((*message)->id,idstr,len);

  len = strlen(sender);
  (*message)->sender = malloc(len + 1);
  memcpy((*message)->sender,sender,len);

  len = strlen(recipient);
  (*message)->recipient = malloc(len + 1);
  memcpy((*message)->recipient,recipient,len);

  free(idstr);

  return E_WP_OKAY;
} 
wp_state wpprotocol_generate_action(Wpaction **action,
    Wpcontextdata *data, SelectedAction saction) {
  Wpaction a = WPACTION__INIT;


  *action = &a;
  (*action)->action = saction; //TODO: might need to alloc this
  (*action)->contextdata = data;
  return E_WP_OKAY;
}
wp_state wpprotocol_generate_contextdata(Wpcontextdata **context, void *data,jnx_size len) {
  Wpcontextdata c = WPCONTEXTDATA__INIT;
  *context = &c;
  
  if(data) {
    (*context)->has_rawdata = 1;
    (*context)->rawdata.data = malloc(sizeof(len));
    memcpy((*context)->rawdata.data,data,len);
    (*context)->rawdata.len = len;
  }

  return E_WP_OKAY;
}
