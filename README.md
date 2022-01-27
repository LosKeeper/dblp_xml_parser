# Projet Programmation 2021

Le but du projet est de d'analyser la base de données des articles de recherche en informatique
provenant du site dblp.org. Votre programme devra ouvrir la base de données, la parser, la stocker
dans une structure adaptée, la stocker dans un autre fichier au format binaire adapté et l'analyser à
l'aide d'algorithmes de graphe. L'analyse permetra notamment de calculer le plus court chemin entre
deux auteurs. Dans ce contexte, un chemin est une suite d'auteurs (a_1, a_2, ..., a_n) telle que,
pour tout 1 <= i < n, il existe un article où a_i et a_{i+1} sont co-auteurs.