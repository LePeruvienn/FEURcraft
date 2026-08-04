@mainpage

@image html FEURcraft.png "Logo FEURcraft"

# Introduction

Salut en ce moment je travaille sur un clone de Minecraft en C et je me demande si ça intéresserait des gens de travailler sur ce projet avec moi pendant le moi d'août ?

Le but c'est d'en fait créer notre propre version du jeu, avec le moins de dépendance possible et rendant la contribution accessible a tout le monde, notamment aux 1A.

Le projet est volontairement en C afin que des la première année les nouveau puisse directement appliquer ce qu'ils font en cours sur su développement de jeux vidéo,

Et je pense qu'un projet comme celui-ci peut être vraiment très enrichissant pour tout le monde, et voir tout les aspect du game dev.

Le projet est en C11 avec OpenGL 3.3 pour parler au GPU.

les dépendances sont GLFW (abstraction OS pour la fenetre et les inputs) et stb pour lire et écrire des PNG/jpg. et c'est tout !

J'ai implémenter une petite couche d'abstraction sur OpenGL et une petite lib de calcul matriciel et vectoriel et d'autres choses aussi, la base est la

Est ce que vous pensez que je projet est une bonne idée ? est ce que ça intéresse des gens? je suis ouvert au retours!

[Lien vers le repo github](https://github.com/LePeruvienn/FEURcraft)

# Architechure tu projet

### Vue d'ensemble

```
. Racine du projet
│
├── FEURcraft           // Dossier contenant le code source
│   ├── CMakeLists.txt  // Règle de compulilations
│   ├── main.c          // point d'entrée du programme
│   │
│   │ // Modules
│   ├── data     // Structures de données
│   ├── graphic  // Abstraction OpenGL / moteur de rendu
│   ├── math     // Mathématiques
│   ├── system   // Gestion entrée/sortie système
│   ├── world    // Représentation du monde voxel
│   └── utils    // Trucs utile que je sais pas ou mettre
```

### Modules

Chaque module est compilé en une librarie partager (`.so` ou `.dll` en fonction de la plateforme), cela permet qu'elle peut être lié facilement à n'importe quelle executable (jeu, tests, exemples).

Chaque module possèdle la même organisation de fichiers.

```
 Mon Module
├── CMakeLists.txt  // Régèle de compilation du module
├── include         // Fichier d'en-tête publique .h
├── private         // Fichier d'en-tête privé .h
└── src             // Fichiers source du module .c
```

- Fichier d'en-tête **publique** : Ils peut être inclu par tout les autres modules.
- Fichier d'en-tête **privé** : Ils peut être inclu uniquement par son propre module.

# Technologie

| Technologie | Rôle                                                          |
| ----------- | ------------------------------------------------------------- |
| OpenGL 3.3  | API graphique afin de communiquer au GPU pour le rendu du jeu | 
| stb_image   | Lecture et écriture d'image (png, jpeg, ...)                  |
| GLFW        | Abstraction entrée système et gestion de la fenêtre           |
| OpenAL ?    | Audio 3D (Pas encore implémenter)                             |

Notre moteur voxel implémente ces technologie et les expose avec une couche d'abstraction pour faciliter leurs utilisateion. (ex: module `graphic` est une abstraction d'OpenGL).

**Documentations** :
- [Documentation d'OpenGL](https://registry.khronos.org/OpenGL-Refpages/gl4//)
- [Documentatioon GLFW](https://www.glfw.org/docs/latest/)

**Liens utiles**
- [Apprendre OpenGL](https://learnopengl.com/)
- [Repo de GLFW](https://github.com/glfw/glfw)
- [Repo de STB](https://github.com/nothings/stb)

# Compilation

La compilation se fait avec [CMake](https://learnopengl.com/) qui permet d'avoir un seul système de build pour plusieurs plateforme (ici on vise Linux et Windows).

Pour compilé le projet il ya deux manière de faire :

1) Via le Makefile qui est un wrapper de CMake

```bash
make clean
make
```

2) Executant directement les commandes de compilation CMake

```bash
rm -rf build/
cmake --build build
cmake -B build
```

# Exécutables

Tout les executable générer par la compilation se trouve dans le dossier `bin/`.

Il ya 3 type d'écutable dans le projet :

- **Excutable principal** : nommé `FEURcraft` c'est le résultat du fichier `main.c`

- **Tests** : se termine tous pas `.tst` c'est tout les fichiers `.c` qui sont dans le dossiers `tests/src/`.

- **Exemples** : Ce sont des petit programme d'exemple d'utilisation de nos modules. Ils se termine par `.c` ce sont tout les fichiers `.c` dans le dossier `examples/src`.

⚠️ **CHAQUE EXECUTABLE DOIT ÊTRE LANCER DEPUIS LA RACINE DU PROJET**

Pour lancer un executable placer vous à la racine du projet, et vous pouvez ensuite l'executer comme ceci :

```bash
./bin/mon_exe
```

# Tests

Le projet possède une petite bibliothèque de tests unitaires nommée **FEUR_Test**.

Chaque fichier source situé dans `tests/src/` est compilé en un exécutable de test indépendant. 

Par exemple :

```text
tests/src/math_test.c
```

génère l'exécutable :

```text
bin/math_test.tst
```

Il est possible de lancer un test individuellement :

```bash
./bin/math_test.tst
```

ou via le script fourni :

```bash
./tests/run.sh math_test
```

Pour exécuter tout les tests du projet

```bash
./tests/run.sh
```

Voci un exemple de tests unitaire :

```c
#include "FEUR_Test/FEUR_Test.h"

#include <stdlib.h>

FEUR_Test_Result Test_1()
{
	int value = 10;

	FEUR_TEST_ASSERT(value == 10);
	FEUR_TEST_ASSERT(value != 5);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_2()
{
	float value = 0.333333f;

	FEUR_TEST_ASSERT_FLOAT(value, 0.333333f);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("This is a example of log in a test!");

	FEUR_Test_Add_Group("Easy Tests :)");

	FEUR_Test_Add_Test("Test 1", Test_1);

	FEUR_Test_Add_Group("Hard Tests D:");

	FEUR_Test_Add_Test("Test 2", Test_2);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
```

