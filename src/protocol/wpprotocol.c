/*********************************************************************************
 *     File Name           :     /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-10 14:38]
 *     Last Modified       :     [2016-06-07 15:09]
 *     Description         :      
 **********************************************************************************/

#include "wpprotocol.h"
#include <jnxc_headers/jnx_check.h>
#include <jnxc_headers/jnx_guid.h>
#include <jnxc_headers/jnx_log.h>

wp_generation_state wpprotocol_generate_message(Wpmessage **omessage,
    char *sender,char *recipient,
    void *data, jnx_size len, SelectedAction action) {
  JNXCHECK(sender);
  JNXCHECK(recipient);
  if(sender == NULL || recipient == NULL) {
    return E_WGS_FAIL;
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
  bzero(m.id,l+1);
  memcpy(m.id,idstr,l);
  //sender 
  l = strlen(sender);
  m.sender = malloc(l + 1);
  bzero(m.sender,l+1);
  memcpy(m.sender,sender,l);
  //recipient
  len = strlen(recipient);
  m.recipient = malloc(l + 1);
  bzero(m.recipient, l+1);
  memcpy(m.recipient,recipient,l);

  free(idstr);
  jnx_size s = wpmessage__get_packed_size(&m);
  jnx_char *buffer = malloc(s);
  jnx_size ps = wpmessage__pack(&m,buffer);
  if(!buffer) {
    return E_WGS_FAIL;
  }
  Wpmessage *output = wpmessage__unpack(NULL,ps,buffer);
  *omessage = output;
  free(buffer);
  return E_WGS_OKAY;
}

wp_generation_state wpprotocol_generate_message_string(Wpmessage *inmsg, 
    jnx_char **obuffer, jnx_size *osize) {

  jnx_size s = wpmessage__get_packed_size(inmsg);
  jnx_char *buffer = malloc(s);
  jnx_size ps = wpmessage__pack(inmsg,buffer);
  if(!buffer) {
    return E_WGS_FAIL;
  }
  *osize = ps;
  *obuffer = buffer;
  return E_WGS_OKAY;
}
wp_generation_state wpprotocol_copy_message(Wpmessage *inmsg, Wpmessage **outmsg) {
  if(!inmsg) {
    return E_WGS_FAIL;
  }
  jnx_size s = wpmessage__get_packed_size(inmsg);
  jnx_char *buffer = malloc(s);
  jnx_size ps = wpmessage__pack(inmsg,buffer);
  if(!buffer) {
    return E_WGS_FAIL;
  }
  Wpmessage *output = wpmessage__unpack(NULL,ps,buffer);
  free(buffer);
  *outmsg = output;
  return E_WGS_OKAY;
}
