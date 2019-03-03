Decottignies Thomas
Projet Arduino 2018/2019

# Compte rendu seance 8:

## Activites:
Modifications de l'affichage et création de fonctions permettant d'améliorer l'esthétique en utilisant le module de FFT fixe. 

## Detail: 
Afin de tirer pleinement parti de nos avancées concernant la FFT à point fixe , nous avons commencé à nous pencher sur une meilleure 
utilisation des possibilités d'affichage que nous offre l'ecran led. Nous avons apporté quelques modifications au programme "Spectrum" qui 
ne consomme que trs peu deressources de l'arduino pour pratiquer la FFT et dispose donc d'une plus grande souplesse pour des fonctions 
d'affichage plus complexes. Pour le moment , nous avons développé deux nouveaux styles d'affichage basés sur des cercles :

- Dans le premier cas l'arduino affiche 4 cercles représentant des "secteurs" de fréquences . A chaque fois que la fréquence captée
se trouve dans la plage concernée par le cercle, le rayon de celui-ci varie en fonction de l'amplitude. Afin d'ameliorer les performances , 
seul le maximum de chaque plage de fréquence est affiché. 

- Dans le second cas , nous avons conservé le principe du précédent mais avons choisi d'afficher les cercles sur deux écrans différents 
en utilisant deux vesrions de notre programme sur deux arduino chargés de traiter chacun une partie du spectre audible. 

Les applications possibles sont infinies dans le sens où elles ne sont que des "skins" que l'on peut créer et appliquer en fonction des 
goûts de l'utilisateur. Nous en dvelopperons d'autres à l'avenir . 

[Quelques photos](https://photos.app.goo.gl/RF9F1LVxFgLvQxwt5)
