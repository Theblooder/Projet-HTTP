# Construction de la réponse

Nous construisons la réponse en respectant le plus possible de règles de sémantique.
Les règles utilisés sont indiqué dans la deuxième partie ci-dessous.

Le fichier `Answer.c` contient une structure pour créer la réponse (Quand tout est est bon nous envoyons d'un seul coup la réponse avec la librairie librequest)
Le fichier `constructAnswer.c` contient tout les fonctions pour créer cette réponse.

Dans chaque fichier .h toutes les fonctions sont documentées.
 
# Règles utilisé / Implémentation

Codes d'erreurs utilisé :

- 400 (Si version >= 1.1 et pas de header `Host` présent)
- 404 (Si le fichier recherché n'existe pas)
- 405 (Si méthode POST mais pas de fichier .php)

- 500 (Si nous avons une erreur serveur dans la lecture du type MIME)
- 501 (Si le méthode n'est pas implémenté (pour l'instant nous avons seulement GET, HEAD et POST))
- 505 (Si le version d'HTTP n'est pas supporté maximum 1.9)

Headers utilisés :

- Host-header : Si la version est plus grande que 1.0 alors nous réutilisons le Host-headers envoyé.
- Content-type-header : On utilise le type MIME du fichier (pour les fichiers javascript et css nous utilisons l'extension du fichier)
- Content-length-header : On met juste la taille du fichier

Ce que nous avons implémenté :

- Mis en place des méthodes GET et HEAD
- Gestion de la connexion (keep-alive / close)
- Gestion du multi-site