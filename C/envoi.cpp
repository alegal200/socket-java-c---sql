/* TCPITER01D.C 
* serveur itératif mono-connexion * 
- Claude Vilvens - 
*/ 
/////////////////////////////////////
//       P46-47-48-49
////////////////////////


#include <stdio.h> 
#include <stdlib.h> /* pour exit */ 
#include <string.h> /* pour memcpy */
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> /* pour les types de socket */ 
#include <netdb.h> /* pour la structure hostent */ 
#include <errno.h> 
#include <netinet/in.h> /* pour la conversion adresse reseau->format dot 
 ainsi que le conversion format local/format reseau */ 
#include <netinet/tcp.h> /* pour la conversion adresse reseau->format dot */ 
#include <arpa/inet.h> /* pour la conversion adresse reseau->format dot */ 
#define PORT 50011 /* Port d'ecoute de la socket serveur */ 
#define MAXSTRING 500 /* Longueur des messages */ 
char* lectureVac( int id_source);
int main() 
{ 
 int hSocketEcoute, /* Handle de la socket d'écoute */ 
 hSocketService; /* Handle de la socket de service connectee au client */ 
 struct hostent * infosHost; /*Infos sur le host : pour gethostbyname */ 
 struct in_addr adresseIP; /* Adresse Internet au format reseau */ 
 struct sockaddr_in adresseSocket; 
 /* Structure de type sockaddr contenant les infos adresses - ici, cas de TCP */ 
 uint tailleSockaddr_in; 
 char msgClient[MAXSTRING], msgServeur[MAXSTRING] , msgHeader[25] ,  msgid[4] , car[1]  ; 
 int nbreRecv; 
/* 1. Création de la socket */ 
hSocketEcoute= socket(AF_INET, SOCK_STREAM, 0); 
 if (hSocketEcoute== -1) 
 { 
 printf("Erreur de creation de la socket %d\n", errno); 
 exit(1); 
 } 
 else printf("Creation de la socket OK\n"); 
/* 2. Acquisition des informations sur l'ordinateur local */ 
 if ( (infosHost = gethostbyname("moon"))==0) 
 { 
 printf("Erreur d'acquisition d'infos sur le host %d\n", errno); 
 exit(1); 
 } 
 else printf("Acquisition infos host OK\n"); 
 memcpy(&adresseIP, infosHost->h_addr, infosHost->h_length); 
 printf("Adresse IP = %s\n",inet_ntoa(adresseIP)); 
 /* Conversion de l'adresse contenue dans le structure in_addr 
 en une chaine comprehensible */ 
/* 3. Préparation de la structure sockaddr_in */ 
 memset(&adresseSocket, 0, sizeof(struct sockaddr_in)); 
 adresseSocket.sin_family = AF_INET; /* Domaine */
 adresseSocket.sin_port = htons(PORT); 
 /* conversion numéro de port au format réseau _*/ 
 memcpy(&adresseSocket.sin_addr, infosHost->h_addr,infosHost->h_length); 
/* 4. Le système prend connaissance de l'adresse et du port de la socket */ 
 if (bind(hSocketEcoute, (struct sockaddr *)&adresseSocket, 
 sizeof(struct sockaddr_in)) == -1) 
 { 
 printf("Erreur sur le bind de la socket %d\n", errno); 
 exit(1); 
 } 
 else printf("Bind adresse et port socket OK\n"); 
/* 5. Mise a l'ecoute d'une requete de connexion */
 if (listen(hSocketEcoute,SOMAXCONN) == -1) 
 { 
 printf("Erreur sur lel isten de la socket %d\n", errno); 
 close(hSocketEcoute); /* Fermeture de la socket */ 
 exit(1); 
 } 
 else printf("Listen socket OK\n"); 
/* 6. Acceptation d'une connexion */ 
 tailleSockaddr_in = sizeof(struct sockaddr_in); 
 if ( (hSocketService = 
 accept(hSocketEcoute, (struct sockaddr *)&adresseSocket, &tailleSockaddr_in) ) 
 == -1) 
 { 
 printf("Erreur sur l'accept de la socket %d\n", errno); 
 close(hSocketEcoute); exit(1); 
 } 
 else printf("Accept socket OK\n"); 
/* 7.Reception d'un message client */ 

do{



    if ((nbreRecv = recv(hSocketService, msgClient, MAXSTRING, 0)) == -1)      { 
    printf("Erreur sur le recv de la socket %d\n", errno); 
    close(hSocketEcoute); /* Fermeture de la socket */ 
    close(hSocketService); /* Fermeture de la socket */ 
    exit(1); 
    } 

    strncpy(msgHeader,msgClient,17);

    printf("Message recu = %s\n", msgClient); 
    msgHeader[17] ='\0';
    printf("msg header %s \n",msgHeader);
   // printf("*\n");
    if(strcmp(msgHeader,"tok:112233445566@") == 0){
        memcpy(msgServeur,&msgClient[17],9);
        for(int i = 0; i <= strlen(msgServeur); i++){
            if(msgServeur[i] == '*')  
            {
                msgServeur[i] = '\0';
            }
        }
        int id = atoi(msgServeur);
        memset(msgServeur,'\0',sizeof(msgServeur));
        snprintf(msgServeur, 1, "%d", id); 
        printf("id est %d \n",id); 
        FILE *fp ;
                char c ,id_read[5] ;
                int id_int ;
                long ln_seek ;  

                fp = fopen("./current.vac","r");
            
                fseek(fp, 0, SEEK_SET);
            
                //lecture du 1 er id 
                fread(id_read, sizeof(id_read), 1, fp); // lecture de
                id_int = atoi(id_read); 
                
                while ( ( c = getc(fp)) != EOF ) {                   ///  |a;bcdefg
                    if(c=='\n'){
                    fread(id_read, sizeof(id_read), 1, fp); // lecture de l id 
                    id_int = atoi(id_read);      
                    }

                    if(id_int == id ){ 
                        int itRep = 0 ;
                        while ( ( c = getc(fp)) != EOF ){
                            if( c =='\n')
                                break;
                             //snprintf(car, 1, "%c", c); 
                             //strcat(msgServeur,car);
                             //printf(car);
                             msgServeur[itRep] = c ;
                            itRep++;    
                        } 
                        id_int = -1 ;   
                                    
                    }
            
                }
                fclose(fp);
                

        printf("msgserv %s*\n",msgServeur);
    }else{
        printf("client non valide \n");
        strcpy(msgServeur,"non pas bien");

    }


        printf("val client %s \n",msgClient);
        printf("val msg %s \n",msgServeur);    

    if (send(hSocketService, msgServeur, MAXSTRING, 0) == -1) 
    { 
        printf("Erreur sur le send de la socket %d\n", errno); 
        close(hSocketEcoute); /* Fermeture de la socket */ 
        close(hSocketService); /* Fermeture de la socket */ 
        exit(1); 
    }    
    else printf("Send socket OK\n");
    
    /* code */
} while (true);
 
/* 11. Fermeture des sockets */ 
close(hSocketService); /* Fermeture de la socket */ 
 printf("Socket connectee au client fermee\n"); 
close(hSocketEcoute); /* Fermeture de la socket */ 
 printf("Socket serveur fermee\n"); 
 return 0; 
} 

