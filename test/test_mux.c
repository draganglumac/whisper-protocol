/*********************************************************************************
 *     File Name           :     test/test_objects.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-17 13:15]
 *     Last Modified       :     [2016-06-02 14:50]
 *     Description         :      
 **********************************************************************************/
#include "wpprotocol.h"
#include "wpmux.h"
#include "wpmessage.pb-c.h"
#include <jnxc_headers/jnx_check.h>
#include <jnxc_headers/jnx_log.h>
#define TESTPORT "9092"

Wpmessage *generate_message() {
  jnx_char *message;
  jnx_size *osize;
  jnx_char *data = malloc(strlen("Hello"));
  bzero(data,6);
  memcpy(data,"Hello",6);
  wp_generation_state w = wpprotocol_generate_message_proto(&message,&osize,"001","002",
      data,6,SELECTED_ACTION__CREATE_SESSION);

  free(data);
  JNXCHECK(w == E_WGS_OKAY);
  JNXCHECK(message);
  Wpmessage *output = wpmessage__unpack(NULL,osize,message);
  Wpaction *a = output->action;
  Wpcontextdata *contextdata = a->contextdata;

  JNXCHECK(contextdata->has_rawdata);
  if(contextdata->has_rawdata) {
    printf("lenth of value: %d\n", contextdata->rawdata.len);
    printf("content: %s\n", contextdata->rawdata.data);
  }

  return output;
}
static int has_emitted = 0;
void test_mux_cb(Wpmessage *message) {
  JNXLOG(LDEBUG,"Emitting message...");
  has_emitted = 1;
}
void test_mux_create() {
  
  wp_mux *m = wpprotocol_mux_create(TESTPORT,AF_INET,test_mux_cb);
  JNXCHECK(m);
  wpprotocol_mux_destroy(&m);
}
void test_mux_tick() {
  wp_mux *m = wpprotocol_mux_create(TESTPORT,AF_INET,test_mux_cb);
  JNXCHECK(m);
  JNXLOG(LDEBUG,"Ticking..."); 
  wpprotocol_mux_tick(m); 
  JNXCHECK(m->out_queue->count == 0); 
  JNXCHECK(m->in_queue->count == 0); 
  wpprotocol_mux_destroy(&m);
}
void test_mux_outqueue() {

  wp_mux *m = wpprotocol_mux_create(TESTPORT,AF_INET,test_mux_cb);

  Wpmessage *om = generate_message();
  jnx_stack_push(m->out_queue,om);
  JNXCHECK(m);
  JNXLOG(LDEBUG,"Ticking..."); 
  wpprotocol_mux_tick(m); 
  om = NULL;
  wpprotocol_mux_pop(m,&om);
  wpmessage__free_unpacked(om,NULL);
  JNXCHECK(m->out_queue->count == 0); 
  JNXCHECK(m->in_queue->count == 0); 
  wpprotocol_mux_destroy(&m);
}
void test_inqueue() {
  wp_mux *m = wpprotocol_mux_create(TESTPORT,AF_INET,test_mux_cb);

  Wpmessage *om = generate_message();
  jnx_stack_push(m->out_queue,om);
  JNXCHECK(m);
  
  Wpmessage *d = generate_message();
  
  wpprotocol_mux_push(m,d);
  JNXLOG(LDEBUG,"Ticking..."); 
  wpprotocol_mux_tick(m); 
  
  JNXCHECK(has_emitted == 1); 
  wpmessage__free_unpacked(om,NULL);
  wpprotocol_mux_destroy(&m);

}
int main(int argc, char **argv) {

  test_mux_create();
  test_mux_tick();
  test_mux_outqueue();
  test_inqueue();
  return 0;
}
