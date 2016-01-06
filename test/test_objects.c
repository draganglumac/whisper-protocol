/*********************************************************************************
 *     File Name           :     test/test_objects.c
 *     Created By          :     anon
 *     Creation Date       :     [2015-12-17 13:15]
 *     Last Modified       :     [2016-01-06 15:31]
 *     Description         :      
 **********************************************************************************/
#include "wpprotocol.h"
#include "wpmessage.pb-c.h"
#include <jnxc_headers/jnxcheck.h>

void test_message_create() {
  Wpmessage *message;
  wp_state w = wpprotocol_generate_message(&message,"001","002");
  JNXCHECK(w == E_WP_OKAY);

  JNXCHECK(message->sender); 
  JNXCHECK(message->recipient); 

}
int main(int argc, char **argv) {
  test_message_create();


  return 0;
}
