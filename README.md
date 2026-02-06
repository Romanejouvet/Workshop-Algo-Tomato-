# 🐣 S1 | Prog: Workshop 


# Exo 1- Ne garder que le vert 
<img src="IMAGES/exo1.png"> 

# Exo 2- Echanger les canaux
<img src="IMAGES/exo2.png" > 

# Exo 3- Noir et Blanc 
<img src="IMAGES/exo3.png" > 

# Exo 4- Négatif
<img src="IMAGES/exo4.png" > 

# Exo 5- Dégradé
<img src="IMAGES/exo5.png" > 

# Exo 6- Miroir  
<img src="IMAGES/exo6.png" > 

# Exo 7- Image bruitée 
<img src="IMAGES/exo7.png" > 

# Exo 8- RGB Split
<img src="IMAGES/exo8.png" > 

# Exo 9- Disque 
<img src="IMAGES/exo9.png" > 

# Exo 10- Cercle
<img src="IMAGES/exo10.png" > 

# Exo 11- Rosace
<img src="IMAGES/exo11.png" > 

Pour la rosace je n'ai pas fait se répeter les cercles a partir du meme point mais j'ai plutot decoupé le cercle en N angles reguliers, ce qui répartit les cercles uniformement sur un cercle. 

# Exo 12- Mosaique
<img src="IMAGES/exo12.png" > 

# Exo 13- Mosaique miroir 
<img src="IMAGES/exo13.png" > 

Fonctionnement: 

Chaque pixel (x, y) calcule sa position dans la cellule (ox, oy) avec %, et selon la cellule (cell_x + cell_y) % 2 == 1, on applique un miroir horizontal (ox = w - 1 - ox).

Pour les soucis rencontrés: 

Je n'avais pas mis au début oy = y % h pour bien répéter les lignes, et il faut aussi recalculer les coordonnées du miroir par cellule car sinon l’effet se déforme.



# Exo 14- Tri de pixels 
<img src="IMAGES/exo14.png" > 

Ce n'est pas vraiment un tri de pixel mais plutot un glitch vertical aléatoire, le code est donc simplifié par rapport au tri de pixels.


# Exo 15- Vortex
<img src="IMAGES/exo15.png" > 

Fonctionnement: 

On calcule la distance au centre, et c'est cette distance qui va déterminer un angle de rotation.
Ensuite on calcule la nouvelle position du pixel après la rotation, et on copie la couleur correspondante depuis l’image originale.



# Exo 16- Convolutions
<img src="IMAGES/exo16.png" > 


Fonctionnement: 


Pour chaque pixel, on va regarder ses pixels voisins dans un carré, et on va additionner les couleurs. Ensuite on fait la moyenne, et on remplace la couleur du pixel par cette moyenne, ce qui crée un effet de flou a la fin (meme si il se voit pas beaucoup).


Soucis rencontrés: 

je n'avais pas pensé a copier l'image originale, et ducoup le flou s'aculume. J'avais aussi oublié de vérifier les bornes pour éviter d'accéder a des pixels en dehors de l'image. 





