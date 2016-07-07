/*********************************************************************************
 *     File Name           :     /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-10 14:38]
 *     Last Modified       :     [2016-06-09 16:17]
 *     Description         :      
 **********************************************************************************/

#include "wpprotocol.h"
#include <jnxc_headers/jnx_check.h>
#include <jnxc_headers/jnx_guid.h>
#include <jnxc_headers/jnx_log.h>

wp_generation_state wpprotocol_generate_message(Wpmessage **omessage,
    jnx_char *message_id, jnx_char *sender,jnx_char *recipient,
    void *data, jnx_size len, SelectedAction action) {
  JNXCHECK(sender);
  JNXCHECK(recipient);
   JNXLOG(LDEBUG,"wpprotocol_generate_message...");
  if(sender == NULL || recipient == NULL) {
    return E_WGS_FAIL;
  }
  //Context data
  Wpcontextdata d = WPCONTEXTDATA__INIT;
  if(data) {
    d.has_rawdata = 1;
    d.rawdata.data = malloc(len);
    bzero(d.rawdata.data,len);
    memcpy(d.rawdata.data,data,len);
    d.rawdata.len = len;
  }else {
    d.has_rawdata = 0;
  }
   JNXLOG(LDEBUG,"Generated context data...");
  //Action
  Wpaction a = WPACTION__INIT;
  a.contextdata = &d;
  a.action = action;
  JNXLOG(LDEBUG,"Generated action...");
  //Message
  Wpmessage m = WPMESSAGE__INIT;
  m.action = &a;
  jnx_guid g;
  int l = strlen(message_id);
  m.id = malloc(l + 1);
  bzero(m.id,l+1);
  memcpy(m.id,message_id,l);
  JNXLOG(LDEBUG,"Generated message...");
  //sender 
  l = strlen(sender);
  m.sender = malloc(l + 1);
  bzero(m.sender,l+1);
  memcpy(m.sender,sender,l);
  JNXLOG(LDEBUG,"Generated sender %s",m.sender);
  //recipient
  len = strlen(recipient);
  m.recipient = malloc(l + 1);
  bzero(m.recipient, l+1);
  memcpy(m.recipient,recipient,l);
  JNXLOG(LDEBUG,"Generated recipient %s", m.recipient);

  jnx_size s = wpmessage__get_packed_size(&m);
  jnx_char *buffer = malloc(s);
  jnx_size ps = wpmessage__pack(&m,buffer);
  JNXLOG(LDEBUG,"Packing message...");
  if(!buffer) {
    return E_WGS_FAIL;
  }
  Wpmessage *output = wpmessage__unpack(NULL,ps,buffer);
  JNXLOG(LDEBUG,"Unpacking message...");
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

  // I know this is dumb, but as of yet I've not found a way to initialise a protobuf object on the heap
  // Without it getting packed
  Wpmessage *output = wpmessage__unpack(NULL,ps,buffer);
  free(buffer);
  *outmsg = output;
  return E_WGS_OKAY;
}
