/*
 Istituto Tecnico Tecnologico FEDI-FERMI
 Laboratorio di Informatica
 Anno scolastico 2016/17
 Classe 3IB

 Progamma      : Water map
 Autore        : Coppini Fabio
 Data consegna : 19/02/2016
*/

#include <iostream>
#include <windows.h>
#include <ctime>
#define MAX 30
using namespace std;

struct ground{
    int height;
    bool awash=0;
};

void gotoXY(int x, int y);
void setColor(int bg, int fg) ;
void screen();
int random(int a);
int capturesizes();
void acquiringmap(ground tab[][MAX], int rig, int col);
void showmap(ground tab[][MAX], int rig, int col);
void showmapflooded(ground tab[][MAX], int rig, int col);
void watersource(int vet[], int rig, int col);
void floodmap(ground tab[][MAX], int x, int y, int rig, int col);
void floods_all_over_the_map(ground tab[][MAX], int r, int c);
char stillplays();

int main(){
    ground ZoneMAP[MAX][MAX];
    int WaterSource[2];
    int r=0, c=0;
    char answer;
    do{
        setColor(12,15);
        system("cls");
        screen();
        gotoXY(6,3);
        cout<<" Inserisci il numero di righe "<<endl;
        r = capturesizes();
        gotoXY(6,6);
        cout<<" Inserisci il numero di colonne "<<endl;
        c = capturesizes();
        acquiringmap(ZoneMAP, r, c);
        system("cls");
        screen();
        gotoXY(0,3);
        showmap(ZoneMAP, r, c);
        watersource(WaterSource, r, c);
        cout<<endl<<"\tQuesta e' l'altezza della fonte: "<<ZoneMAP[WaterSource[0]][WaterSource[1]].height<<endl;
        floodmap(ZoneMAP, WaterSource[0], WaterSource[1], r, c);
        ZoneMAP[WaterSource[0]][WaterSource[1]].awash=1;
        cout<<endl<<"\t\t  *** WATERMAP *** "<<endl;
        floods_all_over_the_map(ZoneMAP, r, c);
        showmapflooded(ZoneMAP, r, c);
        setColor(12,15);
        answer = stillplays();
    }
    while(answer=='s');
}

void gotoXY(int x, int y){
    COORD CursorPos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, CursorPos);
}

void setColor(int bg, int fg){
    int val;
    if (bg<0) bg=0;
    if (fg>15) fg=15;
    val=bg*16+fg;
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        val);
/*
0 BLACK; 1 BLUE; 2 GREEN; 3 CYAN; 4 RED; 5 MAGENTA; 6 BROWN; 7 LIGHTGRAY; 8 DARKGRAY;
9 LIGHTBLUE; 10 LIGHTGREEN; 11 LIGHTCYAN; 12 LIGHTRED; 13 LIGHTMAGENTA; 14 YELLOW; 15 WHITE.
*/
}

void screen(){
    setColor(12,15);
    gotoXY(20,1);
    cout<<" !!! THIS IS THE WATER MAP !!!"<<endl;
}

int random(int a){
    int c;
    c = rand()%a+1;
    return c;
}

int capturesizes(){
    int a=0;
    do{
        cout<<"       Inserimento: ";
        cin>>a;
    }while(a<1);
    return a;
}

void acquiringmap(ground tab[][MAX], int rig, int col){
    int i=0, j=0;;
    char answer;
    gotoXY(6,9);
    cout<<" ACQUISIZIONE DEI VALORI "<<endl;
    do{
        cout<<"\n\tPreferisci inserirli manualmente o generarli in modo casuale? \n\t'a' = manuale\n\t'b' = casuale\n        Inserimento: ";
        cin>>answer;
        if(answer!='a' && answer!='b'){
            cout<<"\n\t'a' = MANUALE. \n\t'b' = CASUALE."<<endl;
        }
    }while(answer!='a' && answer!='b');
    if(answer=='a'){
        system("cls");
        screen();
        gotoXY(0,3);
        for(i=0; i<rig; i++){
            for(j=0; j<col; j++){
                do{
                    cout<<" Altezza del terreno in riga "<<i+1<<" e in colonna "<<j+1<<": ";
                    cin>>tab[i][j].height;
                    if((tab[i][j].height<1) || (tab[i][j].height>5001)){
                        cout<<"\n\t'5000 metri' = ALTEZZA MASSIMA. \n\t'1 metro' = ALTEZZA MINIMA."<<endl;
                    }
                }while((tab[i][j].height<1) || (tab[i][j].height>5001));
            }
        }
    }else{
        srand((unsigned)time(NULL));
        for(i=0; i<rig; i++){
            for(j=0; j<col; j++){
                tab[i][j].height = random(4999);
            }
        }
    }
}

void showmap(ground tab[][MAX], int rig, int col){
    int i, j;
    cout<<endl;
    for(i=0; i<rig; i++){
        for(j=0; j<col; j++){
            cout<<"\t"<<tab[i][j].height;
        }
        cout<<endl;
    }
}

void showmapflooded(ground tab[][MAX], int rig, int col){
    int i, j;
    cout<<endl;
    for(i=0; i<rig; i++){
        for(j=0; j<col; j++){
            if(tab[i][j].awash==1){
                setColor(12,15);
                cout<<"\t";
                setColor(11,15);
                cout<<tab[i][j].height;
            }else{
                if(tab[i][j].height>3999){
                    setColor(12,15);
                    cout<<"\t";
                    setColor(6,15);
                    cout<<tab[i][j].height;
                }
                if(tab[i][j].height>1999 && tab[i][j].height <= 3999){
                    setColor(12,15);
                    cout<<"\t";
                    setColor(2,15);
                    cout<<tab[i][j].height;
                }
                if(tab[i][j].height<=1999){
                    setColor(12,15);
                    cout<<"\t";
                    setColor(10,15);
                    cout<<tab[i][j].height;
                }
            }
        }
    cout<<endl;
    }
}

void watersource(int vet[], int rig, int col){
    cout<<"\n\tDove si trova la fonte?"<<endl;
    do{
        cout<<"\n\tRIGA: ";
        cin>>vet[0];
    }while(vet[0]>rig || vet[0]<1);
    do{
        cout<<"\n\tCOLONNA: ";
        cin>>vet[1];
    }
    while(vet[1]>col || vet[1]<1);
    vet[0]--;
    vet[1]--;
}

void floodmap(ground tab[][MAX], int x, int y, int rig, int col){
    if((tab[x-1][y].height <= tab[x][y].height) && (x>0)){
        tab[x-1][y].awash = 1;
    }
    if((tab[x-1][y+1].height <= tab[x][y].height) && (x>0 && y<col)){
        tab[x-1][y+1].awash = 1;
    }
    if((tab[x][y+1].height <= tab[x][y].height) && (y<col)){
        tab[x][y+1].awash = 1;
    }
    if((tab[x+1][y+1].height <= tab[x][y].height) && (x<rig && y<col)){
        tab[x+1][y+1].awash = 1;
    }
    if((tab[x+1][y].height <= tab[x][y].height) && (x<rig)){
        tab[x+1][y].awash = 1;
    }
    if((tab[x+1][y-1].height <= tab[x][y].height) && (x<rig && y>0)){
        tab[x+1][y-1].awash = 1;
    }
    if((tab[x][y-1].height <= tab[x][y].height) && (y>0)){
        tab[x][y-1].awash = 1;
    }
    if((tab[x-1][y-1].height <= tab[x][y].height) && (x>0 && y>0)){
        tab[x-1][y-1].awash = 1;
    }
}

void floods_all_over_the_map(ground tab[][MAX], int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(tab[i][j].awash==1){
                floodmap(tab, i, j, r, c);
            }
        }
    }
}

char stillplays(){
    char a=0;
    cout<<endl;
    cout<<endl;
    do{
        cout<<"\t Vuoi riprovare?\n\t's' = SI. \n\t'n' = NO.\n\t Inserimento: ";
        cin>>a;
        if(a!='s' && a!='n'){
            cout<<"\t\n\t's' = SI. \n\t'n' = NO."<<endl;
        }
        if(a=='n'){
            system("cls");
            gotoXY(30,10);
            cout<<" ALLA PROSSIMA!";
        }
    }
    while(a!='s' && a!='n');
    return a;
}
