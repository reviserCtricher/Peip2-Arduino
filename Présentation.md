# Présentation projet Arduino 2018/2019
## Introduction :
### 1. Recherche et but du projet :
- Intérets personnels 
- Faisabilité et contexte 
### 2. Cahier des charges :
- Les fonctions 
- Fonctions + algo
## Le déroulement :
- Branchements écran + BT (site adafruit CE)  (Thomas)
- Recherches FFT (Théo) + CDC
- Test écran (programme + photo) + BT affichage cercle telephone
- PB techniques , explication contrainte arduino , que processing (etat de l'art) . Processing marche seance 3 , pas bon affichage , pb source in (original micro pas fichier , librairie minim)
- BT + Processing , fin liaison filaire seance 4. Centrage affichage processing (développé pour écran 16*32) . Difficultés de compréhension pour adapter.  Début recherche solution FFT via arduino . Aucune source fiable. Essai traduction processing vers arduino (arduinoSolo) pdt deux séances , échec. 
- PB envoi données , arduino pas adapté . Encodage + connection BT ,traduction telephone MIT APP INVENTOR. Fin de séance Masson micro ky -037. Début redaction spectrum.ino , fft fixe.
- Micro cassé (test simple led) , changement micro , test concuant . Utilisation 2 arduino 2 ecran. Bidouillage analog * 50 . S6
- Reparation alim et terre . Module BT non isolé (ancien model grillé) , perte de temps . Changement module . Comparaison 2 versions , 20hz->20khz. Spectrum traite des plages de 400 hz(modulo librairie) , processing traite tout et mieux. Masson propose solution augmenter fréquence pour micro . Problème prescaleur et librairie. Boite. Projet fini (CDC) S7.
- Boite , affichages fun , applications ILLIMITE.

## Conclusion et apport

