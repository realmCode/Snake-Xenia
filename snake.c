#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define HEIGHT 20
#define WIDTH 40
#define FILENAME "scoreboard.txt"

int snakex[100];
int snakey[100];
char mattrix[HEIGHT][WIDTH]; // string mattrix
// int* cmattrix[HEIGHT][WIDTH]; // integer matrix
int lensnake = 2;

int fruitx = WIDTH / 2 + 5;
int fruity = HEIGHT / 2 + 5;

int key = 3; // by default snake goes upward
int gameover = 0;
int tkey;

FILE *scoreboard;
struct player
{
    char name[50];
    int score;
};
int find(int x, int arr[])
{
    int lmn = 0;
    for (int i = 0; i < lensnake; i++)
    {
        if (x == arr[i])
        {
            return 1;
        }
    }
    return lmn;
}
int findstruct(char x[50], struct player arr[], int n)
{
    int lmn = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(x,arr[i].name)==0)
        {
            return 1;
        }
    }
    return lmn;
}

int input()
{
    if (kbhit())
    {
        tkey = tolower(getch());
        if (tkey != key)
        {
            switch (tkey)
            {
            case 'a':
                if (key != 2)
                    key = 1;
                break;
            case 'd':
                if (key != 1)
                    key = 2;
                break;
            case 'w':
                if (key != 4)
                    key = 3;
                break;
            case 's':
                if (key != 3)
                    key = 4;
                break;
            case 'x':
                gameover = 1;
                break;
            }
        }
    }
}

int updatehead()
{
    // here ishifnft the body segment
    for (int l = lensnake - 1; l > 0; l--)
    {
        snakex[l] = snakex[l - 1];
        snakey[l] = snakey[l - 1];
    }
    // Update the head position based on the direction (key)
    switch (key)
    {
    case 1: // left
        snakex[0]--;
        break;
    case 2: // right
        snakex[0]++;
        break;
    case 3: // up
        snakey[0]--;
        break;
    case 4: // down
        snakey[0]++;
        break;
    default:
        break;
    }

    if (snakex[0] == fruitx && snakey[0] == fruity)
    {
        snakex[lensnake] = snakex[lensnake - 1];
        snakey[lensnake] = snakey[lensnake - 1];
        lensnake++;
        fruitx = rand() % WIDTH - 1;
        // i dont know why this skibbi not generating fruit at proper point
        while (fruitx == 0 || find(fruitx, snakex))
        {
            fruitx = rand() % WIDTH - 1;
        }
        fruity = rand() % HEIGHT - 1;
        while (fruity == 0 || find(fruity, snakey))
        {
            fruity = rand() % HEIGHT - 1;
        }
    }
}

int initialise()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            mattrix[i][j] = ' ';
        }
    }

    snakex[0] = WIDTH / 2 - 1;
    snakey[0] = HEIGHT / 2 - 1;
    snakex[1] = snakex[0];
    snakey[1] = snakey[0] + 1;
    lensnake = 2;
    // snakex0 = snakex[0];
    // snakey0 = snakey[0];

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            if (fruitx == j && fruity == i)
            {
                mattrix[i][j] = '*';
            }

            if (j == 0 || j == WIDTH - 1)
            {
                mattrix[i][j] = '#';
            }
            if (i == 0 || i == HEIGHT - 1)
            {
                mattrix[i][j] = '#';
            }
            for (int l = 0, m = 0; l < lensnake && m < lensnake; l++, m++)
            {
                if (j == snakex[l] && i == snakey[m])
                {
                    if (l == 0)
                    {
                        mattrix[i][j] = 'O';
                    }
                    else
                    {
                        mattrix[i][j] = 'o';
                    }
                }
            }
        }
    }
}

int printmattrix()
{

    system("cls"); // remove old printed output to print new and keey game top of console;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", mattrix[i][j]);
        }
        printf("\n");
    }
}

int reinitialisemattrix()
{
    // printf("(%i, %i)\n", fruitx, fruity);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            mattrix[i][j] = ' ';
        }
    }
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            if (fruitx == j && fruity == i)
            {

                mattrix[i][j] = '*';
            }

            if (j == 0 || j == WIDTH - 1)
            {
                mattrix[i][j] = '#';
            }
            if (i == 0 || i == HEIGHT - 1)
            {
                mattrix[i][j] = '#';
            }
            for (int l = 0; l < lensnake; l++)
            {
                if (j == snakex[l] && i == snakey[l])
                {
                    if (l == 0)
                    {
                        mattrix[i][j] = 'O';
                        if (snakex[0] == 0 || snakex[0] == WIDTH - 1 || snakey[0] == 0 || snakey[0] == HEIGHT - 1)
                        {
                            mattrix[i][j] = 'X';
                            gameover = 1;
                        }
                    }
                    else
                    {
                        mattrix[i][j] = 'o';
                    }
                }
            }
        }
    }
}

int addScore(const char *playerName, int score)
{
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }
    fprintf(file, "%s %d\n", playerName, score);
    fclose(file);
}

int highscore(const char *playerName)
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    char currentPlayer[50];
    int score, highestScore = -1;

    while (fscanf(file, "%s %d", currentPlayer, &score) == 2)
    {
        if (strcmp(currentPlayer, playerName) == 0)
        {
            if (score > highestScore)
            {
                highestScore = score;
            }
        }
    }
    fclose(file);

    return highestScore;
}
int sort(struct player arr[], int n)
{
    struct player temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].score < arr[j + 1].score)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int displayscore()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    char names[100][50];
    char currentPlayer[50];
    int score, highestScore = -1;
    struct player arr[100];

    int i = 0;
    while (fscanf(file, "%s %d", currentPlayer, &score) == 2)
    {
        if (!findstruct(currentPlayer,arr, i))
        {
            strcpy(arr[i].name, currentPlayer);
            arr[i].score = highscore(currentPlayer);
            i++;
        }
    }
    sort(arr, i);
    system("cls");
    printf("\n\nLEADER BOARDS\n\n");
    for (int x = 0; x < i; x++)
    {
        printf("%i. %s - %i\n", x + 1, arr[x].name, arr[x].score);
    }

    fclose(file);
}

int main()
{
    int choice;
    char playerName[50];
    int score;

    do
    {
        printf("\nSNAKE XENIA\n");
        printf("1. Start \n");
        printf("2. Display Scores \n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter player name: ");
            scanf("%s", playerName);
            initialise();
            printmattrix();
            while (!gameover)
            {
                input(); // take keyboard input
                Sleep(100);
                updatehead(); // update the direction of head of snake
                reinitialisemattrix();
                printmattrix();
            }
            Sleep(1000);
            system("cls");
            score = lensnake;
            printf("\n\nGAME OVER :/\n\n");
            addScore(playerName, score);
            printf("PLAYER %s\nCurrent Score - %i\nHigh score - %i\n\n", playerName, score, highscore(playerName));
            initialise();
            break;
        case 2:
            displayscore();
        case 3:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
