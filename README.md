# Traduction et Simulation d'un Assembleur vers Code Machine

## Présentation

Ce projet a pour but de traduire un programme écrit en assembleur vers son équivalent en code machine hexadécimal, puis de simuler son exécution.  
Il a été réalisé dans le cadre du cours **Architecture des Ordinateurs** à l'Université Paris Dauphine.

## Fonctionnalités principales

- **Traduction Assembleur → Hexadécimal**  
- **Exécution d'un programme hexadécimal**  
- **Menu interactif** avec affichage stylisé dans le terminal (couleurs, ASCII art)  
- **Détection d'erreurs** lors de la traduction et de l'exécution (syntaxe, débordements de pile, accès illégal en mémoire, etc.)  
- **Gestion des étiquettes** pour les instructions de saut

## Structure du projet

```
Projet_Archi/
├── Source/
│   ├── assembleur_to_machine.c
│   ├── assembleur_to_machine.h
│   ├── executeur.c
│   ├── executeur.h
│   ├── main.c
├── exemples/         # Exemples de fichiers assembleur
└── README.md
```

- `main.c` : Gestion du menu et de l'interface utilisateur.
- `assembleur_to_machine.c / .h` : Traduction du code assembleur vers hexadécimal.
- `executeur.c / .h` : Exécution du fichier hexadécimal.

## Installation

1. **Cloner le dépôt :**

```bash
git clone https://github.com/ton-pseudo/projet-archi.git
cd projet-archi
```

2. **Compiler :**

```bash
gcc Source/main.c Source/assembleur_to_machine.c Source/executeur.c -o executeur
```

3. **Exécuter :**

```bash
./executeur
```

## Comment utiliser

1. Lancer l'exécutable.
2. Choisir un fichier assembleur parmi les exemples ou fournir le vôtre.
3. Le programme traduit le fichier en hexadécimal (`hexa.txt`).
4. Le simulateur exécute ce fichier et affiche les résultats dans le terminal.

## Exemples

Des exemples de fichiers assembleur sont disponibles dans le dossier `exemples/`.

## Bugs connus et améliorations possibles

- Pas de gestion des commentaires dans l'assembleur (`;`).
- Aucune correction automatique des fautes dans les étiquettes.
- Complexité potentielle pour gérer des boucles imbriquées lors de la détection d'erreurs.

**Idées d'améliorations** :  
- Ajout de la détection de fautes de frappe dans les étiquettes (distance de Levenshtein).
- Meilleure gestion mémoire pour de très grands fichiers.

## Développeurs

- **William Miserolle**
- **Nicolas de Pellegars Malhortie**

---

*Projet réalisé en avril 2025.*
