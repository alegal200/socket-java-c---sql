# communication using sockets 

## client c 
    -> demande les identifiants  pseudo / password 
    -> selectionner 
        -> deconnextion 
        -> Ajout vacancier 
        -> modificatin vacancier

*  connection 
    - envoies au serveur  login et le mots de passes 
    si le serveur est d accord alors le serveur donnera un numéro de connection (token)

* deconnection 
    - couper la connection avec le serveur 

* ajout vacancier 
    - le client envoi une demande de création au serveur 
    - le serveur repond en donnant l id du nouveau utilisateur
    - le client modifie le nouveau vacancier 

* modification vacancier 
    - envoyer une demande au serveur  + token de connection + modification + type de modification suivit de l id suivit de la valeur a cahnger (pas d espace)

