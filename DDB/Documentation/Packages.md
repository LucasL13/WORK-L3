# DROP DA BOMB

# Les packages et technologies utilisés

## Express 

Le module Express (package npm) est probablement le module le plus populaire et le plus utilisé pour Node. 
Nous avons vu dans la section précédente que si la plateforme Node est en soi un noyau simple et aux fonctionnalités limités, elle devient en revanche d’une incroyable puissante si on prend en compte les modules que l’on peut y ajouter. Express apparait comme l’un de ces modules qui rend Node si populaire, puissant et agréable à utiliser ; ce module agit comme une « surcouche » et permet d’ajouter (et/ou remplacer) des fonctionnalités très intéressantes à notre serveur. 
NB : Express est lui-même un module « décomposé », qui est livré avec un certain nombre de fonctionnalités et qui peut être « augmenté » par de nombreux et divers sous-modules. Pour plus d’informations au sujet de ce module, ses possibilités et ses « sous-modules » nous vous invitons à consulter la page officielle du package, dont le lien est fourni dans la section finale « Bibliographie ». 
Nous présenterons uniquement les deux fonctionnalités utilisées dans le cadre de notre serveur. 

* La première concerne la « gestion des routes ». En effet, Node seul permet de servir les fichiers au client à partir d’une requête précise, mais force est de reconnaitre que cela devient relativement compliqué et peu pratique lorsque les différentes requêtes à traiter se multiplient et se complexifient. Express (et c’est là une des raisons de sa popularité) permet de gérer tout cela de manière simplifiée et automatisée avec un système de routes. 
Ainsi en deux lignes seulement on peut indiquer au serveur « Pour telle requête, tu envoi tel fichier ».

    Initialisation : 
    ``` javascript
        var express = require('express');
        var app = express();
    ```

    Ensuite lorsque l’utilisateur veut accéder à monSite/AccountCreate, on lui renvoi la page AccountCreate.html. 
``` javascript
  app.get('/Account', function(req,res){
      res.render('Account');
  });
```

    On fait cela pour toutes les routes, tous les fichiers, que l’on souhaite desservir au client.
    Un autre aspect incroyable du système de routes par Express est la gestion des ressources liées auxdits fichiers. En effet, avec Node seul si on renvoi une page, disons index.html, mais que celle-ci importe 2 scripts, 2 images et 3 feuilles de styles, on doit alors créer un « chemin » pour chacun de ces fichiers, les ouvrir et les renvoyer en adaptant précisément le contenu de la requête de renvoi. 
    C’est terriblement lourd et complexe à gérer manuellement.

    Avec Express, encore une fois, on peut le faire en… 1 ligne seulement.
``` javascript
    app.use(express.static(path.resolve('../')));
```
