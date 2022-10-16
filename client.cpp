/* TCPCLI01.C 
* client * 
- Claude Vilvens - 

//////////////////////////////
        PAGE  50-51-52 
/////////////////////////////

*/ 
#include <stdio.h> 
#include <stdlib.h> /* pour exit */ 
#include <string.h> /* pour memcpy */ 
#include <sys/types.h> 
#include <sys/socket.h> /* pour les types de socket */ 
#include <netdb.h> /* pour la structure hostent */ 
#include <errno.h> 
#include <netinet/in.h> /* conversions adresse reseau->format dot et local/ reseau */ 
#include <netinet/tcp.h> /* pour la conversion adresse reseau->format dot */ 
#include <arpa/inet.h> /* pour la conversion adresse reseau->format dot */ 
#include <unistd.h>
#include <iostream>
using namespace std;
#define PORT 50000 /*F Port d'ecoute de la socket serveur */ 
#define MAXSTRING 100 /* Longeur des messages */ 
int main() 
{ 
 int hSocket; /* Handle de la socket */ 
 struct hostent * infosHost; /*Infos sur le host : pour gethostbyname */ 
 struct in_addr adresseIP; /* Adresse Internet au format reseau */ 
 struct sockaddr_in adresseSocket; /* Structure de type sockaddr - ici, cas de TCP */ 
 unsigned int tailleSockaddr_in; 
 int ret; /* valeur de retour */ 
 char msgClient[MAXSTRING], msgServeur[MAXSTRING]; 
    /* 1. Création de la socket */ 
 hSocket = socket(AF_INET, SOCK_STREAM, 0); 
 if (hSocket == -1) { 
    printf("Erreur de creation de la socket %d\n", errno); 
    exit(1); 
 } 
 else printf("Creation de la socket OK\n"); 
    /* 2. Acquisition des informations sur l'ordinateur distant */ 
 if ( (infosHost = gethostbyname("moon"))==0) { 
    printf("Erreur d'acquisition d'infos sur le host distant %d\n", errno); 
    exit(1); 
 } 
 else printf("Acquisition infos host distant OK\n"); 
 memcpy(&adresseIP, infosHost->h_addr, infosHost->h_length);
 printf("Adresse IP = %s\n",inet_ntoa(adresseIP)); 
    /* 3. Préparation de la structure sockaddr_in */ 
 memset(&adresseSocket, 0, sizeof(struct sockaddr_in)); 
 adresseSocket.sin_family = AF_INET; /* Domaine */
 adresseSocket.sin_port = htons(PORT); 
    /* conversion numéro de port au format réseau */ 
 memcpy(&adresseSocket.sin_addr, infosHost->h_addr,infosHost->h_length); 
    /* 4. Tentative de connexion */ 
 tailleSockaddr_in = sizeof(struct sockaddr_in); 
 if (( ret = connect(hSocket, (struct sockaddr *)&adresseSocket, tailleSockaddr_in) )  == -1) { 
    printf("Erreur sur connect de la socket %d\n", errno); 
    close(hSocket); 
    exit(1); 
 } 
 else printf("Connect socket OK\n"); 
    /* 5.Envoi d'un message client */ 
 strcpy(msgClient,"Bonjour ! Nous nous connaissons ?"); 
 if (send(hSocket, msgClient, MAXSTRING, 0) == -1) /* pas message urgent */ { 
    printf("Erreur sur le send de la socket %d\n", errno); 
    close(hSocket); /* Fermeture de la socket */ 
    exit(1); 
 } 
 else printf("Send socket OK\n"); 
 printf("Message envoye = %s\n", msgClient); 
    /* 6. Reception de l'ACK du serveur au client */ 
 if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
     printf("Erreur sur le recv de la socket %d\n", errno); 
     close(hSocket); /* Fermeture de la socket */ 
     exit(1); 
 } 
 else printf("Recv socket OK\n"); 
 printf("Message recu en ACK = %s\n", msgServeur); 
    /* 7.Envoi d'un deuxième message client */ 
 printf("Message a envoyer : ");
   cin >> msgClient ; 
 if (send(hSocket, msgClient, MAXSTRING, 0) == -1) /* pas message urgent */ { 
     printf("Erreur sur le send de la socket %d\n", errno); 
     close(hSocket); /* Fermeture de la socket */ 
     exit(1); 
 } 
 else printf("Send socket OK\n"); 
 printf("Message envoye = %s\n", msgClient); 
    /* 8. Reception de l'ACK du serveur au client */ 
 if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) 
 { 
 printf("Erreur sur le recv de la socket %d\n", errno); 
 close(hSocket); /* Fermeture de la socket */ 
 exit(1); 
 } 
 else printf("Recv socket OK\n"); 
 printf("Message recu en ACK = %s\n", msgServeur); 
    /* 9. Fermeture de la socket */ 
 close(hSocket); /* Fermeture de la socket */ 
 printf("Socket client fermee\n"); 
 return 0; 
} 


