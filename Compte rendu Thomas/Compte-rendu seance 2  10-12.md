Compte-rendu séance 2

Le 10/12 :

Activités : 

Etablissement de la connexion BT entre le téléphone (application BT electronics vue en TD) et l’écran LED via la carte Arduino Méga. 

Détail :

Nous avons utilisé une carte BT HC-06 reliée aux ports communication de notre carte Méga 2560. Le paramétrage du module est assuré à l’aide du programme donné en td (GitHub Projet Arduino/commBT). Nous avons rencontré un problème de rapidité de communication entre le téléphone et notre carte, nous avons donc augmenté la vitesse de communication à 38400 (initialement à 9600) ce qui atténue la latence rencontrée. 

Test : 

Nous avons utilisé une fonction de la librairie fournie avec l’écran LED afin d’afficher un cercle dont nous avons fait varier en temps réel le rayon à l’aide d’un curseur sur l’application BT electronics (GitHub Projet Arduino/led34X64). Le résultat est bon, la connexion est établie. La partie « électronique » de notre projet étant relativement simple nous allons pouvoir attaquer dès la prochaine séance le code et une application de la transformée de Fourier dont nous avons déjà trouvé plusieurs bibliothèques. 
Nous n’avions pas à disposition d’appareil permettant la capture vidéo, notre seul smartphone étant dédié à l’usage de l’application BT electronics, nous apporterons donc à la prochaine séance de quoi ajouter la vidéo au compte-rendu .
