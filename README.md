# whisper-protocol

`Depends on jnxlibc`

A self contained google protobuf protocol for whisper-core.
Uses the principle of a mux to control push/pull from queues.

- Main benefits are that controlling the network via multiplexing we can run it on a single thread
- Queues abstract the network layer from the user
- No awkward awaiting either end of the TCP channel

Example of messaging below:

```C
wp_mux *m = NULL;


void my_custom_emitter(Wpmessage *message,void *custom_emitter_args) {

 jnx_size osize;
 jnx_char *obuffer;
 wp_generation_state e = wpprotocol_generate_message_string(message,
     &obuffer,&osize); 

  //send the string buffer of data via some means...
  send_data("192.168.1.68","8080",obuffer,osize);

}


void example() {
  m = wpprotocol_mux_create(TESTPORT,AF_INET,my_custom_emitter,NULL);

  //generate some message and push it into the queues
  Wpmessage *outmessage = generated_message();

  wpprotocol_mux_push(m,outmessage);

  while(;;) { 
    wpprotocol_mux_tick(m);
  
    //read anything on the incoming queue
    Wpmessage *message;
    wpprotocol_mux_pop(m,&message);
    if(message) {
    
    }
  
    sleep(500);
  }

  wpprotocol_mux_destroy(&m);
} 

```
