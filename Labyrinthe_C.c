#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//--------------------------------------------------------------CREATION-DES-VARIABLES-----------------------------------------------------------------------

char direct;
int stop;
int continu = 0;


int ligne;
int colonne;

int bord = 219;
int lignes = 45;
int pas_utiliser = 64;
int joueur = 177;
int utilise_move = 178;
int arriver = 146;

bool nord;
bool sud;
bool est;
bool west;

void affiche_tableau(int tableau[][colonne]);



int liste_passage[10000][2];

int x = 1;
int y = 1;

int taille = 1;

int reponse;

//--------------------------------------------------------------CREATION-DES-FONCTIONS-----------------------------------------------------------------------


void creer_lab(int tableau[][colonne]){//genere le labyrinthe en tant que quadrillage
    for(int i=0;i<ligne;i++){
        for(int j=0;j<colonne;j++){
            if (i==0 || i==ligne-1 || j==0 || j==colonne-1){
                tableau[i][j] = 8;
            }
            else if(i%2==1 && j%2==1) {
                tableau[i][j] = 1;
            }
            else {
                tableau[i][j] = 9;
            }
        }
    }
    tableau[1][1] = 2;
    tableau[ligne-2][colonne-2] = 4;
}


bool verif_mur(int tableau[][colonne]){//verifie si un mouvement d'une direction est possible (pour detruire un mur)
    if (tableau[x-1][y]==9 && tableau[x-2][y]!=5 && tableau[x-2][y]!=2 && tableau[x-2][y]!=4){
        nord = true;
    }
    if (tableau[x+1][y]==9 && tableau[x+2][y]!=5 && tableau[x+2][y]!=2/* && tableau[x+2][y]!=4*/){
        sud = true;
    }
    if (tableau[x][y+1]==9 && tableau[x][y+2]!=5 && tableau[x][y+2]!=2 && tableau[x][y+2]!=4){
        est = true;
    }
    if (tableau[x][y-1]==9 && tableau[x][y-2]!=5 && tableau[x][y-2]!=2 && tableau[x][y-2]!=4){
        west = true;
    }
    if (nord == true || sud == true || est == true || west == true){
        return true;
    }
    else {
        return false;
    }
}

void north(int tableau[][colonne]){//mouvement haut
    x -= 2;
    tableau[x+1][y] = 5;
    tableau[x][y] = 5;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void south(int tableau[][colonne]){//mouvement bas
    x += 2;
    tableau[x-1][y] = 5;
    tableau[x][y] = 5;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void east(int tableau[][colonne]){//mouvement droite
    y += 2;
    tableau[x][y-1] = 5;
    tableau[x][y] = 5;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void ouest(int tableau[][colonne]){//mouvement gauche
    y -= 2;
    tableau[x][y+1] = 5;
    tableau[x][y] = 5;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void chemin(int tableau[][colonne]){//choisi un chemin aleatoire si c'est possible
    int aleatoire = rand() % 4;
    if (aleatoire == 0) {
        if (nord == true){
            north(tableau);
        }
    }
    if (aleatoire == 1) {
        if (sud == true){
            south(tableau);
        }
    }
    if (aleatoire == 2) {
        if (est == true){
            east(tableau);
        }
    }
    if (aleatoire == 3) {
        if (west == true){
            ouest(tableau);
        }
    }
}

void affiche_tableau(int tableau[][colonne]){ //affiche le tableau
    for (int i=0;i<ligne;i++){
        for (int j=0;j<colonne;j++){
            if (tableau[i][j] == 8){
                printf("%c%c",bord,bord);
            }
            else if (tableau[i][j] == 9){
                printf("%c%c",bord,bord);
            }
            else if (tableau[i][j] == 5){
                printf("  ");
            }
            else if (tableau [i][j] == 10){
                printf("  ");
            }
            else if (tableau[i][j] == 1){
                printf("%c%c",pas_utiliser,pas_utiliser);
            }
            else if (tableau [i][j] == 2){
                printf("%c%c",joueur,joueur);
            }
            else if (tableau [i][j] == 4){
                printf("%c%c",arriver,arriver);
            }
            else if (tableau [i][j] == 3){
                printf("%c%c",utilise_move,utilise_move);
            }
        }
        printf("\n");
    }
}


//----------------------------------------------------------------FONCTION-COMPLETER-------------------------------------------------------------------------
int nombre = 0;

int liste_passage[10000][2];

bool verif_pass(int tableau[][colonne]){//verifie si un mouvement d'une direction est possible
    if (tableau[x-1][y]==5){
        nord = true;
    }
    if (tableau[x+1][y]==5){
        sud = true;
    }
    if (tableau[x][y+1]==5){
        est = true;
    }
    if (tableau[x][y-1]==5){
        west = true;
    }
    //printf("%d\n,%d\n,%d\n,%d\n\n\n",nord,sud,est,west);
    if (nord == true || sud == true || est == true || west == true){
        return true;
    }
    else {
        return false;
    }
}

void north_move(int tableau[][colonne]){//mouvement haut
    x -= 1;
    tableau[x][y] = 3;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void south_move(int tableau[][colonne]){//mouvement bas
    x += 1;
    tableau[x][y] = 3;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void east_move(int tableau[][colonne]){//mouvement droite
    y += 1;
    tableau[x][y] = 3;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void ouest_move(int tableau[][colonne]){//mouvement gauche
    y -= 1;
    tableau[x][y] = 3;
    liste_passage[taille][0] = x;
    liste_passage[taille][1] = y;
    taille += 1;
}

void passage(int tableau[][colonne]){//choisi un chemin en suivant un paterne definie
    if (est == true){
        east_move(tableau);
    }
    else if (sud == true){
        south_move(tableau);
    }
    else if (west == true){
        ouest_move(tableau);
    }
    else if (nord == true){
        north_move(tableau);
    }
}

void liste_pass(){//reinicialise la liste de retour en arriere
    for(int a=0;a<=99;a++){
        for(int b=0;b<=1;b++){
            liste_passage[a][b] = 00;
        }
    }
}

void complete(int tableau[][colonne]){ //Complete le labyrinthe
    x=1;
    y=1;
    liste_pass();
    liste_passage[0][0] = x;
    liste_passage[0][1] = y;
    taille = 0;
    while (nombre!=100000){
        nord = false;
        sud = false;
        est = false;
        west = false;
        //affiche_tableau(tableau);
        nombre += 1;
        if (tableau[x-1][y]==4 || tableau[x+1][y]==4 || tableau[x][y-1]==4 || tableau[x][y+1]==4){
            break;
        }
        if (verif_pass(tableau)==false){
            tableau[x][y] = 10;
            liste_passage[taille][0] = 00;
            liste_passage[taille][1] = 00;
            taille -= 1;
            x = liste_passage[taille][0];
            y = liste_passage[taille][1];
        }
        else{
            verif_pass(tableau);
        }
        passage(tableau);
    }
}

//---------------------------------------------------------------PROGRAMME-PRINCIPAL-------------------------------------------------------------------------
void main(){
    printf("Bonjour,\n");
    printf("Voici mon labyrinthe fait en C.\n");
    printf("Tout d'abord, vous devez donner les dimensions du labyrinthe.\n");
    printf("Ensuite, il y a 2 modes, manuel et automatique.\n");
    printf("Le mode manuel se joue avec z (haut), q (gauche), s (bas) et d (droite).\n");
    printf("Le mode automatique fera le labyrinthe seul.\n\n");

    printf("Veuillez entrer le nombre de lignes, impaire, superieur a 5 : ");
    scanf("%d",&ligne);
    printf("\n");
    printf("Veuillez entrer le nombre de colonnes, impaire, superieur a 5 : ");
    scanf("%d",&colonne);
    printf("\n");


    srand( time( NULL ) );

    int tableau[ligne][colonne];
    creer_lab(tableau);

//random------------------------------------------------------------
    //int x = rand() % 9;
    //int y = rand() % 9;

//    if (x==0){
//        x++;
//    }
//    if (y==0){
//        y++;
//    }

    int nb = 0;

    liste_passage[0][0] = x;
    liste_passage[0][1] = y;



    //true = 1

//------------------------------------------------------------GENERATION-DU-LABYRINTHE-----------------------------------------------------------------------
    while(nb != 1){
        nord = false;
        sud = false;
        est = false;
        west = false;

        if(liste_passage[taille][0]==1 && liste_passage[taille][1]==1 && verif_mur(tableau)==false){
            break;
        }
        if(liste_passage[taille-1][0] && liste_passage[taille-1][1]==0){
            break;
        }
        if (verif_mur(tableau)==false){
            liste_passage[taille][0] = 00;
            liste_passage[taille][1] = 00;
            taille -= 1;
            x = liste_passage[taille][0];
            y = liste_passage[taille][1];
        }
        else{
            verif_mur(tableau);
        }
        chemin(tableau);
    }
    tableau[ligne-2][colonne-2] = 4;
    affiche_tableau(tableau);
    printf("\n\n");
    printf("\n\n");

    printf("Veuillez choisir le mode de jeu, 1 manuel, 2 automatique : ");
    scanf("%d",&reponse);

    if (reponse==1){
        x = 1;
        y = 1;
        while (continu==0){
            if (stop==10000){
                break;
            }
            switch(direct){
            case 'z':
                if (tableau[x-1][y]==5){
                    x--;
                    tableau[x][y] = 2;
                    printf("Vous avancez...\n");
                }
                else if (tableau[x-1][y]==4){
                    x--;
                    continu = 1;
                }
                else if (tableau[x-1][y]==9 || tableau[x-1][y]==8){
                    printf("Un mur...\n");
                }
                break;

            case 'q':
                if (tableau[x][y-1]==5){
                    y--;
                    tableau[x][y] = 2;
                    printf("Vous avancez...\n");
                }
                else if (tableau[x][y-1]==4){
                    y--;
                    continu = 1;
                }
                else if (tableau[x][y-1]==9 || tableau[x][y-1]==8){
                    printf("Un mur...\n");
                }
                break;

            case 's':
                if (tableau[x+1][y]==5){
                    x++;
                    tableau[x][y] = 2;
                    printf("Vous avancez...\n");
                }
                else if (tableau[x+1][y]==4){
                    x++;
                    continu = 1;
                }
                else if (tableau[x+1][y]==9 || tableau[y+1][x]==8){
                    printf("Un mur...\n");
                }
                break;

            case 'd':
                if (tableau[x][y+1]==5){
                    y++;
                    tableau[x][y] = 2;
                    printf("Vous avancez...\n");
                }
                else if (tableau[x][y+1]==4){
                    y++;
                    continu = 1;
                }
                else if (tableau[x][y+1]==9 || tableau[x][y+1]==8){
                    printf("Un mur...\n");
                }
                break;
            default:
                affiche_tableau(tableau);
            }
            stop+=1;
            printf("Veuillez choisir une direction :\n");
            scanf("%c",&direct);
        }
    printf("Victoire !\n");
    }
    else if (reponse==2){
        complete(tableau);
        affiche_tableau(tableau);
    }
    else {
        printf("Choisissez entre 1 et 2.");
    }
}
