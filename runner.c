#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define ESC 27
#define SPACE ' '

int x = 0, y = 0;

char character[9];
char map[4][1000];
int position = 0;
int j=4;
// "■ ►"

void displayMap() {
    for (int i = 0; i < sizeof(map)/sizeof(map[0]); i++) {
        if (i==3) {
            printf("%s", character);
            if (y>0) {
                printf("\n\n");
                if (j<=0) y=0;
                else j--;
            }
        }   
        printf(map[i]);
    }
}

void renderGame() {
    system("cls");
    for (int i = 0; i < sizeof(map)/sizeof(map[0]); i++) {
        strcpy(map[i],map[i]+1);
    };
    printf("\n\n\n\n\n");
    displayMap();
}

void loadMap() {
    strcat(map[0], "                             \n");
    strcat(map[1], "                             \n");
    strcat(map[2], "                             \n");
    // char obstacles[][2] = {{'[', '}'}, {' ', ' '}, {'{', ']'}, {'@'}, {' ', ' '}, {' ', ' '}, {' '}, {' ', ' '}};
    char obstacles[][2] = {{'@'}};
    for (int i = 0; i < 12; i++) {
        strcat(map[3], obstacles[rand() % sizeof(obstacles)/sizeof(obstacles[0])]);
        if (i%2==0) strcat(map[3], "           ");
    }
    displayMap();
}

int main() {
    printf("PRESS SPACE TO JUMP | ESC TO EXIT\n");
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(console_color, 2);

    Sleep(1500);
    srand(time(0));
    bool gameRunning = true;
    strcpy(character, " _o_\n /|");
    loadMap();
    
    while (gameRunning) {
        if (kbhit()) {
            char c = getch();
            switch (c) {
                case ESC:
                    gameRunning = false;
                    SetConsoleTextAttribute(console_color, 07);
                    break;
                case SPACE:
                    y+=1;
                    j=4;
            }
        }
        renderGame();
        Sleep(200); // windows.h
        position+=1;
        if (position > 50) {SetConsoleTextAttribute(console_color, 07);return printf("\n=================\nYOU WON!\n=================");}
        if (map[3][0]!=' ' && y==0) {
            displayMap();
            printf("\nYOU LOST!");
            gameRunning=false;
            SetConsoleTextAttribute(console_color, 07);
        };
    }
    return 0;
}