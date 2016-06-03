# whisper-protocol

A self contained google protobuf protocol for whisper-core.
Uses the principle of a mux to control push/pull from queues.

- Main benefits are that controlling the network via multiplexing we can run it on a single thread
- Queues abstract the network layer from the user
- No awkward awaiting either end of the TCP channel

Example of messaging below:

```C
wp_mux *m = NULL;


void some_callback_for_user_on_message(Wpmessage *message) {

  //maybe send a reply?
  if(m) {
    Wpmessage *d = generate_message();
    wpprotocol_mux_push(m,d);
  }
}


void example() {
  m = wpprotocol_mux_create(TESTPORT,AF_INET,some_callback_for_user_on_message);

  while(;;) { 
    wpprotocol_mux_tick(m); 
  }

  wpprotocol_mux_destroy(&m);
} 

```
