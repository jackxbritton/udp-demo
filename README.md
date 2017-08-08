# udp-demo

UDP sockets are great for streaming lots of order-independent data quickly. They have lower overhead than TCP sockets, and that's mostly because they don't do any of the connection management / keepalive stuff / arrival guarantees that TCP does. Applications include video streaming, audio streaming, and games.
