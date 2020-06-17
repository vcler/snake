// snake.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

//#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
//using namespace std;
#define width 31
#define height 21

bool gameover = false;
int fruitX, fruitY, x = width/2, y = height/2;
int snakexy[width][width] = { 0 };

int in_size = 1, counter = 0, score = 3, randtime = 0;
char arr[1000000] = { 0 };

void draw() {
    system("cls");

    for (int i = 0; i <= height; i++) {

        for (int j = 0; j <= width; j++) {

            if (i == 0 && j == width) printf("# Score: %d | WASD", score - 3); //prints score indicator

            else if (j == 0 || j == width || i == 0 || i == height) printf("#"); //prints border

            else if (j == x && i == y) printf("O"); //prints the snakes head

            else if (snakexy[j][i] != 0) printf("o"); //prints the snkaes body

            else if (j == fruitX && i == fruitY) printf("+"); //prints the fruit
             
            else printf(" ");

        }
        printf("\n");
    }
}

void fruit() {
    //creates the fruits position
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;

    if (snakexy[fruitX][fruitY] != 0) fruit();
}

void input() {
    //checks which key is pressed and stores it in arr
    if (_kbhit()) {

        switch (_getch()) {
        case 'w':
            arr[counter] = 'w';
            break;
        case 's':
            arr[counter] = 's';
            break;
        case 'd':
            arr[counter] = 'd';
            break;
        case 'a':
            arr[counter] = 'a';
            break;
        }
        
    }
    else {
        if (counter > 0) arr[counter] = arr[counter - 1];
    }
    counter++;
}

void logic() {
    //gameover
    if (x == 0 || x == width || y == 0 || y == height) gameover = true;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (snakexy[x][y] != 0) gameover = true;
        }
    }

    //sneker eat
    if (x == fruitX && y == fruitY) {
        score++;
        fruit();
    }
    if (snakexy[fruitX][fruitY] != 0) fruit();
    

    //snake move head
    switch (arr[counter - 1]) {
    case 'w':
        y--;
        break;
    case 's':
        y++;
        break;
    case 'd':
        x++;
        break;
    case 'a':
        x--;
        break;
    }

    //snake move body
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            snakexy[i][j] = 0;
        }
    }
    
    int tempy = y, tempx = x;

    for (int i = 1; i < score + 1; i++) {

        if ((x != 0 && y != 0) || (x != width && y != height)) {

            switch (arr[counter - i]) {
            case 'w':
                snakexy[tempx][tempy + 1] = 1;
                tempy += 1;
                break;
            case 's':
                snakexy[tempx][tempy - 1] = 1;
                tempy -= 1;
                break;
            case 'd':
                snakexy[tempx - 1][tempy] = 1;
                tempx -= 1;
                break;
            case 'a':
                snakexy[tempx + 1][tempy] = 1;
                tempx += 1;
                break;
            }
        }
    }

}

int main() {

    srand(time(0));
    fruit();

    while (!gameover) {
        input();
        logic();
        draw();
        Sleep(50);

    }
    
    printf("Game Over!  Your Score: %d",score-3);

    return 0;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
