/*********************************************************************************
*     File Name           :     /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c
*     Created By          :     anon
*     Creation Date       :     [2015-12-10 14:38]
*     Last Modified       :     [2015-12-17 10:30]
*     Description         :      
**********************************************************************************/

#include "wpprotocol.h"
#include <jnxc_headers/jnxcheck.h>
#include <jnxc_headers/jnxguid.h>
#include <jnxc_headers/jnxlog.h>

wp_state wpprotocol_generate_message(Wpmessage **message, char *sender, 
    char *recipient) {
  JNXCHECK(sender);
  JNXCHECK(recipient);

  wpmessage__init(*message);
 
  jnx_guid g;
  jnx_guid_create(&g);
 
  char *idstr;
  jnx_guid_to_string(&g, &idstr);
  int len = strlen(idstr);
  JNXLOG(LDEBUG,"Creating message identity => %s", idstr);
  (*message)->id = malloc(len + 1);
  memcpy((*message)->id,idstr,len);
  


  free(idstr);

  return E_WP_OKAY;
} 
