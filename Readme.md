# communication using sockets 

## client c 
    -> demande les identifiants  pseudo / password 
    -> selectionner 
        -> deconnextion 
        -> Ajout vacancier 
        -> modificatin vacancier

*  connection 
    - envoies au serveur  login et le mots de passes 
    si le serveur est d accord alors le serveur donnera un numéro de connection 

* deconnection 
    - envoies au serveur une deconnextion avec le id de session 

* ajout vacancier 
    - créer une structure vacancier 
    - envoyer le vacancier 
    - envoyer le numero de connection 

* modification vacancier 
    - envoyer une demande au serveur  + num de connection 
    - recupéré les informations 
    - afficher les infos plus possibilité de modification 
    - renvoyer le vacancier au serveur 
