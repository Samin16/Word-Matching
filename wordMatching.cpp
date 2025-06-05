#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>

#define screenWidth 1180
#define screenHeight 700
int matrix[5][2];
int mposx, mposy;
bool musicOn = true;

int window = 1;
int chosenFromLeft = -1;
int chosenFromRight = -1;
int arrGreenL[5];
int arrGreenR[5];
int arrRedR[5];
int gamelevel = 1;

int x = 0;
int y = 0;
int r = 255;
int g = 255;
int b = 255;

int showAccuracy = 0;

char s[5];
// char s_1[100];

// char s_2[5];
// char s_3[100];

int dx = 10;
int dy = 10;

void change();
char str[4][20] = {"image\\ptitle.bmp"};
// char ptr[4][20]={"image\\title.bmp"};
int strIndex = 0;
int ptrIndex = 0;

// storing score in file
FILE *score_save;

int score = 0;
int score_1 = 0;
int score_2 = 0;
static int click = 0;
double accuracy_1 = 0;
double accuracy_2 = 0;
double accuracy_3 = 0;

int name_index = 0;
char player_name[200];
char show_player_name[100];
double show_player_acq;
char s_1[100];
char s_3[100];
FILE *playerDetails;

char fileName[3][30] = {"level1.txt", "level2.txt", "level3.txt"};
char naruto[11][44] = {"image\\bmp1.bmp", "image\\bmp2.bmp", "image\\bmp3.bmp", "image\\bmp4.bmp", "image\\bmp5.bmp", "image\\bmp6.bmp", "image\\bmp7.bmp", "image\\bmp8.bmp", "image\\bmp9.bmp", "image\\bmp10.bmp"};

int narutoCordinateX = 1115;
int narutoCordinateY = 660;
int narutoIndex = 0;
int play = 0;

char mat[20][30];
char mat2[20][30];
int workingMatrix[5];
int resMatrix[5];
int workingMatrix2[5];

void loadFromFile(int index)
{
    FILE *filePointer = fopen(fileName[index - 1], "r");
    if (filePointer == NULL)
    {
        return;
    }
    int n;
    fscanf(filePointer, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(filePointer, "%s%s", mat[i], mat2[i]);
    }
    fclose(filePointer);
}

void randoMizeResult();
void getRandomSet()
{
    srand(time(NULL));
    memset(workingMatrix, -1, 5);
    workingMatrix[0] = rand() % 20;
    resMatrix[0] = workingMatrix[0];
    for (int i = 1; i < 5; i++)
    {
        bool found = false;
        while (!found)
        {
            int index = rand() % 20;
            bool duplicate = false;
            for (int j = 0; j < i; j++)
            {
                if (index == workingMatrix[j])
                {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate)
            {
                workingMatrix[i] = index;
                resMatrix[i] = index;
                found = true;
                break;
            }
        }
    }
    randoMizeResult();
}

int PermuMatrix[120][5];

void loadPermutation()
{
    FILE *filePointer = fopen("permutation.txt", "r");
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fscanf(filePointer, "%d", &PermuMatrix[i][j]);
        }
    }
    fclose(filePointer);
}

void randoMizeResult()
{
    int index = rand() % 120;
    for (int i = 0; i < 5; i++)
    {
        workingMatrix2[i] = resMatrix[PermuMatrix[index][i]];
    }
}

void drawPlayModule()
{
    for (int i = 0; i < 5; i++)
    {
        iSetColor(255, 255, 255);
        iText(188, 106 + i * 101, mat[workingMatrix[i]], GLUT_BITMAP_TIMES_ROMAN_24);
        iText(682, 106 + i * 101, mat2[workingMatrix2[i]], GLUT_BITMAP_TIMES_ROMAN_24);
        if (arrGreenR[i])
        {
            iSetColor(0, 255, 0);
        }
        else if (arrRedR[i])
        {
            iSetColor(255, 0, 0);
        }
        iRectangle(550, 78 + 100 * i, 412, 82);
        if (arrGreenL[i])
        {
            iSetColor(0, 255, 0);
        }
        else
            iSetColor(255, 255, 255);
        iRectangle(104, 78 + 100 * i, 412, 82);
    }
}

void iDraw()
{
    iClear();
    iSetColor(r, g, b);
    // iText(x,y,"WORD MATCHING",GLUT_BITMAP_TIMES_ROMAN_24);
    // level 3
    if (window == 6)
    {
        iSetColor(0, 240, 155);
        char arr[50];
        sprintf(arr, "YOU HAVE SUCCESFULLY FINISHED LEVEL %d!", gamelevel - 1);
        iText(380, 340, arr, GLUT_BITMAP_TIMES_ROMAN_24);
        char arr1[50];
        sprintf(arr1, "PRESS NEXT TO PLAY LEVEL %d!", gamelevel);
        iText(385, 300, arr1, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(900, 32, "Next>>", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(43, 651, "<<BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    }

    else if (window == 5)
    {
        // iShowBMP(0,0,ptr[0]);
        char arr2[50];
        iSetColor(240, 255, 100);
        iRectangle(981, 415, 172, 166);
        iLine(980, 539, 1153, 539);
        iLine(980, 495, 1153, 495);
        iLine(980, 469, 1153, 469);
        iSetColor(255, 0, 10);
        iText(1014, 555, "SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(985, 475, "ACCURACY(%)", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1002, 32, "Next>>", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 255, 255);
        accuracy_1 = ((10.0) / click) * 100;
        sprintf(s_1, "%.2lf", accuracy_1);
        sprintf(s, "%d", score);
        iText(1038, 508, s, GLUT_BITMAP_TIMES_ROMAN_24);
        if (showAccuracy == 1)
        {
            iText(1013, 425, s_1, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iSetColor(255, 150, 150);
        sprintf(arr2,"LEVEL %d",gamelevel-1);
        iText(440, 578, arr2, GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0, 255, 0);
        drawPlayModule();
    }
    else if (window == 4)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, 1180, 700);
        score_save = fopen("score.txt", "a");
        fprintf(score_save, "%s", player_name);
        fclose(score_save);
    }
    else if (window == 3)
    {
        iSetColor(155, 0, 150);
        iRectangle(20, 20, 1061, 670);
        iSetColor(255, 0, 0);
        iText(363, 531, "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 255, 255);
        iText(40, 458, "1.Select a word from left side by left click on mouse", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(40, 420, "2.Choose the word of same meaning from the right clicking left button", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(40, 382, "3.If chosen word correct the box will be of green color.", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(40, 344, "4.If chosen word is wrong you cannot choose another from left", GLUT_BITMAP_TIMES_ROMAN_24);
        //iText(40, 306, "5.By a right click on the mouse you can eliminate red color", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(40, 268, "6.After correct choice you can choose another word from left sight", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(40, 230, "7.Do it till you not get appropriate word", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(40, 192, "8.If you complete by clicking as number as word then accuracy=100%.", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(43, 651, "<<BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if (window == 2)
    {
        iSetColor(150, 140, 50);
        iText(100, 345, "Name:", GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(227, 324, 600, 40);
        iText(228, 335, player_name, GLUT_BITMAP_TIMES_ROMAN_24);
        if (play == 1)
        {
            playerDetails = fopen("player.txt", "a");
            printf("%s", player_name);
            fprintf(playerDetails, "%s %lf %lf %lf\n", player_name, accuracy_1, accuracy_2, accuracy_3);
            fclose(playerDetails);
            play = 0;
        }
        iText(1136, 348, ">>", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(224, 656, "<<HISTORY>>", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(995, 678, "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(43, 651, "<<BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if (window == 1)
    {
        iShowBMP(0, 0, str[strIndex]);
        iSetColor(0, 0, 0);
        iText(414, 27, "Click DOWN button to start play", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 10, 20);
        iText(1045, 635, "Log in", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 255, 255);
        iFilledEllipse(1080, 645, 70, 30, 38);
        iSetColor(255, 10, 20);
        iText(1045, 628, "Log in", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 255, 255);
        iFilledEllipse(1080, 545, 70, 30, 38);
        iSetColor(255, 10, 20);
        iText(1045, 528, "SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if (window == 7)
    {
        iSetColor(255, 255, 255);
        iSetColor(255, 255, 255);
        iFilledRectangle(0, 0, screenWidth, screenHeight);
        iSetColor(0, 0, 0);
        // int line_y = 600;
        // for (int i = 0; i < 12; i++)
        // {
        //     iLine(0, line_y, 1200, line_y);
        //     line_y -= 50;
        // }
        // int line_x = 400;
        // for (int i = 0; i < 3; i++)
        // {
        //     iLine(line_x, 0, line_x, 550);
        //     line_x += 400;
        // }
        iSetColor(200, 100, 250);
        iText(43, 651, "<<BACK", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(43, 651, "<<BACK", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(105, 510, "NAME", GLUT_BITMAP_HELVETICA_18);
        iText(475, 510, "ACQURACY", GLUT_BITMAP_HELVETICA_18);
        int pos_y = 460;
        score_save = fopen("player.txt", "r");
        while (fscanf(score_save, "%s %lf", &show_player_name, &show_player_acq) == 2)
        {
            sprintf(s_1, "%.2lf", show_player_acq);
            sprintf(s_3, "%s", show_player_name);
            printf("%s %d\n", show_player_name, show_player_acq);
            iText(105, pos_y, s_3, GLUT_BITMAP_TIMES_ROMAN_24);
            iText(475, pos_y, s_1, GLUT_BITMAP_TIMES_ROMAN_24);
            pos_y -= 50;
        }
        fclose(score_save);
    }
}

void newLevel()
{
    gamelevel++;
    memset(arrGreenL, 0, 5 * sizeof(int));
    memset(arrGreenR, 0, 5 * sizeof(int));
    memset(arrRedR, 0, 5 * sizeof(int));
    loadFromFile(gamelevel);
    getRandomSet();
    score = 0;
    chosenFromLeft = -1;
}
void iMouseMove(int mx, int my)
{
}
void chooseIndex(int x)
{
    arrGreenL[x] = 1;
    chosenFromLeft = workingMatrix[x];
    click++;
}
void chooseIndexRight(int x)
{
    click++;
    if (chosenFromLeft == workingMatrix2[x])
    {
        arrGreenR[x] = 1;
        chosenFromLeft = -1;
        score++;
    }
    else
        arrRedR[x] = 1;
}
void iMouse(int button, int state, int mx, int my)
{
    printf("%d %d\n", mx, my);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // log in button
        if (mx >= 1008 && mx <= 1149 && my >= 614 && my <= 677)
        {
            window = 2;
            for (int i = 0; i < strlen(player_name); i++)
            {
                player_name[i] = ' ';
                name_index = 0;
            }
        }
        if (mx >= 45 && mx <= 132 && my >= 650 && my <= 672)
        {
            window = 1;
        }
        if (mx >= 1010 && mx <= 1150 && my >= 516 && my <= 577)
        {
            window = 7;
        }
        if (mx >= 1134 && mx <= 1161 && my >= 349 && my <= 363)
        {
            newLevel();
            window = 5;
        }
        if(mx>=998 && mx<=1164 && my>=678 && my<=694 && window==2)
        {
            window=3;
        }
        else if (window == 2)
        {
        }
        else if (window == 3)
        {
        }
        else if (window == 4)
        {
        }
        else if (window == 5)
        {
            if (mx >= 104 && mx <= 516 && my >= 78 && my <= 160 && chosenFromLeft == -1)
            {
                chooseIndex(0);
            }
            else if (mx >= 104 && mx <= 516 && my >= 178 && my <= 260 && chosenFromLeft == -1)
            {
                chooseIndex(1);
            }
            else if (mx >= 104 && mx <= 516 && my >= 278 && my <= 360 && chosenFromLeft == -1)
            {
                chooseIndex(2);
            }
            else if (mx >= 104 && mx <= 516 && my >= 378 && my <= 460 && chosenFromLeft == -1)
            {
                chooseIndex(3);
            }
            else if (mx >= 104 && mx <= 516 && my >= 478 && my <= 560 && chosenFromLeft == -1)
            {
                chooseIndex(4);
            }
            else if (mx >= 550 && mx <= 962 && my >= 78 && my <= 160 && chosenFromLeft != -1)
            {
                chooseIndexRight(0);
            }
            else if (mx >= 550 && mx <= 962 && my >= 178 && my <= 260 && chosenFromLeft != -1)
            {
                chooseIndexRight(1);
            }
            else if (mx >= 550 && mx <= 962 && my >= 278 && my <= 360 && chosenFromLeft != -1)
            {
                chooseIndexRight(2);
            }
            else if (mx >= 550 && mx <= 962 && my >= 378 && my <= 460 && chosenFromLeft != -1)
            {
                chooseIndexRight(3);
            }
            else if (mx >= 550 && mx <= 962 && my >= 478 && my <= 560 && chosenFromLeft != -1)
            {
                chooseIndexRight(4);
            }
            else if (mx >= 1002 && mx <= 1076 && my >= 34 && my <= 49)
            {
                score_save = fopen("player.txt", "a");
                fprintf(score_save, "%s %.2lf\n", player_name, accuracy_1);
                fclose(score_save);
                click = 0;
                window = 6;
            }
        }
        else if (window == 6)
        {
            if (mx >= 900 && mx <= 974 && my >= 32 && my <= 47)
            {
                if (gamelevel  == 4)
                {
                    window = 1;
                }
                else
                {
                    newLevel();
                    window = 5;
                }
            }
        }
    }
}
void iKeyboard(unsigned char key)
{
    if (window == 1)
    {
    }
    else if (window == 2)
    {
    }
    else if (window == 3)
    {
    }
    else if (window == 4)
    {
    }
    else if (window == 5)
    {
    }
    else if (window == 6)
    {
    }
    if (key == 'q')
    {
        exit(0);
    }
    if (window == 2)
    {
        if (key != '\b' && key != 13)
        {
            player_name[name_index] = key;
            name_index++;
            player_name[name_index + 1] != '\0';
        }
        else if (key != 13)
        {
            if (name_index < 0)
            {
                name_index = 0;
            }
            player_name[--name_index] = '\0';
        }
        else
        {
            play = 1;
        }
    }
}
void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_UP)
    {
        if (musicOn)
        {
            musicOn = false;
            PlaySound(0, 0, 0);
        }
        else
        {
            musicOn = true;
            PlaySound(TEXT("music\\musicPlay.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
    }

    if (key == GLUT_KEY_RIGHT)
    {
        showAccuracy = 1;
        // score_save = fopen("player.txt", "a");
        // fprintf(score_save, "%s %.2lf\n", player_name, accuracy_1);
        // fclose(score_save);
    }
    // if (window == 1)
    //     {
    //         newLevel();
    //         window = 5;
    //     }
    if (key == GLUT_KEY_DOWN)
    {
        newLevel();
        window = 5;
    }
}
void change()
{
    narutoIndex++;
    if (narutoIndex >= 10)
    {
        narutoIndex = 0;
    }
}
void loadTable()
{
    FILE *playerDetails;
    playerDetails = fopen("player.txt", "a");
}
int main()
{
    loadPermutation();
    iSetTimer(25, change);
    if (musicOn)
        PlaySound(TEXT("music/musicPlay.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    iInitialize(screenWidth, screenHeight, "WORD MATCHING");

    return 0;
}