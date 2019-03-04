![Logo Polytech Nice-Sophia](/Images/logoEPU.png) 
![Logo arduino](/Images/Arduino_logo_pantone.png)
![Logo Atmel](/Images/Atmel_logo.svg.png)

# Rapport projets Arduino 2018-2019

## Application de la Transformée de Fourier à l'affichage pratique et esthétique de contenu audio

### Auteurs : 
- Decottignies Thomas
- Picke Théo

### Responsable enseignant :
- Pascal Masson 

## Sommaire 
1. [**Motivations**](#motivations-)  
   - Pourquoi ce projet ?
   - A quoi ça sert ?
   - Comment ?
  
2. [**Etablissement du cahier des charges**](#etablissement-du-cahier-des-charges-) 
   - Les fonctions
   - Le matériel

3. [**Recherches**](#recherches-) 
   - Etat de l'art
   - Dans notre contexte
  
4. [**Déroulement**](déroulement-)
   - Séance 1 
   - ...
  
5. [**Rendu**](#rendu-)
   - Comparaison au cahier des charges
   - Améliorations possibles 
   - Ouverture à d'autres applications 
   
6. **Contributions et remerciements**

# Motivations :

## Pourquoi ce projet ?
### La puce **Arduino** :
Dans le cadre du cours d'electronique , nous avons l'occasion de faire preuve de créativité dans un sujet libre utilisant les capacités que nous offre Arduino et ses composants . Une carte Arduino est une puce programmable possédant au minima des entrées/sorties numériques/analogiques et une prise USB. Elle fonctionne selon un principe simple : un signal reçu depuis une entrée déclenche une ou des actions. Il est possible d'y connecter une batterie d'appareils capable d'acquérir des données (capteurs) et de moyens permettants une action (led, moteurs etc...). Nous ferons le long de ce projet l'abus de langage "l'Arduino" pour designer la puce Arduino , ce terme désignant en réalité l'écosystème Arduino. 
Dans notre cas , nous simplifierons le fonctionnement de l'Arduino selon le principe suivant :
> **Réception --> Traitement --> Action**

### Les contraintes :
Malgré la certaine liberté dont nous disposons, nous sommes tenus de respecter les contraintes suivantes :
- La faisabilité : il s'agit évidemment de mettre en pratique et d'approfondir nos connaissances. Nous devons veiller à ne pas être trop ambitieux et rester conscient de ce qui relève de notre niveau de compétance .
- Le coût : le budget de l'ecole n'etant pas illimité il faut veiller à ce que les sommes dépensées soient en commune mesure avec la nature du projet .
- Le temps : nous disposons d'un semestre et demi pour mener le projet à son terme . Toutefois si des difficultés techniques sont rencontrées , il est possible de minimiser la pénalisation en faisant preuve de d'ingéniosité et en proposant des solutions .
- L'utilisation d'une connexion radioferéquence est imposée.

### Idée et intérêts personnels :
Il s'est passé deux semaines entre le moment où nous avons formé les binômes et fixé le sujet. Nous avions une multitude de projets possibles parmi lesquels : 
- Des baskets GPS
- Un stabilisateur de chute
- Un trieur d'objets adaptatif
- Un trackpad laser pour PC

Toutefois nous avons rencontré un certain nombre de difficultés techniques qui semblaient compromettre une à une nos idées.
La confirmation de notre projet nous est venue avant tout de nos interets respectifs. Comment concilier musique , probabilité et programmation ? En nous penchant sur les vastes capacités que nous offre Arduino nous avons fini par nous accorder sur la création d'un afficheur de fréquence tel qu'on en trouve sur n'importe quel équaliseur , en ayant une vague notion de ce qu'est la transformée de Fourier (merci l'utilisation de l'osciloscope ).

## A quoi ça sert ?

### Utilité au quotidien
Le premier exemple qui nous est venu , étant tous les deux musiciens est le fonctionnement d'un accordeur. Un son émis par l'instrument est capté par un micro (sonore ou à vibrations) , analysé en fréquences et un affichage de la fréquence actuelle constitue la note jouée. C'est le même principe lorsqu'il s'agit de rêgler l'équibrage des différentes enceintes d'un home cinéma par exemple. La mesure des différentes fréquences permet d'avoir une balance entre grave et aigus adaptés au type de divertissement. D'autres applications dans les sciences existent pour l'analyse de systèmes mécaniques.

## Comment ?
### Les ressources
Sans avoir étudié en détail les caractéristiques du système , nous savons qu'il nous faut un capteur pour l'acquisition du son , un boitier d'acquisition , un logiciel de traitement et enfin un écran .
Un lot d'écrans LED etait déjà à notre disposition en salle de TP ,nous avons donc décidé de les utiliser.

### Le principe
Le coeur du projet repose sur un opérateur qu'est la transformée de fourier rapide : ... Description Théo
Le fonctionnement de la FFT nous pose toutefois un problème . Etant très gourmande en ressources , nous sommes conscients que la faible puissance de calcul de l'arduino peut être un frein à la réalisation d'un programme devant gerer à la fois l'affichage sur l'écran LCD et les calculs liés à la transformée. Nous avons dans un premier temps penséà l'utilisation d'un PC afin de déleguer les calculs à un processeur plus puissant. Nous avons également à disposition des cartes Arduino Mega et due.

# Etablissement du cahier des charges :
## Découpage en fonctions
Afin d'établir le cahier des charges (consultable [ici](/CDC.md)), nous avons choisi de découper notre projet en fonctions simples que nous tacherons de faire interagir par la suite :
### 1. L'affichage :
Afin d'afficher correctement les resultat de notre programme , il est essentiel de maitriser les possibilités d'affichage que nous offre l'ecran mis à notre disposition . Nous devons réfléchir à la fois à un affichage clair , intelligible et esthétique . Pour cela le tracer de formes géométriques , de droites et l'affichage de connées sur l'ecran constituent les elements de base de ce que sera l'affichage final.
### 2. Lacommunication radio-fréquence :
Les différentes composantes de notre projet etant fixes , les connections utilisées auraient pu être réalisées de façcon filaire. Toutefois afin de respecter les contraites du cours , nous allons mettre en place un connexion Bluetooth dont nous avons étudié le fonctionnement auparavant . Cette connexion servira d'intermédiaire entre le traitement et l'affichage des données.
### 3. Opérer une transformée de Fourier rapide sur lesignal d'entrée:
Nous devons réaliser une FFT sur un signal provenant de différentes sources numériques (fichier audio) et analogiques (micro). C'est à ce moment que nous avons pris la décision dans un premier temps de réaliser une FFT sur le logiciel Processing (sur pc) et de revenir à un traitement unique sur Arduino plus tard pour des raisons techniques . Nous avions un doute quant à la capacité d'un Arduino à effectuer seul cette FFT. 

## Le matériel
Une grande partie du matériel necessaire à la réalisation de notre projet etait déjà à notre disposition parmi :
- [x] Arduino mega 

![Arduino Mega](Images/mega.jpg)

- [x] Une allimentation filaire
- [x] Ecran led Adafruit Industries 32*64

![Ecran LED](/Images/ecran.jpg)

- [x] Un ordinateur portable
- [x] Un micro type ky-037

![Micro](/Images/kymic.jpg)

- [x] Une puce BT HC-06

![BT](/Images/hc06.jpg)

Des éléments mineurs à acheter : 
- [ ] Une boite afin de contenir tous les élément de notre projet 
- [ ] De la colle à bois
- [ ] Du scotch double face isolant

# Recherches :
## L'état de l'art

## Dans notre contexte

# Déroulement :

# Rendu :

















