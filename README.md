# Maurice Romain et Viry Corentin - LZW

## Introduction

Dans le cadre de notre projet d'algorithmie, nous avons réalisé un encodeur et un décodeur implémentant l'algorithme LZW. Cet algorithme est largement utilisé pour compresser des images, notamment des images au format .GIF.

### Encodage

L'encodage LZW comprend les étapes suivantes :

1. **Lecture de l'input** : Premièrement, nous lisons le fichier que nous souhaitons compresser. Cela peut être un fichier texte contenant des caractères ASCII ou bien un fichier image (les images sont plus de domaine de LZW).

2. **Initialisation du dictionnaire** : Création d'un dictionnaire remplis avec des codes ASCII et leur correspondance, ce dictionnaire sera utiliser par la suite afin de stocker les motifs rencontrer lors du parcours du fichier.

3. **Encodage des motifs et ecriture dans l'output** : Nous parcourons ensuite le fichier source caractère par caractère (char ou bit) et le disctionnaire se remplis au fur et à mesure. À chaque fois, il faut verifier si le motif courant est connu par le dictionnaire. Si il est deja connu, nous ajoutons un autre char a ce motif afin d'obtenir un motif qui n'est pas connu et qu'on l'insere dans le dictionnaire. Ces codes que l'on ajoute dans le dictionnaire, sont ensuite écrite les un a la suite des autres dans le fichier output.

### Décodage

Le decodage LZW comprend les étapes suivantes :

1. **Lecture de l'input** : Premièrement, nous lisons le fichier que nous souhaitons decompresser. Cela est un fichier qui contient donc du code déjà compresser.

2. **Initialisation du dictionnaire** : Création d'un dictionnaire remplis avec des codes des motifs et leur correspondance, ce dictionnaire sera utiliser par la suite afin de stocker les codes de motifs rencontrés lors du parcours du fichier.

3. **Décodage des codes** : Nous parcourons les codes du fichier compressé et utilisons le dictionnaire pour reconstruire les motifs originaux correspondants à chaque code. Nous ajoutons progressivement ces motifs au fichier output.

4. **Reconstruction du fichier original** : En utilisant les motifs décryptés, nous reconstituons le fichier original caractère par caractère (ou pixel par pixel). Les motifs décodés sont ajoutés au fichier de sortie pour restaurer le contenu original.

5. **Écriture du fichier décodé** : Une fois que tout le fichier original a été reconstitué, nous écrivons le résultat dans un nouveau fichier, qui est une version décompressée et identique à l'original.


## Utilisation

utiliser `make`

Pour exécuter le programme, utilisez la commande `./main '-e'` pour decoder remplacer le `-e` par le `-d` dans le dossier du projet. `-e` pour l'encodage et `-d` pour le décodage. l'input est l'input de l'encodage et l'output de decodage et inversement.

## État final du projet :

- Encodeur ASCII -> fonctionnel 
- Décodeur ASCII -> en partie fonctionnel 

Fichiers testés :

- 2city11.txt (TP 06)

## Répartition du travail

Maurice Romain :
- Implémentation du décodeur ASCII
- Implémentation de l'encodeur ASCII
- Tests et débogage

Viry Corentin :
- Implémentation du décodeur ASCII
- Implémentation de l'encodeur ASCII
- Tests et débogage

## Bilan du Groupe

Ce projet nous a permis de mieux comprendre le fonctionnement de l'algorithme LZW et de nous familiariser avec le langage C. Nous avons réussi à mettre en œuvre un encodeur et un décodeur fonctionnels pour les fichiers ASCII.

Cependant, le chemin était semé d'embuche, nous avons rencontré quelques problèmes lors de la réalisation du projet. Par exemple, lors de l'implémentation de l'encodeur, nous avons découvert qu'il y avait des moments où le même pointeur était utilisé dans plusieurs cases du dictionnaire. A cause de cela nous avons perdu beaucoup de temps en refaisant de zero notre code.

lors de la partie concernant la manipulation des bits, nous avons consacré beaucoup de temps (pas seulement notre groupe) à essayer de coder les 0, qui sont difficiles à encoder et à manipuler en C. , mais cela nous a permis 

Au final, ce projet nous a été très bénéfique et nous a permis de développer nos compétences en algorithmique et en programmation, tout en nous confrontant à des problématiques spécifiques.

