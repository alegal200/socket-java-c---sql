all:  clear rm client server envoi test

#remove compile project
rm : 
	rm client
	rm server
#	rm envoi
#	rm test
#clear console
clear : 
	clear 

client : client.cpp ./aes/aes.o
	g++ client.cpp ./aes/aes.o -o client 
# 
#-lnsl -lsocket
server : server.cpp ./aes/aes.o
	g++ server.cpp ./aes/aes.o -o server 
# 
#-lnsl -lsocket
#
envoi: 
	g++ envoi.cpp -o envoi
#
 test : test.cpp ./aes/aes.o
	g++ test.cpp ./aes/aes.o -o test 

./aes/aes.o : ./aes/aes.c ./aes/aes.h
	g++ ./aes/aes.c -c -o ./aes/aes.o