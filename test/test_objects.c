/*********************************************************************************
 *     File Name           :     test/test_objects.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-17 13:15]
 *     Last Modified       :     [2016-06-09 13:40]
 *     Description         :      
 **********************************************************************************/
#include "wpprotocol.h"
#include "wpmessage.pb-c.h"
#include <jnxc_headers/jnx_check.h>

void test_message_create() {
  Wpmessage *message;

  jnx_size *osize;

  jnx_char *data = malloc(strlen("hello"));
  bzero(data,6);
  memcpy(data,"Hello",6);
  wp_generation_state w = wpprotocol_generate_message(&message,"00000000000001",
      "001","002",
      data,6,SELECTED_ACTION__CREATE_SESSION);

  free(data);

  JNXCHECK(message);

  Wpmessage *output = message;
  Wpaction *a = output->action;
  Wpcontextdata *contextdata = a->contextdata;

  JNXCHECK(contextdata->has_rawdata);
  if(contextdata->has_rawdata) {
    printf("lenth of value: %d\n", contextdata->rawdata.len);
    printf("content: %s\n", contextdata->rawdata.data);
  }

  JNXCHECK(strcmp(contextdata->rawdata.data,"Hello") == 0);
  
  wpmessage__free_unpacked(message,NULL);
}

void test_message_copy() {

  Wpmessage *message;

  jnx_size *osize;

  jnx_char *data = malloc(strlen("hello"));
  bzero(data,6);
  memcpy(data,"hello",6);
  wp_generation_state w = wpprotocol_generate_message(&message,"00000000000002",
      "001","002",
      data,6,SELECTED_ACTION__CREATE_SESSION);

  free(data);

  JNXCHECK(message);

  Wpmessage *copied;

  wpprotocol_copy_message(message,&copied);

  JNXCHECK(strcmp(message->action->contextdata->rawdata.data, copied->action->contextdata->rawdata.data) == 0);

  wpmessage__free_unpacked(message,NULL);
  wpmessage__free_unpacked(copied,NULL);

}
int main(int argc, char **argv) {

  test_message_create();
  
  test_message_copy();
  return 0;

}
