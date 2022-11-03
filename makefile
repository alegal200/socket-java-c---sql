all: clear rm client server
#test

#remove compile project
rm : 
	rm client
	rm server
#clear console
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