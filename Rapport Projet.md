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
  
2. **Etablissement du cahier des charges** 
   - Les fonctions
   - Le materiel

3. **Recherches** 
   - Etat de l'art
   - Dans notre contexte
  
4. **Déroulement**
   - Séance 1 
   - ...
  
5. **Rendu**
   - Comparaison au cahier des charges
   - Améliorations possibles 
   - Ouverture à d'autres applications 
   
6. **Contributions et remerciements**

# Motivations :

## Pourquoi ce projet ?
### La puce **Arduino** :
Dans le cadre du cours d'electronique avec Arduino , nous avons l'occasion de faire preuve de créativité dans un sujet libre utilisant les capacités que nous offre Arduino et ses composants . Une carte Arduino est une puce programmable possédant au minima des entrées/sorties numériques/analogiques et une prise USB. Elle fonctionne selon un principe simple : un signal reçu depuis une entrée déclenche une ou des actions. Il est possible d'y connecter une batterie d'appareils capable d'acquérir des données (capteurs) et de moyens permettants une action (led, moteurs etc...).
Dans notre cas , nous simplifierons le fonctionnement de la carte Arduino selon le principe suivant:
^ **Réception --> Traitement --> Action**

### Les contraintes :
Malgré la certaine liberté dont nous disposons, nous sommes tenus de respecter les contraintes suivantes :

### Idée et intérêts personnels :
Il s'est passé deux semaines entre le moment où nous avons formé les binômes et fixé le sujet. Nous avions une multitude d'idées parmi lesquelles : ...  
Toutefois nous avons rencontré un certain nombre de difficultés techniques qui semblaient compromettre une à une nos idées.
La confirmation de notre projet nous est venue avant tout de nos interets respectifs. Comment concilier musique , probabilité et programmation ? En nous penchant sur les vastes capacités que nous offre arduino nous avons fini par nous accorer sur la création d'un afficheur de fréquence tel qu'on en trouve sur n'importe quel équaliseur en ayant une vague notion de ce qu'est la FFT (merci l'utilisation de l'osciloscope ). 
## A quoi ça sert ?

### Utilité au quotidien
Le premier exemple qui nous est venu , étant tous les deux musiciens est le fonctionnement d'un accordeur. Un son émis par l'instrument est capté par un micro (sonore ou à vibrations) , analysé en fréquences et un affichage de la fréquence actuelle constitue la note jouée. C'est le même principe lorsqu'il s'agit de rêgler l'équibrage des différentes enceintes d'un home cinéma par exemple. La mesure des différentes fréquences permet d'avoir une balance entre grave et aigus adaptés au type de divertissement. D'autres applications dans les sciences existent ...  

## Comment ?
### Les ressources
Sans avoir étudié en détail les caractéristiques du système , nous savons qu'il nous faut un capteur pour l'acquisition du son (un simple micro fait l'affaire) , un boitier d'acquisition (l'Arduino) , un logiciel de traitement et enfin un écran .
### Le principe
Le coeur du projet repose sur un opérateur qu'est la transformée de fourier rapide : ...
Problématique : gourmande en ressources 






















