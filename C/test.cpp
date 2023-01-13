#include "sha/sha256.h"
#include <stdio.h>
#include <stdio.h> 
#include <stdlib.h> /* pour exit */ 
#include <string.h> 

int main()
{
    printf("salt \n");
    Sha256Context ctx;
    SHA256_HASH hash;
    char input[] = "Hello, World!";
     char has [64] , c [64] ;
    // Initialisation du contexte
    Sha256Initialise( &ctx );

    // Ajout des données à hacher
    Sha256Update( &ctx, (uint8_t*)input, strlen(input) );

    // Calcul du hash
    Sha256Finalise( &ctx, &hash );

    // Impression du hash en hexadécimal
    for (int i = 0; i < 64; i = i+2)
    {
        printf("%02x", hash.bytes[i/2]);
        sprintf(&has[i], "%02x", hash.bytes[i/2]);
        
        
    }
    


    printf("\n*%s*\n",has);
    return 0;

}