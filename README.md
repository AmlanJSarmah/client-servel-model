# Client Server Model
A basic client server implementation using the TCP/IP protocol. It uses and demonstrates the use of sockets in the C programming language.


### Working
Sockets is an endpoint to a connection, they are widely used in various areas. One of them is in the Internal for things like real time chat apps, games etc. 
They allow inter process communication for two processes running in the same network.

  Server                      Client
    |                            |
socket opt                       |
    |                            |
   bind                          |
    |              <-         connect
  listen                         |  
    |                            |
  accept                         |   
    |                            |
   I/O                          I/O
