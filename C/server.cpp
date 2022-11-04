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
#define PORT 50000 /* Port d'ecoute de la socket serveur */ 
#define MAXSTRING 100 /* Longueur des messages */ 
int creationDunVac();
void modifvac(char id[4] , char val[25] , int zone);
int main() 
{ 
 int hSocketEcoute, /* Handle de la socket d'écoute */ 
 hSocketService; /* Handle de la socket de service connectee au client */ 
 struct hostent * infosHost; /*Infos sur le host : pour gethostbyname */ 
 struct in_addr adresseIP; /* Adresse Internet au format reseau */ 
 struct sockaddr_in adresseSocket; 
 /* Structure de type sockaddr contenant les infos adresses - ici, cas de TCP */ 
 uint tailleSockaddr_in; 
 char msgClient[MAXSTRING], msgServeur[MAXSTRING] , msgHeader[25] ,  msgid[4]; ; 
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
 if ((nbreRecv = recv(hSocketService, msgClient, MAXSTRING, 0)) == -1) 
 /* pas message urgent */ 
 { 
 printf("Erreur sur le recv de la socket %d\n", errno); 
 close(hSocketEcoute); /* Fermeture de la socket */ 
 close(hSocketService); /* Fermeture de la socket */ 
 exit(1); 
 } 
 else printf("Recv socket OK\n"); 
 msgClient[nbreRecv]=0; 
 printf("Message recu = %s\n", msgClient); 
/* 8. Envoi de l'ACK du serveur au client */ 
 sprintf(msgServeur,"ACK pour votre message : <%s>", msgClient); 
 if (send(hSocketService, msgServeur, MAXSTRING, 0) == -1) 
 { 
 printf("Erreur sur le send de la socket %d\n", errno); 
 close(hSocketEcoute); /* Fermeture de la socket */ 
 close(hSocketService); /* Fermeture de la socket */ 
 exit(1); 
 } 
 else printf("Send socket OK\n"); 
 while (true){
        // printf("recption d un msg");
        /* 9. Reception d'un second message client */ 
    if ((nbreRecv = recv(hSocketService, msgClient, MAXSTRING, 0)) == -1) 
    /* pas message urgent */ 
    { 
    printf("Erreur sur le recv de la socket %d\n", errno); 
    close(hSocketEcoute); /* Fermeture de la socket */ 
    close(hSocketService); /* Fermeture de la socket */ 
    exit(1); 
    } 
    //else printf("Recv socket OK\n"); 

        msgClient[nbreRecv]=0; // ?
        printf("Message recu = %s\n", msgClient); 

        /* 10. Envoi de l'ACK du serveur au client */ 
        // sprintf(msgServeur,"ACK pour votre message : <%s>", msgClient); 
        printf("\n\n\n\nla reponse envoyer est %s\n",msgClient);
        strncpy(msgHeader,msgClient,23);
        printf("val du header %s \n",msgHeader);
        if( strcmp("con:alex@pass",msgClient) == 0){
            strcpy( msgServeur ,"123456789987654321" ) ;
        }
        
        else if(strcmp("tok:123456789987654321@",msgHeader) == 0){
            memcpy(msgServeur,&msgClient[23],9);
            // creation ->
            if(strcmp(msgServeur,"creation") == 0 ){   
                int id_tmp ;
                char id_tmpp[4];
                memset(msgServeur,'\0',sizeof(msgServeur));
                id_tmp = creationDunVac();      
                snprintf(id_tmpp, 6, "%d", id_tmp);
                strcpy(msgServeur,id_tmpp);
                printf("vla %s \n",msgServeur);
            }
            else{
            // modification -> 
                memset(msgServeur,'\0',sizeof(msgServeur));
                memcpy(msgServeur,&msgClient[23],2);
                    // nom 
                
                if(msgServeur[0] == 'm' &&msgServeur[1] == 'n' ){
                memcpy(msgid,&msgClient[25],4); 
                msgid[4] = '\0'; 
                memcpy(msgServeur,&msgClient[29],25); 
                modifvac(msgid,msgServeur,0);
                }

                if(msgServeur[0] == 'm' &&msgServeur[1] == 'p' ){
                memcpy(msgid,&msgClient[25],4); 
                msgid[4] = '\0'; 
                memcpy(msgServeur,&msgClient[29],25); 
                modifvac(msgid,msgServeur,1);
                }
                if(msgServeur[0] == 'm' &&msgServeur[1] == 'd' ){
                memcpy(msgid,&msgClient[25],4); 
                msgid[4] = '\0'; 
                memcpy(msgServeur,&msgClient[29],25); 
                modifvac(msgid,msgServeur,2);
                }
                if(msgServeur[0] == 'm' &&msgServeur[1] == 'e' ){
                memcpy(msgid,&msgClient[25],4); 
                msgid[4] = '\0'; 
                memcpy(msgServeur,&msgClient[29],25); 
                modifvac(msgid,msgServeur,2);
                }
            
            }
           
            
            
           
        }
        else{
            strcpy(msgServeur,"\0");
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
 }
 
 
/* 11. Fermeture des sockets */ 
close(hSocketService); /* Fermeture de la socket */ 
 printf("Socket connectee au client fermee\n"); 
close(hSocketEcoute); /* Fermeture de la socket */ 
 printf("Socket serveur fermee\n"); 
 return 0; 
} 




///////////////////////////////////
///// ouverture du fichier + création d une ligne pour un nouveau vac + return id vac (int)
//////////////////////////////////
int creationDunVac(){
    char val_last_id[5] , c ; 
    int last_id ;
    FILE *fp , *fp_tmp;
    fp = fopen("./current.vac","r");
    fseek(fp, 0, SEEK_SET); 
    fread(val_last_id, sizeof(val_last_id), 1, fp);
    last_id = atoi(val_last_id);
    fp_tmp = fopen("./tmp.vac","w");
    fprintf(fp_tmp,"%4d;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;00/00/0000;N\n",++last_id);
    fseek(fp, 0, SEEK_SET); 
    while ( ( c = getc(fp)) != EOF ) { 
        fputc(c, fp_tmp);  
    }
    fclose(fp);
    fclose(fp_tmp);
    remove("./current.vac");
    rename("./tmp.vac","./current.vac");
    return last_id ;
}
///////////////////////////////////
//////id , valeur plus la zonne de mémoir et le fichier sera mit a  jour avec la bonne valeur
///////////////////////////////////
void modifvac(char id[5] , char val[25], int zone){
    printf("entre dans la fct modifiif \n ////////// \n");
    FILE *fp , *fp_tmp;
    char c ,id_read[5]  ;
    int id_int , id_source , ptvirg = 0 ;
    long ln_seek ;  
    id_source = atoi(id);  
    fp = fopen("./current.vac","r");
    fp_tmp = fopen("./tmp.vac","w");
    fseek(fp, 0, SEEK_SET);
    fseek(fp_tmp, 0, SEEK_SET);
    //lecture du 1 er id 
    fread(id_read, sizeof(id_read), 1, fp); // lecture de
    id_int = atoi(id_read); 
    fprintf(fp_tmp,"%4d",id_int);   
    fputc(';', fp_tmp);  
    
    while ( ( c = getc(fp)) != EOF ) {                   ///  |a;bcdefg
        if(c=='\n'){
           fread(id_read, sizeof(id_read), 1, fp); // lecture de l id 
           id_int = atoi(id_read);  
           fputc('\n', fp_tmp); 
           fprintf(fp_tmp,"%4d",id_int);   
           fputc(';', fp_tmp);   
           ptvirg = 0 ; 
        }
        if(c==';')
            ptvirg++;
        if(id_int == id_source && ptvirg == zone ){ 
            while ( ( c = getc(fp)) != EOF ){
                if(c==';' || c =='\n')
                    break;
            }
            if(zone != 0)    
                fputc(';', fp_tmp);  
            fputs(val,fp_tmp); 
            id_int = -1 ;
            //ptvirg = 0 ;    
                        
        }
        if(c !='\n')
            fputc(c, fp_tmp);     
    }
    fclose(fp);
    fclose(fp_tmp);

    remove("./current.vac");
    rename("./tmp.vac","./current.vac");
}