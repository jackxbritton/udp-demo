# udp-demo

UDP sockets are great for streaming lots of order-independent data quickly. They have lower overhead than TCP sockets, and that's mostly because they don't do any connection management / keepalive stuff / arrival guarantees that TCP does. Applications include video streaming, audio streaming, and games. I like games so I'm going to try to write something like that.

## Roadmap

### Distinguish packets as belonging to new or returning users.

I'll need a buffer of user info and a way to tell who a packet belongs to.

### Set up a heartbeat.

TCP handles timeouts on it's own. I'll need to implement a 'heartbeat', that is, pinging users and timing their responses, so the server doesn't end up with a bunch of dead users.

### Stream arbitrary data to clients.

This means keeping track of those connections, packing data into a buffer, and having the client receive it without issue.

### SDL2 / OpenGL on the client, clientside prediction and lag compensation.. who knows?!?

It'll be fun. I'll have a blast.
