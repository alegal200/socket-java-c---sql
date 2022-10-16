all: clear client server
#test
 
clear : 
	clear

client :
	g++ client.cpp -o client 
# 
#-lnsl -lsocket
server : 
	g++ server.cpp -o server 
# 
#-lnsl -lsocket
#
#
# test : 
#	g++ test.cpp -o test