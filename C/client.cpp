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
#include "aes/aes.h"
using namespace std;
#define PORT 50000 /*F Port d'ecoute de la socket serveur */ 
#define MAXSTRING 100 /* Longeur des messages */ 
#define DEBUG 0 // set 0 or 1
int taille( char* ta);
void sendmsg( int sock , char * val);
void recevmsg(int sock);

char msgServeur[MAXSTRING];
uint8_t key[] = { 0x61, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                      0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };
 
int main() 
{ 
 int hSocket; /* Handle de la socket */ 
 struct hostent * infosHost; /*Infos sur le host : pour gethostbyname */ 
 struct in_addr adresseIP; /* Adresse Internet au format reseau */ 
 struct sockaddr_in adresseSocket; /* Structure de type sockaddr - ici, cas de TCP */ 
 unsigned int tailleSockaddr_in; 
 int ret , id_du_vac; /* valeur de retour */ 
 char msgClient[MAXSTRING] , msgClientTmp[MAXSTRING], tokenDeCon[MAXSTRING]  , id_vac[5] ; 
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
//mycode
tokenDeCon[0] = '\0';
while (tokenDeCon[0] == '\0' || tokenDeCon[0] == 'E' ){
   printf("------------------\n");
   printf("Bonjour \n");
   printf("pseudo ?\n");
   cin >> pseudo ; 
   printf("password ? \n");
   cin >> pass ;
   strcpy(msgClientTmp,"\0");
   strcat(msgClientTmp,"con:");
   strcat(msgClientTmp,pseudo);
   strcat(msgClientTmp,"@");
   strcat(msgClientTmp,pass);

   sendmsg(hSocket,msgClientTmp);
   recevmsg(hSocket);


   printf("*%s\n",msgServeur);
   strcpy(tokenDeCon,msgServeur);  
   if(DEBUG)
    printf("nv val de token -%s-",tokenDeCon);

} 


memset(msgClient,0,sizeof(msgClient));
memset(msgClientTmp,0,sizeof(msgClient));
///////////////////// part 2(when connected)
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

         sendmsg(hSocket,msgClient);
         
         recevmsg(hSocket);
         
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
         sendmsg(hSocket,msgClient);

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
         sendmsg(hSocket,msgClient);
         
         recevmsg(hSocket);

         memset(msgClient,'\0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@md"); 
         strcat(msgClient,id_vac);
         printf("inserer la date de naissance du vacancier :\n");
         cin >> tmpsend ;
         strcat(msgClient,tmpsend);
         strcat(msgClient,"\0");
         sendmsg(hSocket,msgClient);
         
         recevmsg(hSocket);
         memset(msgClient,'\0',sizeof(msgClient));
         strcpy(msgClient,"tok:");
         strcat(msgClient,tokenDeCon);
         strcat(msgClient,"@me"); 
         strcat(msgClient,id_vac);
         printf("inserer la presence ou non du vac  :\n");
         cin >> tmpsend ;
         strcat(msgClient,tmpsend);
         strcat(msgClient,"\0");
         sendmsg(hSocket,msgClient);
         
         recevmsg(hSocket);


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
         printf("-> p : prenom\n") ; 
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
         sendmsg(hSocket,msgClient);
         
         recevmsg(hSocket);
         printf("Well done\n" );
         break;
      case 'J' :
         printf("You are on cheatmode or not\n" );
         break;
   }

 }

///////////////////////////////////////////////

    /* 9. Fermeture de la socket */ 
 close(hSocket); /* Fermeture de la socket */ 
 printf("Socket client fermee\n"); 
 return 0; 
} 

///////////////////////////////////////////////////////////
int taille( char* ta){
   int taille = 0 ;
   while (ta[taille] != '\0') {
      taille++;
   }
   return taille ;
}
/////////////////////////////////////////////////////////////   
void sendmsg( int sock , char * val){
   
   struct AES_ctx ctx;
   AES_init_ctx(&ctx, key);

   char valTmp[MAXSTRING];
   uint8_t crypt [MAXSTRING];
   memcpy(crypt,val, MAXSTRING);
   AES_ECB_encrypt(&ctx, crypt);
   memcpy(val,crypt, MAXSTRING);
   int nbraenv = taille(val);
   snprintf(valTmp, 6, "%4d", nbraenv);
   strcat(valTmp,val);
   
    if (send(sock, valTmp, 4+nbraenv, 0) == -1)  {
            printf("Erreur sur le send de la socket %d\n", errno); 
            close(sock); /* Fermeture de la socket */ 
            exit(1);
         }
 //  printf("val envoyer chiffré :%s \n",valTmp);
}
/////////////////////////////////////////////////////////////  
void recevmsg(int hSocket){
  // printf("hey tu recois un msg \n ");
   char val[MAXSTRING];
   uint8_t crypt [MAXSTRING];
   int nbrtoread ;
   struct AES_ctx ctx;
   AES_init_ctx(&ctx, key);
   memset(val,'\0',sizeof(val));
   if (recv(hSocket, val, 4, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         }
   //printf("-> %s",val);
   nbrtoread = atoi(val);
    if (recv(hSocket, val, nbrtoread, 0) == -1) { 
            printf("Erreur sur le recv de la socket %d\n", errno); 
            close(hSocket); /* Fermeture de la socket */ 
            exit(1); 
         }
  memcpy(crypt,val, MAXSTRING);
  AES_ECB_decrypt(&ctx,crypt); 
  memcpy(val,crypt, MAXSTRING);
 // printf("envoie resaux  : %s \n",val);
  memset(msgServeur,'\0',sizeof(msgServeur));
  strcpy(msgServeur,val);
}
/////////////////////////////////////////////////////////////