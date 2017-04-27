
<h1 align="center"> DROP DA BOMB </h1>

## Les aspects techniques

### La structure du projet
<p align="center">
    <img src="https://github.com/LucasL13/WORK-L3/blob/master/DDB/Documentation/Images/structure.png" width="600px"/>
</p>

Le projet DropDaBomb est basé sur une architecture Client-Serveur classique. 
Le client est un client web, il est donc ouvert à tous les systèmes d’exploitation, tous les navigateurs, quel que soit le support. 
Le serveur est un serveur distant, adressé par une IP publique, qui repose sur deux technologies : Node.js pour l’aspect purement serveur (détaillé dans les parties suivantes) et MySQL pour le serveur Base de Données. Seul le serveur Node.js est autorisé à échanger avec la base de données, le client communique donc uniquement avec le serveur Node.js.

*Dans un soucis de simplification, on parlera de **Serveur** pour le serveur Node.js et de **Base de données** ou **BDD** pour la partie serveur MySQL*

 
