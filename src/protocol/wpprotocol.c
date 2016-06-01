/*********************************************************************************
 *     File Name           :     /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-10 14:38]
 *     Last Modified       :     [2016-06-01 20:54]
 *     Description         :      
 **********************************************************************************/

#include "wpprotocol.h"
#include <jnxc_headers/jnx_check.h>
#include <jnxc_headers/jnx_guid.h>
#include <jnxc_headers/jnx_log.h>

wp_message_state wpprotocol_generate_message_proto(jnx_char **obuffer, jnx_size *osize,
    char *sender,char *recipient,
    void *data, jnx_size len, SelectedAction action) {
  JNXCHECK(sender);
  JNXCHECK(recipient);
  if(sender == NULL || recipient == NULL) {
    return E_WMS_FAIL;
  }
  //Context data
  Wpcontextdata d = WPCONTEXTDATA__INIT;
  if(data) {
    d.has_rawdata = 1;
    d.rawdata.data = malloc(sizeof(len));
    memcpy(d.rawdata.data,data,len);
    d.rawdata.len = len;
  }else {
    d.has_rawdata = 0;
  }
  //Action
  Wpaction a = WPACTION__INIT;
  a.contextdata = &d;
  a.action = action;
  //Message
  Wpmessage m = WPMESSAGE__INIT;
  m.action = &a;
  jnx_guid g;
  jnx_guid_create(&g);
  char *idstr;
  jnx_guid_to_string(&g, &idstr);
  int l = strlen(idstr);
  m.id = malloc(l + 1);
  memcpy(m.id,idstr,l);
  //sender 
  l = strlen(sender);
  m.sender = malloc(l + 1);
  memcpy(m.sender,sender,l);
  //recipient
  len = strlen(recipient);
  m.recipient = malloc(l + 1);
  memcpy(m.recipient,recipient,l);

  free(idstr);

  jnx_size s = wpmessage__get_packed_size(&m);

  *obuffer = malloc(s);
  jnx_size ps = wpmessage__pack(&m,*obuffer);
  if(!*obuffer) {
    return E_WMS_FAIL;
  }
  *osize = ps;

  return E_WMS_OKAY;
}
