CC            = g++
CPPFLAGS        = -Wall -g

PORT          = 5000

SERVER_LFLAGS = -pthread
SERVER_OBJS   = server.o
SERVER_ARGS   = $(PORT)

CLIENT_LFLAGS = -lSDL2 -lGL -lGLEW
CLIENT_OBJS   = client.o
CLIENT_ARGS   = $(PORT)

all : server client

server : $(SERVER_OBJS)
	$(CC) $(SERVER_LFLAGS) $(SERVER_OBJS) -o server

client : $(CLIENT_OBJS)
	$(CC) $(CLIENT_LFLAGS) $(CLIENT_OBJS) -o client

run :
	./server $(SERVER_ARGS) &
	sleep 0.25
	./client $(CLIENT_ARGS)
	$(SHELL fg)

clean :
	rm server client $(SERVER_OBJS) $(CLIENT_OBJS)
