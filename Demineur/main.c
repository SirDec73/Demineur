#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
//Créer deux structures représentant la grille(Grid) et une case (Tile)
void ClearBuffer()
{
    char c = getchar();;
    while (c != '\n') {
        c = getchar();
    }
}

// Fonction qui demande une entre entiere encadre par des bornes Min et Max
int AskIntInRange(const char* text, int Value, int Bmin, int Bmax) {
    int iError = 0;

    //Tant que la valeur rentre n'est pas un entier ou qu'il n'est pas compris dans les borns
    while (iError == 0) {
        printf(text);

        // Verifier que l'entre est un int
        iError = scanf_s("%d", &Value);
        if (iError == 1) {
            //Si il est dans les bornes
            if (Value <= Bmax && Value >= Bmin) {
                printf("\n");
                return Value;
            }
            //Si il n'est pas dans les bornes
            else {
                printf("ERREUR Hors bornes \nEntree entre %d et %d : \n", Bmin, Bmax);
                iError = 0;
            }
        }
        // reset buffer du scanf_s
        ClearBuffer();
    }
}
void CreatMine(int* MineY, int* MineX,int SizeHeight, int SizeWidth){
	*MineY = rand() % SizeHeight;
	*MineX = rand() % SizeWidth;
}
/*
void Affichage_Player(int Height, int Width, int Tile) {
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++) {
            if (Tile[i * Width + j].hidden == 0) {
                printf("|%d|", Tile[i * Width + j].content);
            }
            else if (Tile[i * Width + j].flag == 1) {
                printf("|P|");
            }
            else { printf("| |"); }
        }
        printf("\n");
    }
}*/;

typedef struct Tile{
    int x;
    int y;
    int content;
    int hidden;
    int flag;
}Tile;

typedef struct Grid{
	int Width;
	int Height;
    Tile* Tile;
}Grid;

//Créer une fonction permettant d’initialiser la grille et chaque case 
int main() {
    int ChoiceX = 0,ChoiceY = 0,flag = 0;
	int MineY = 0;
	int MineX = 0;
    // Demander un int pour la taille
    int SizeWidth = 0;
    SizeWidth = AskIntInRange("Choose the Width of the Grid : ", SizeWidth,1,50);
    int SizeHeight = 0;
    SizeHeight = AskIntInRange("Choose the Height of the Grid : ", SizeHeight, 1, 50);
    // Generer des cases en fonction de la taille de la grid

    Tile* AllTiles = (Tile*)malloc(sizeof(Tile) * SizeHeight * SizeWidth);
    if (AllTiles == NULL) {
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < SizeHeight; i++)
    {
		for (int j = 0; j < SizeWidth; j++) {
			AllTiles[i * SizeWidth + j].x = j;
			AllTiles[i * SizeWidth + j].y = i;
            AllTiles[i * SizeWidth + j].content = 0;
            AllTiles[i * SizeWidth + j].hidden = 1;
            AllTiles[i * SizeWidth + j].flag = 0;
		}
    }
    // Generer la grid
    Grid Grid;
    Grid.Height = SizeHeight;
    Grid.Width = SizeWidth;
    Grid.Tile = AllTiles;
    // Generer les mines
    for (int i = 0; i < floor((SizeHeight * SizeWidth) * 0.2) ;i++) {
        do {
            CreatMine(&MineY, &MineX, SizeHeight, SizeWidth);
        } while (AllTiles[MineY * SizeHeight + MineX].content == 9);
		AllTiles[MineY *SizeHeight+MineX].content = 9;
    }
    // Afficher la grille DEV
	for (int i = 0; i < Grid.Height; i++)
	{
        for (int j = 0; j < Grid.Width; j++) {
            printf("|%d|", Grid.Tile[i * Grid.Width + j].content);
        }
        printf("\n");
    }
    // Afficher la grille PLAYER
    //Affichage_Player(Grid.Height, Grid.Width, Grid.Tile);
	for (int i = 0; i < Grid.Height; i++)
	{
		for (int j = 0; j < Grid.Width; j++) {
			if (Grid.Tile[i * Grid.Width + j].hidden == 0) {
				printf("|%d|", Grid.Tile[i * Grid.Width + j].content);
			}
			else if (Grid.Tile[i * Grid.Width + j].flag == 1) {
				printf("|P|");
			}
			else { printf("| |"); }
		}
		printf("\n");
	}

    while (1) {
        flag = AskIntInRange("Do you want put a flag ? yes = 1 | no = 0 : ", flag, 0, 1);
        ChoiceX = AskIntInRange("Choose X : ", ChoiceX, 1, Grid.Width)-1;
        ChoiceY = AskIntInRange("Choose Y : ", ChoiceY, 1, Grid.Height)-1;
        printf("1 : %d |2 : %d |3 : %d \n", ChoiceX, ChoiceY, flag);
        if (Grid.Tile[ChoiceY * Grid.Height + ChoiceX].hidden == 0) {
            Grid.Tile[ChoiceY * Grid.Height + ChoiceX].flag = 1;
            printf("The tile is already open\n");
        }else if (Grid.Tile[ChoiceY * Grid.Height + ChoiceX].flag == 1 && flag==0) {
            printf("The tile is flaged !\n");
        }else if (Grid.Tile[ChoiceY * Grid.Height + ChoiceX].flag == 1 && flag == 1) {
            Grid.Tile[ChoiceY * Grid.Height + ChoiceX].flag = 0;
            printf("The tile is unflaged !\n");
        }else if (Grid.Tile[ChoiceY * Grid.Height + ChoiceX].flag == 0 && flag == 1) {
            Grid.Tile[ChoiceY * Grid.Height + ChoiceX].flag = 1;
            printf("The tile becomes flaged !\n");
        }else if (Grid.Tile[ChoiceY * Grid.Height + ChoiceX].hidden == 1) {
            Grid.Tile[ChoiceY * Grid.Height + ChoiceX].hidden = 0;
        }
        //Affichage_Player(Grid.Height, Grid.Width, Grid.Tile);
        for (int i = 0; i < Grid.Height; i++)
        {
            for (int j = 0; j < Grid.Width; j++) {
                if (Grid.Tile[i * Grid.Width + j].hidden == 0) {
                    printf("|%d|", Grid.Tile[i * Grid.Width + j].content);
                }
                else if (Grid.Tile[i * Grid.Width + j].flag == 1) {
                    printf("|P|");
                }
                else { printf("| |"); }
            }
            printf("\n");
        }
    }
}
        

// Mettre +1 autour des mines
// Vérifier vide pour tout clear

