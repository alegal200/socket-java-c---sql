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
#define DEBUG 1 // set 0 or 1
int main() 
{ 
 int hSocket; /* Handle de la socket */ 
 struct hostent * infosHost; /*Infos sur le host : pour gethostbyname */ 
 struct in_addr adresseIP; /* Adresse Internet au format reseau */ 
 struct sockaddr_in adresseSocket; /* Structure de type sockaddr - ici, cas de TCP */ 
 unsigned int tailleSockaddr_in; 
 int ret , id_du_vac; /* valeur de retour */ 
 char msgClient[MAXSTRING], msgServeur[MAXSTRING] , tokenDeCon[MAXSTRING]  , id_vac[5] ; 
 char choix ;
 char  pseudo[MAXSTRING] ="0", pass[MAXSTRING] ="0" ;  
    /* 1. Création de la socket */ 
 hSocket = socket(AF_INET, SOCK_STREAM, 0); 
 if (hSocket == -1) { 
   if(DEBUG)
    printf("Erreur de creation de la socket %d\n", errno); 
    exit(1); 
 } 
 else {
   if(DEBUG)
   printf("Creation de la socket OK\n"); 
   }
    /* 2. Acquisition des informations sur l'ordinateur distant */ 
 if ( (infosHost = gethostbyname("moon"))==0) { 
   if(DEBUG)
      printf("Erreur d'acquisition d'infos sur le host distant %d\n", errno); 
    exit(1); 
 } 
 else {
   if(DEBUG)
      printf("Acquisition infos host distant OK\n"); 
   }
 memcpy(&adresseIP, infosHost->h_addr, infosHost->h_length);
if(DEBUG)
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
   if(DEBUG)
      printf("Erreur sur connect de la socket %d\n", errno); 
    close(hSocket); 
    exit(1); 
 } 
 else{
   if(DEBUG)
      printf("Connect socket OK\n"); 
 } 
    /* 5.Envoi d'un message client */ 
 strcpy(msgClient,"tentative de connection"); 
 if (send(hSocket, msgClient, MAXSTRING, 0) == -1) /* pas message urgent */ { 
   if(DEBUG)
      printf("Erreur sur le send de la socket %d\n", errno); 
    close(hSocket); /* Fermeture de la socket */ 
    exit(1); 
 } 
 else {
   if(DEBUG)
      printf("Send socket OK\n"); 
   }
if(DEBUG)  
   printf("Message envoye = %s\n", msgClient); 
    /* 6. Reception de l'ACK du serveur au client */ 
 if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
   if(DEBUG)
      printf("Erreur sur le recv de la socket %d\n", errno); 
     close(hSocket); /* Fermeture de la socket */ 
     exit(1); 
 } 
 else {
    if(DEBUG)
      printf("Recv socket OK\n"); 
 }
if(DEBUG){
    printf("Message recu en ACK = %s\n", msgServeur); 
}

while (tokenDeCon[0] == '\0' )
   {
   printf("------------------\n");
   printf("Bonjour \n");
   printf("pseudo ?\n");
   cin >> pseudo ; 
   printf("password ? \n");
   cin >> pass ;
   strcpy(msgClient,"\0");
   strcat(msgClient,"con:");
   strcat(msgClient,pseudo);
   strcat(msgClient,"@");
   strcat(msgClient,pass);
   if(DEBUG)
      printf(" concat str :%s* \n",msgClient);
   // envoie
   
   if (send(hSocket, msgClient, MAXSTRING, 0) == -1) /* pas message urgent */ { 
      printf("Erreur sur le send de la socket %d\n", errno); 
      close(hSocket); /* Fermeture de la socket */ 
      exit(1); 
   } 
   if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
     
     printf("Erreur sur le recv de la socket %d\n", errno); 
     close(hSocket); /* Fermeture de la socket */ 
     exit(1); 
   }
   if(DEBUG)
      printf("le serveur a repondu voici la vlauer du token -%s- et la valeur que le serveur a renvoyer -%s- \n",tokenDeCon , msgServeur); 
   strcpy(tokenDeCon,msgServeur);  
   if(DEBUG)
      printf("nv val de token -%s-",tokenDeCon);

   } 


memset(msgClient,0,sizeof(msgClient));
while (true)
{  
   printf("------------------\n");
   printf("A -> deconnextion \n");
   printf("B -> Créer vacancier \n");
   printf("C -> modifier un vacancier \n");
   printf("------------------\n");
   cin >> choix ; 
    switch(choix) {
      case 'A' :
         printf("Excellent! tu as finis ta session \n" );
         close(hSocket);
         exit(0) ;
         return 0 ;
         break;
      case 'B' :
        
         char tmpsend[30];
         memset(msgServeur,'\0',sizeof(msgServeur));
         memset(msgClient,'0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@creation");
         if (send(hSocket, msgClient, MAXSTRING, 0) == -1)  {  
         printf("Erreur sur le send de la socket %d\n", errno); 
         close(hSocket); /* Fermeture de la socket */ 
         exit(1);
         }
         
         if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         } 
         
         printf("val id %s\n",msgServeur);
         id_du_vac = atoi(msgServeur);
         snprintf(id_vac, 5, "%4d", id_du_vac); 
         memset(msgClient,'\0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@mn"); 
         strcat(msgClient,id_vac);
         printf("inserer le nom du vacancier :\n");
         cin >> tmpsend ;
         strcat(msgClient,tmpsend);
         strcat(msgClient,"\0");
         if (send(hSocket, msgClient, MAXSTRING, 0) == -1)  {
            printf("Erreur sur le send de la socket %d\n", errno); 
            close(hSocket); 
            exit(1);
         }

         if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         } 

         memset(msgClient,'\0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@mp"); 
         strcat(msgClient,id_vac);
         printf("inserer le prenom du vacancier :\n");
         cin >> tmpsend ;
         strcat(msgClient,tmpsend);
         strcat(msgClient,"\0");
         if (send(hSocket, msgClient, MAXSTRING, 0) == -1)  {
            printf("Erreur sur le send de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1);
         }

         if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         } 

         memset(msgClient,'\0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@md"); 
         strcat(msgClient,id_vac);
         printf("inserer la date de naissance du vacancier :\n");
         cin >> tmpsend ;
         strcat(msgClient,tmpsend);
         strcat(msgClient,"\0");
         if (send(hSocket, msgClient, MAXSTRING, 0) == -1)  {
            printf("Erreur sur le send de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1);
         }

         if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         } 

         memset(msgClient,'\0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@me"); 
         strcat(msgClient,id_vac);
         printf("inserer la presence ou non du vac  :\n");
         cin >> tmpsend ;
         strcat(msgClient,tmpsend);
         strcat(msgClient,"\0");
         if (send(hSocket, msgClient, MAXSTRING, 0) == -1)  {
            printf("Erreur sur le send de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1);
         }

         if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         } 


         break;
      case 'C' : 
         char modchoix[1] , tmpsend2[30];
         printf("donner son id \n");
         cin >> id_vac ;
         id_du_vac = atoi(id_vac);
         snprintf(id_vac, 5, "%4d", id_du_vac); 
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         printf("type de modification \n");
         printf("-> n : nom\n") ; 
         printf("-> p : presence\n") ; 
         printf("-> d : date\n") ; 
         printf("-> e : présence\n") ; 
         cin >> modchoix ;
         strcat(msgClient,"@m");
         strcat(msgClient,modchoix);
         strcat(msgClient,id_vac);
         printf("la valeur :\n");
         cin >> tmpsend2 ; 
         strcat(msgClient,tmpsend2);
         strcat(msgClient,"\0");
         printf("le msg envoyer au serv %s",msgClient);
         if (send(hSocket, msgClient, MAXSTRING, 0) == -1)  {
            printf("Erreur sur le send de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1);
         }

         if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         } 

         printf("Well done\n" );
         break;
      case 'D' :
         printf("You passed\n" );
         break;
}

 }



    /* 7.Envoi d'un deuxième message client */ 
if(DEBUG)
   printf("Message a envoyer : ");
   cin >> msgClient ; 
 if (send(hSocket, msgClient, MAXSTRING, 0) == -1) /* pas message urgent */ { 
   if(DEBUG)
      printf("Erreur sur le send de la socket %d\n", errno); 
     close(hSocket); /* Fermeture de la socket */ 
     exit(1); 
 } 
 else{
   if(DEBUG)
      printf("Send socket OK\n");
 }  
if(DEBUG)
   printf("Message envoye = %s\n", msgClient); 
    /* 8. Reception de l'ACK du serveur au client */ 
 if (recv(hSocket, msgServeur, MAXSTRING, 0) == -1) 
 { 
 if(DEBUG)
   printf("Erreur sur le recv de la socket %d\n", errno); 
 close(hSocket); /* Fermeture de la socket */ 
 exit(1); 
 } 
 else{
    if(DEBUG)
    printf("Recv socket OK\n"); 
 } 
if(DEBUG)
   printf("Message recu en ACK = %s\n", msgServeur); 
printf("******************************************* \n");







    /* 9. Fermeture de la socket */ 
 close(hSocket); /* Fermeture de la socket */ 
 printf("Socket client fermee\n"); 
 return 0; 
} 


