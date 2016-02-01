/*********************************************************************************
 *     File Name           :     test/test_objects.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-17 13:15]
 *     Last Modified       :     [2016-02-01 08:58]
 *     Description         :      
 **********************************************************************************/
#include "wpprotocol.h"
#include "wpmessage.pb-c.h"
#include <jnxc_headers/jnxcheck.h>

Wpmessage* test_message_create(Wpaction *action) {
  Wpmessage *message;
  wp_state w = wpprotocol_generate_message(&message,"001","002", action);
  JNXCHECK(w == E_WP_OKAY);

  JNXCHECK(message->sender); 
  JNXCHECK(message->recipient); 

  return message;
}
Wpaction* test_action_create(Wpcontextdata *contextdata) {
  Wpaction *action;
  wp_state w = wpprotocol_generate_action(&action,contextdata,
      SELECTED_ACTION__CREATE_SESSION);

  return action;
}
Wpcontextdata *test_context_data() {
  Wpcontextdata *data;

  char *testdata = malloc(strlen("Hello"));
  bzero(testdata,6);
  memcpy(testdata,"Hello",6);

  wp_state w = wpprotocol_generate_contextdata(&data,testdata,
      6);

  return data;
}
int main(int argc, char **argv) {

  Wpcontextdata *context = test_context_data();

  Wpaction *action = test_action_create(context);

  Wpmessage *message = test_message_create(action);


  return 0;
}
