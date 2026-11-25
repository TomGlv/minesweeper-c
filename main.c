#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 10
#define MINES 10
#define CELL_VIDE ' '
#define CELL_MINE '*'

char plateau[TAILLE][TAILLE];
char plateauCache[TAILLE][TAILLE];
int cellulesRevelees = 0;

void initialiserPlateau() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j] = CELL_VIDE;
            plateauCache[i][j] = CELL_VIDE;
        }
    }
}

void afficherPlateau() {
    printf("   ");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAILLE; j++) {
            printf("%c ", plateau[i][j]);
        }
        printf("\n");
    }
}

void placerMines() {
    srand(time(NULL));
    int count = 0;
    while (count < MINES) {
        int x = rand() % TAILLE;
        int y = rand() % TAILLE;
        if (plateauCache[x][y] != CELL_MINE) {
            plateauCache[x][y] = CELL_MINE;
            count++;
        }
    }
}

void calculerChiffres() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (plateauCache[i][j] == CELL_MINE) {
                continue;
            }
            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = i + dx;
                    int ny = j + dy;
                    if (nx >= 0 && nx < TAILLE && ny >= 0 && ny < TAILLE && plateauCache[nx][ny] == CELL_MINE) {
                        count++;
                    }
                }
            }
            plateauCache[i][j] = count + '0';
        }
    }
}

int revelerCellule(int x, int y) {
    if (x < 0 || x >= TAILLE || y < 0 || y >= TAILLE || plateau[x][y] != CELL_VIDE) {
        return 0;
    }
    plateau[x][y] = plateauCache[x][y];
    cellulesRevelees++;
    if (plateauCache[x][y] == '0') {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                revelerCellule(x + dx, y + dy);
            }
        }
    }
    return 1;
}

int verifierVictoire() {
    return cellulesRevelees == TAILLE * TAILLE - MINES;
}

int main() {
    initialiserPlateau();
    placerMines();
    calculerChiffres();

    int x, y;
    while (1) {
        afficherPlateau();
        printf("Entrez la ligne et la colonne (ex: 3 4) ou 'q' pour quitter : ");
        char action;
        scanf(" %c", &action);
        if (action == 'q') {
            printf("Quitting game.\n");
            break;
        }
        scanf("%d %d", &x, &y);
        if (plateauCache[x][y] == CELL_MINE) {
            printf("Vous avez touché une mine ! Partie terminée !\n");
            break;
        }
        if (!revelerCellule(x, y)) {
            printf("Cellule déjà révélée ou hors limites !\n");
        }
        if (verifierVictoire()) {
            printf("Félicitations ! Vous avez gagné !\n");
            break;
        }
    }

    return 0;
}
