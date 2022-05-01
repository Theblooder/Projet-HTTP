# README.md

## Version 2.0

Nous pouvons maintenant générer une réponse pour un requete reçu, toutes les informations détaillées sont dans le fichier README.md dans le dossier /src/semantique.
C'est la que ce trouve les fichiers rajoutés pour cette version.

Nous avons de plus ajouté un fichier de configuration `server.conf` ou l'on peu gérer le multi-site. Attention ce fichier est très rudimentaire (n'ajouter que des lignes contenant au moins un égal et bien laisser une ligne vide à la fin du fichier (ce fichier sera amélioré par la suite))

Les méthodes acceptées sont :
- GET
- HEAD

Le programme s’exécute de la manière suivante

- `make`
- `./httpparseur`

Le programme écoute sur l'adresse 127.0.0.1 et sur le port 8080.


## Version 1.0

Parseur pour vérifier la syntaxe HTTP

# Informations indispensables

Le programme s’exécute de la manière suivante

- `make`
- `./httpparseur <file> [search]`

Sans le [search] vous pourrez voir l’arbre des tokens.

`script.bs 0 19999`
Pour vérifié que tout les fichiers de test sont parser correctement

27 sec pour l'éxécution complète

# Information complémentaire

Seuls les headers suivant sont présents

- Accept-Header
- Accept_Charset_header
- Accept_Encoding_header
- Accept_Language_header
- Connection_header
- Content_Length_Header
- Content_Type_header
- Cookie_header
- Expect_header
- Host_header
- Referer_header
- Transfer_Encoding_header
- User_Agent_header


__Authors__

GILGER Rémi, COURTEL Benoît, FATHI Ihab