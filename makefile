#Compiles the server code
server : finalprojectServer.o

finalprojectServer.o : finalprojectServer.c CaesarCypher.c
	gcc finalprojectServer.c CaesarCypher.c -lws2_32 -o server

#Compiles the client code	
client : finalprojectClient.o

finalprojectClient.o : finalprojectClient.c CaesarCypher.c
	gcc finalprojectClient.c CaesarCypher.c -lws2_32 -o client