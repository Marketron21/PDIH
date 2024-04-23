#include <ncurses.h>
#include <unistd.h>
#define DELAY 45000

void explicacion(int max_y, int max_x);
void final(int puntuacion_izq, int puntuacion_der, int max_y, int max_x);

int main(int argc, char *argv[]) {
    int x, y, x1, y1, x2, y2;
    int max_y = 50, max_x = 50;
    int next_x = 0, next_y = 0;
    int dir_x= 1, dir_y = 1;
    int puntuacion_izq = 0, puntuacion_der = 0;
    bool punto = false;
    
    char * str1;
    char * str2;
    
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr,TRUE);
    keypad(stdscr,TRUE);
    curs_set(FALSE);
    getmaxyx(stdscr, max_y, max_x);
    x = max_x/2;
    y = max_y/2;
    y1 = max_y / 2;
    x1 = max_x / 6;
    y2 = max_y / 2;
    x2 = max_x * 5 / 6;
    
    explicacion(max_y, max_x);
    while(puntuacion_izq < 3 && puntuacion_der < 3) {
        clear();
        mvprintw(y, x, "o");
        for(int i = y1-2; i <y1+3; i++){
            mvprintw(i,x1,"|");
        }
        for(int i = y2-2; i <y2+3; i++){
            mvprintw(i,x2,"|");
        }
        
        refresh();
        usleep(DELAY);
        next_x = x + dir_x;
        next_y = y + dir_y;
        
        int a = getch();
        if (a != ERR){
            if (a == KEY_UP){
                if ((y2 - 3) >= 0){
                    y2 -= 1;
                }
            }
            else if (a == KEY_DOWN){
                if ((y2 + 3) < max_y){
                    y2 += 1;
                }
            }
            else if (a == 'w'){
                if ((y1 - 3) >= 0){
                    y1 -= 1;
                }
            }
            else if (a == 's'){
                if ((y1 + 3) < max_y){
                    y1 += 1;
                }
            }
        }
        
        if (next_x >= max_x){
            puntuacion_izq += 1;
            punto = true;
        } 
        else if (next_x < 0) {
            puntuacion_der += 1;
            punto = true;
        } 
        else {
            x+= dir_x;
        }
        
        if (next_y >= max_y || next_y < 0) {
            dir_y*= -1;
        } 
        else {
            y+= dir_y;
        }
        
        if (x == x1){
            if (y >= y1-2 && y <= y1+2){
                dir_x*=-1;
            }
        }
        
        if (x == x2){
            if (y >= y2-2 && y <= y2+2){
                dir_x*=-1;
            }
        }
        
        if (punto){
            punto = false;
            clear();
            mvprintw(max_y/2,max_x/2 - 2,"%d - %d",puntuacion_izq,puntuacion_der);
            refresh();
            usleep(17*DELAY);
            x = max_x/2;
            y = max_y/2;
            y1 = y;
            y2 = y;
            dir_x*=-1;
        }
        
    }
    final(puntuacion_izq, puntuacion_der, max_y, max_x);
    endwin();
}


void explicacion(int max_y, int max_x){
    clear();
    mvprintw(max_y/2 - 2,max_x/2 - 16, "Juego creado por Marcos Rico Guerra");
    mvprintw(max_y/2, max_x/2-5,"Controles:");
    mvprintw(max_y/2+1, max_x/2-23,"Jugador 1: (W) Mover Arriba     (S) Mover Abajo");
    mvprintw(max_y/2+2, max_x/2-36,"Jugador 2: (Flecha Arriba) Mover Arriba     (Flecha Abajo) Mover Abajo");
    refresh();
    usleep(120*DELAY);
}

void final(int puntuacion_izq, int puntuacion_der, int max_y, int max_x){
    clear();
    if(puntuacion_izq > puntuacion_der){
        mvprintw(max_y/2 - 2, max_x/2-14, "Felicidades Jugador 1. Has Ganado");
    }
    else if(puntuacion_izq < puntuacion_der){
        mvprintw(max_y/2 - 2, max_x/2-14, "Felicidades Jugador 2. Has Ganado");
    }
    else{
        mvprintw(max_y/2 - 2, max_x/2-17, "Buen Juego. Ha sido un empate");
    }
    
    mvprintw(max_y/2, max_x/2-7, "Resultado final:");
    mvprintw(max_y/2+2,max_x/2 - 2,"%d - %d",puntuacion_izq,puntuacion_der);
    refresh();
    usleep(110*DELAY);
}
