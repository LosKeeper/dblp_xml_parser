# DBLP Parsing (projet programmation 2021)
## Sujet
Le but du projet est de d'analyser la base de données des articles de recherche en informatique
provenant du site dblp.org. Votre programme devra ouvrir la base de données, la parser, la stocker
dans une structure adaptée, la stocker dans un autre fichier au format binaire adapté et l'analyser à
l'aide d'algorithmes de graphe. L'analyse permetra notamment de calculer le plus court chemin entre
deux auteurs. Dans ce contexte, un chemin est une suite d'auteurs (a_1, a_2, ..., a_n) telle que,
pour tout 1 <= i < n, il existe un article où a_i et a_{i+1} sont co-auteurs.

## Compilation
Le programme doit être compilé avec le makefile en utilisant le commande `make`.

## Exécution
Le programme doit être exécuté avec le commande `./bin/dblp-parsing`.
- ### Options de lancement
    - `-h`: affiche l'aide
    - `-d ARGUMENT`: indique la base de données à ouvrir.
    - `-o ARGUMENT`: indique le fichier binaire à ouvrir.
    - `-o ARGUMENT`: indique le fichier binaire de sortie.
    - `-t ARGUMENT`: indique les titres de l'auteur renseigné.
    - `-a ARGUMENT`: indique le premier auteur pour la recherche de chemin.
    - `-b ARGUMENT`: indique le deuxième auteur pour la recherche de chemin.

## Fonctionnement
- Le programme ouvre la base de données et pour chaque article délimité par des balises `<article>`, il remplit une structure de données avec les informations de cet article puis les ajoutes à la structure du graphe en passant par une table de hachage. 
- Pour déterminer le chemin entre 2 auteurs, le programme applique l'algorithme de Dijkstra sur le graphe afin d'obtenir le plus court chemin entre les auteurs.

## Problèmes rencontrés
- Le programme fonctionne uniquement avec une petite base de données (moins de 15 Mo).
- L'algorithme de Dijkstra est mal implémenté et ne fonctionne pas correctement.
- Le système d'écriture et de lecture de fichiers binaire n'est pas optimale car écrit dans un fichier texte lisible par tous.
- Le parsage du fichier XML n'est pas optimale.
- La fonction de hachage est un peu lente.