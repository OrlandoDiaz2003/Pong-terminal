#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void finish(int sig);

void ball( int * ball_x, int *ball_y, int *ball_vel_x, int *ball_vel_y ){

    //deleting the last draw of the ball
    mvaddch(* ball_y, * ball_x, ' ');

    //ball speed 
    * ball_x += * ball_vel_x;
    * ball_y += * ball_vel_y;

    //collision with borders 
    if(* ball_x <= 0 || *ball_x >= COLS - 1){
      *  ball_vel_x *= - 1 ; 
    }
    if(* ball_y <= 0 || * ball_y >= LINES - 1){
      *  ball_vel_y *= - 1 ; 
    }

    //drawing ball in the new position
    mvaddch(* ball_y, * ball_x, 'O');

}

void paddle(int * paddle_height, int * paddle_x,int * paddle_y){
    

    // getting user input
    int key = getch();

    //Delete
    for (int i = 0; i < *paddle_height; i++)
    {
        mvaddch(*paddle_y + i, *paddle_x, ' ');
    }

    if(key == KEY_UP && * paddle_height > 0) (* paddle_y) --;
    
    if(key == KEY_DOWN && * paddle_y + * paddle_height < LINES) (* paddle_y) ++;

    //Draw paddle
    for (int i = 0; i < *paddle_height; i++)
    {
        mvaddch(*paddle_y + i, *paddle_x, '#');
    }


}

int main()
{
    //inicia screen
    initscr();

    nodelay(stdscr, TRUE);
    signal(SIGINT, finish);

    keypad(stdscr, TRUE);
    noecho();
    cbreak();

    //BALL VARIABLES
    //ball position
    int ball_y = 0;
    int ball_x = COLS / 2;

    //ball velocity
    int ball_vel_x = 1;
    int ball_vel_y = 1;


    //PADDLE VARIABLES
    //paddle height 
    int paddle_height = 4;

    //paddle position
    int paddle_x = 0;
    int paddle_y = 0;

    for(;;)
    {
        ball(&ball_x, &ball_y, &ball_vel_x, &ball_vel_y);
        paddle( &paddle_height, &paddle_x, &paddle_y);

        refresh();
        usleep(16000);
    }

    finish(0);
}

static void finish(int sig){
    endwin();

    exit(0);
}