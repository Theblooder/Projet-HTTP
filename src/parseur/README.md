# Fonctionnement du parseur

Tout les fichiers contiennent les fonctions pour toutes les règles de la grammaire HTTP (abnf)

Les fonctions vont s’appeler les uns les autres pour parcourir toute la chaîne est savoir si elle correspond à cette grammaire. Si oui alors un arbre `tree.c` est construit contenant tout les tokens de cette chaîne.

## Prototype des fonctions

`int HTTP_message(int **p*, const char **req*, node **pere*);`

`@param int *p` pointeur qui indique à la fonction à partir de quel endroit dans la requête elle doit lire

`@param const char *req` la requête à parser

`@param node *pere` endroit dans l’arbre ou l’on est

`@return int` retourne 0 si la règle est fausse et 1 si cette partie de l’arbre est juste

A chaque appel les fonctions vont créer un nouveau nœud dans l’arbre

Avant de se finir une fonction à deux possibilités :

- Ajouter les valeurs du nœud si la règle est bonne
- Supprimer la partie fausse de l’arbre et remet le pointeur p comme il était avant, sinon