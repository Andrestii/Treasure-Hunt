// Treasure Hunt - Andrea Onesti.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*Realizzare un programma che consenta di realizzare il seguente gioco:
2 giocatori, ciascuno con a disposizione un campo 5X5 in cui inserire all’interno un valore rappresentante un tesoro e tre valori rappresentanti delle bombe.
Ogni giocatore ha tre vite, ed a turno indica all’avversario una cella da scoprire, se trova una bomba perde una vita, se non trova nulla viene restituito un 
messaggio che indica la distanza di celle a cui si trova il tesoro, ed il turno passa all’utente successivo.
Il gioco termina se si trova il tesoro o si perdono tutte le vite.*/

#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define N 5 //Campo N*N
#define B 3 //Numero di bombe

void vis(string mat[N][N]); //Visualizzo matrice string
void delay(int ms); //Delay
void istru(string scelta); //Visualizzare istruzioni
string insplayer(string player); //Inserimento dei nomi dei giocatori
void carico(string matcar[N][N], int matinv[N][N], string player); //Caricamento del tesoro e bombe sul campo avversario
void posi_iniz(string campo[N][N], int matinv[N][N]); //Sceglie una posizione casuale per l'inizio del gioco E inizializza la matrice campo
void gioco(string campo[N][N], int matinv[N][N], int &life, int &exit); //Svoglimento del gioco

int main()
{
	string scelta;
	string player1, player2; //Nomi dei giocatori
	string matcar1[N][N], matcar2[N][N]; //Matrici di caricamento
	int matinv1[N][N], matinv2[N][N]; //Matrici Invisibile
	string campo1[N][N], campo2[N][N]; //Matrici del campo
	int life1 = B, life2 = B, exit = 0;
	cout << "---TREASURE HUNT---\nBy Andrea Onesti\n\nVuoi vedere l'istruzioni del gioco? (si/no): ";
	cin >> scelta; istru(scelta);
	player1 = insplayer(player1); player2 = insplayer(player2);
	system("cls");
	cout << "Per " << player1 << ": Inserire il tesoro e le bombe nel campo avversario:" << endl << endl;
	carico(matcar2,matinv2,player1);
	system("cls");
	cout << "Per " << player2 << ": Inserire il tesoro e le bombe nel campo avversario:" << endl << endl;
	carico(matcar1, matinv1,player2);
	posi_iniz(campo1, matinv1); posi_iniz(campo2, matinv2);
	while (1) {
		system("cls");
		cout << "Tocca a " << player1 << endl;

		gioco(campo1, matinv1, life1, exit);
		if (exit == 1) {
			system("cls");
			cout << "\n\n\nCONGRATUALZIONI " << player1 << " HAI VINTO!\n\n\n\n";
			return 0;
		}
		if (exit == 2) {
			system("cls");
			cout << "\n\n\nMi spiace " << player1 << ", hai perso tutte le vite :(\n\n\n\n";
			return 0;
		}
		delay(2000);
		system("cls");
		cout << "Tocca a " << player2 << endl;
		gioco(campo2, matinv2, life2, exit);
		if (exit == 1) {
			system("cls");
			cout << "\n\n\nCONGRATUALZIONI " << player2 << " HAI VINTO!\n\n\n\n";
			return 0;
		}
		if (exit == 2) {
			system("cls");
			cout << "\n\n\nMi spiace " << player2 << ", hai perso tutte le vite :(\n\n\n\n";
			return 0;
		}
		delay(2000);
	}
	system("pause");
}

void vis(string mat[N][N]) { //Visualizzo matrice string
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << mat[i][j] << " ";

		}
		cout << endl;
	}
}

void delay(int ms) {
	clock_t timeDelay = ms + clock();
	while (timeDelay > clock());
}

void istru(string scelta) {
	if (scelta == "si") {
		cout << "\nISTRUZIONI:\n-Lo scopo del gioco e' trovare il tesoro prima del tuo avversario senza perdere tutte le vite\n-Sulla mappa si troveranno " << B << " bombe che tolgono una vita ciascuna (si inizia con " << B << " vite)\n-Prima che inizi la partita ogni giocatore inserisce la posizione del tesoro e delle bombe dell'avversario\n-Se non si trova una bomba, verra' restituito un messaggio con la distanza tra il giocatore e il tesoro\n-Per muoversi si utilizzano i tasti w,a,s,d (guardare tastiera per vedere direzione dei tasti)\nw = Su\na = Sinistra\ns = Giu'\nd = Destra\n\n";
	}
}

string insplayer(string player) {
	cout << "Inserire il nome del giocatore: ";
	cin >> player;
	return player;
}

void carico(string matcar[N][N], int matinv[N][N], string player) { //Caricamento del tesoro e bombe sul campo avversario
	int a = 0, b = 0;
	for (int i = 0; i < N; i++) { //Inizializzazione matrice di caricamento
		for (int j = 0; j < N; j++) {
			matcar[i][j] = 'O';
		}
	}
	for (int i = 0; i < N; i++) { //Inizializzazione matrice invisibile
		for (int j = 0; j < N; j++) {
			matinv[i][j] = 0;
		}
	}
	vis(matcar);
	cout << "\n-Scegliere dove si trovera' il tesoro sul campo avversario-" << endl;
	do {
		cout << "Riga numero: "; cin >> a; a--;
		cout << "Colonna numero: "; cin >> b; b--;
		if (a >= N || b >= N)
			cout << "Posizione invalida, riprovare" << endl << endl;
	} while (a >= N || b >= N);
	matcar[a][b] = "T";
	matinv[a][b] = 10; //Il 10 rappresenta il tesoro
	for (int i = 0; i < B; i++) {
		system("cls");
		cout << "Per " << player << ": Inserire il tesoro e le bombe nel campo avversario:" << endl << endl;
		vis(matcar);
		cout << "\n-Scegliere dove si troveranno le " << B << " bombe-";
		cout <<endl<< i + 1 << "/" << B << endl;
		do {
			cout << "Riga numero: "; cin >> a; a--;
			cout << "Colonna numero: "; cin >> b; b--;
			if (a >= N || b >= N)
				cout << "Posizione invalida, riprovare" << endl;
			if (matinv[a][b] == 10 || matinv[a][b] == 8)
				cout << "Posizione occupata, riprovare" << endl;
		} while (a >= N || b >= N || matinv[a][b] == 10 || matinv[a][b] == 8);
		matcar[a][b] = 'B';
		matinv[a][b] = 8; //L'8 rappresenta le bombe
	}
}

void posi_iniz(string campo[N][N], int matinv[N][N]) {
	srand(time(NULL));
	int a, b;
	do {
		a = rand() % N;
		b = rand() % N;
	} while (matinv[a][b] == 8 || matinv[a][b] == 10);
	matinv[a][b] = 1; // L'1 rappresenta la posizione del giocatore
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			campo[i][j] = 'O';
			if (matinv[i][j] == 1)
				campo[i][j] = 'X';
		}
	}
}

void gioco(string campo[N][N], int matinv[N][N],int &life, int &exit) {
	string move;

	int a = 0, b = 0;
	int dist; //Distanza di celle
	vis(campo);
	cout << endl;
	/*Per visualizzare la matrice invisibile
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matinv[i][j] << " ";
		}
		cout << endl;
	}*/
	cout << "Vite rimaste: " << life << endl;
	cout << "In quale direzione vorresti andare? (w/a/s/d)" << endl;
	do {
		//Inserimento spostamento
		do {
			cin >> move;
			//Ho dovuto inserire queste condizioni lunghe perche' non mi prendeva il diverso
			if (move == "b" || move == "c" || move == "e" || move == "f" || move == "g" || move == "h" || move == "i" || move == "j" || move == "k" || move == "l" || move == "m" || move == "n" || move == "o" || move == "p" || move == "q" || move == "r" || move == "t" || move == "u" || move == "v" || move == "x" || move == "y" || move == "z")
				cout << "Spostamento invalido, riprovare" << endl;
		} while (move == "b" || move == "c" || move == "e" || move == "f" || move == "g" || move == "h" || move == "i" || move == "j" || move == "k" || move == "l" || move == "m" || move == "n" || move == "o" || move == "p" || move == "q" || move == "r" || move == "t" || move == "u" || move == "v" || move == "x" || move == "y" || move == "z");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matinv[i][j] == 1) {
					if (move == "w") {
						a = i - 1;
						b = j;
					}
					if (move == "a") {
						a = i;
						b = j - 1;
					}
					if (move == "s") {
						a = i + 1;
						b = j;
					}
					if (move == "d") {
						a = i;
						b = j + 1;
					}
				}
			}
		}
		if (a < 0 || a >= N || b < 0 || b >= N)
			cout << "Stai uscendo dal campo, riprovare" << endl;
	} while (a < 0 || a >= N || b < 0 || b >= N);
	//Controlla se hai incontrato una bomba
	if (matinv[a][b] == 8) {
		cout << "Hai trovato una bomba ed hai perso una vita!";
		life--;
	}
	//Controlla se sei morto
	if (life == 0)
		exit = 2;
	//Controlla se hai trovato il tesoro
	if (matinv[a][b] == 10)
		exit = 1;
	//Ti dice quanto sei lontano (solo se non trovi una bomba/tesoro)
	if (matinv[a][b] != 8) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matinv[i][j] == 10)
					dist = abs(a - i) + abs(b - j);
			}
		}
		cout << "Distanza dal tesoro: " << dist << " posizioni" << endl;
	}
	//Sposta di posizione il giocatore
	if (move == "w") {
		matinv[a][b] = 1;
		campo[a][b] = 'X';
		matinv[a + 1][b] = 0;
		campo[a + 1][b] = '-';
	}
	if (move == "a") {
		matinv[a][b] = 1;
		campo[a][b] = 'X';
		matinv[a][b + 1] = 0;
		campo[a][b + 1] = '-';
	}
	if (move == "s") {
		matinv[a][b] = 1;
		campo[a][b] = 'X';
		matinv[a - 1][b] = 0;
		campo[a - 1][b] = '-';
	}
	if (move == "d") {
		matinv[a][b] = 1;
		campo[a][b] = 'X';
		matinv[a][b - 1] = 0;
		campo[a][b - 1] = '-';
	}
}