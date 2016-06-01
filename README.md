# whisper-protocol

A self contained google protobuf protocol for whisper-core.

Example below

```C
#include "wpprotocol.h"
#include "wpmessage.pb-c.h"
#include <jnxc_headers/jnxcheck.h>

void test_message_create() {
  jnx_char *message;

  jnx_size *osize;

  jnx_char *data = malloc(strlen("Hello"));
  bzero(data,6);
  memcpy(data,"Hello",6);
  wp_state w = wpprotocol_generate_message_proto(&message,&osize,"001","002",
      data,6,SELECTED_ACTION__CREATE_SESSION);

  free(data);
  JNXCHECK(w == E_WP_OKAY);

  JNXCHECK(message);

  Wpmessage *output = wpmessage__unpack(NULL,osize,message);

  Wpaction *a = output->action;

  Wpcontextdata *contextdata = a->contextdata;

  JNXCHECK(contextdata->has_rawdata);
  if(contextdata->has_rawdata) {
    printf("lenth of value: %d\n", contextdata->rawdata.len);
    printf("content: %s\n", contextdata->rawdata.data);
  }

  JNXCHECK(strcmp(contextdata->rawdata.data,"Hello") == 0);
  wpmessage__free_unpacked(output,NULL);
}
int main(int argc, char **argv) {

  test_message_create();

  return 0;
}
```
