# DROP DA BOMB

1. [Le jeu](#le-jeu)
2. [Utilisation du site](#utilisation-du-site)
3. [Les Regles](https://github.com/LucasL13/WORK-L3/tree/master/DDB/Documentation/LesRegles.md)
4. [Les Cartes](https://github.com/LucasL13/WORK-L3/tree/master/DDB/Documentation/LesCartes.md)
5. [L'interface](https://github.com/LucasL13/WORK-L3/tree/master/DDB/Documentation/Interface.md)
6. [Les packages et technologies utilisés](https://github.com/LucasL13/WORK-L3/tree/master/DDB/Documentation/Packages.md)
7. [Les aspects techniques](https://github.com/LucasL13/WORK-L3/tree/master/DDB/Documentation/Technique.md)
8. [La gestion de projet](https://github.com/LucasL13/WORK-L3/tree/master/DDB/Documentation/GestionProjet.md)
9. [Les fonctionnalités](#les-fonctionnalités)

## Le jeu

Drop Da Bomb est un jeu de plateau/cartes en ligne.
Il se base sur un ensemble de cartes (Cartes) collectionnables (**Inventaire**) par un joueur (**Compte**) afin de composer une ou plusieurs « main de jeu » (**Deck**). 
Ces cartes peuvent être obtenues de diverses manières mais principalement via la boutique (**Shop**) qui permet d’acheter avec différentes monnaies des lots de cartes (**Packs**). Il existe différents types et raretés pour les cartes. 
Une partie (**Match**) oppose deux joueurs, dans une arène spécifique avec des règles et des modes de jeu précis ; à tour de rôle les joueurs peuvent utiliser les cartes de leur Deck alors en main pour tenter de faire basculer l’objectif (« la bombe ») dans le camp de leur adversaire. 
Si la bombe explose ou se trouve dans le camp d’un joueur à la fin du temps imparti, la partie est perdue par celui-ci ; elle est gagnée par l’autre qui pourra alors remporter des récompenses (Cartes, Monnaie Virtuelle, etc..).

Ce jeu s’inspire par moments des jeux du même type devenus aujourd’hui des grands classiques (Yu-Gi-Oh, Clash Royale, HearthStone) mais se démarque par bien des aspects afin de se créer une véritable identité, un gameplay unique et tente de se faire sa place parmi les classiques cités précédemment. 

Ce projet concerne donc la réalisation de ce jeu ainsi que de toutes ses composantes à savoir : 
-	Réalisation du jeu pour clients web
-	Réalisation d’une interface de gestion pour clients web
-	Réalisation d’une interface web pour administrateurs (optionnel)
A plus long terme, les objectifs sont de développer une version « application » pour smartphones, ainsi que de maintenir et faire évoluer le jeu au travers de nouveaux contenus, nouveaux modes de jeux, évènements, etc... 


## Utilisation du site

Si vous êtes un nouvel utilisateur, voici comment jouer en quelques étapes seulement : 

1. Se connecter au site : [DDB](http://217.182.69.175:8080/Account)
2. Créer son compte 
3. Jouer en cliquant sur le bouton "Jouer" de la barre de navigation

+ Modifier son deck lorsque vous aurez acquis de nouvelles cartes dans la section **"Decks"**

## Les fonctionnalités 

### Implementées

* Interface web de connexion
* Interface web de visualisation et de modification des decks
* Matchmaking (8 salons - 16 joueurs max)
* Client de jeu 

### En cours d'implementation

* Interface web de création de compte

### A venir 

* Interface web avancée pour la gestion de compte
* Interface web pour les administrateurs
* Interface web pour la Boutique
* Amélioration de l'UI du jeu 
* Creation de nouveaux contenus (cartes, modes de jeu, icônes, etc..)
 