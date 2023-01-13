all:rm clear client server test
#test envoi  

#remove compile project
rm : 
	rm client
	rm server
#	rm envoi
	rm testing
#clear console
clear : 
	clear 

client : client.cpp ./aes/aes.o
	g++ client.cpp ./aes/aes.o -o client 

server : server.cpp ./aes/aes.o ./sha/sha256.o
	g++ server.cpp ./aes/aes.o ./sha/sha256.o -o server 

envoi: 
	g++ envoi.cpp -o envoi

 test : test.cpp ./sha/sha256.o
	g++ test.cpp ./sha/sha256.o -o testing 

./aes/aes.o : ./aes/aes.c ./aes/aes.h
	g++ ./aes/aes.c -c -o ./aes/aes.o

./sha/sha256.o : ./sha/sha256.c ./sha/sha256.h
	g++ ./sha/sha256.c -c -o ./sha/sha256.o



# TO DO
# sha256
# java - c
# java - c aes 
# html p2 
# html error 
#
#
#