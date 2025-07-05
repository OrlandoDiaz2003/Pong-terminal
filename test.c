#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void finish(int sig);

void ball( float * ball_x, float *ball_y, float *ball_vel_x, float *ball_vel_y, float *paddle_height,float *paddle_x, float * paddle_y){

    //deleting the last draw of the ball
    mvaddch(* ball_y, * ball_x, ' ');

    //ball speed 
    float acomulator = acomulator + *ball_vel_x;

    * ball_x += acomulator;
    * ball_y += * ball_vel_y;

    //collision with borders 
    if(* ball_x <= 0 || *ball_x >= COLS - 1){
      * ball_vel_x *= - 1 ; 
      * ball_x = (COLS/2) - 1;
      * ball_y = LINES/2;
    }

    if(* ball_y <= 0 || * ball_y >= LINES - 1){
      *  ball_vel_y *= - 1 ; 
    }

    //collision with paddle
     
    if(* ball_x <= * paddle_x && * paddle_y <= * ball_y && * paddle_y + * paddle_height >= * ball_y){
        * ball_vel_x *= -1;
    }

    //drawing ball in the new position
    mvaddch(* ball_y, * ball_x, 'O');
}


void paddle(float * paddle_height,float  * paddle_x,float * paddle_y){
    
    // getting user input
    int key = getch();

    //Delete
    for (int i = 0; i < *paddle_height; i++)
    {
        mvaddch(*paddle_y + i, *paddle_x, ' ');
    }

    //move the paddle
    if(key == KEY_UP && * paddle_y > 0) (* paddle_y) --;
    if(key == KEY_DOWN && * paddle_y + * paddle_height < LINES) (* paddle_y) ++;

    //Draw paddle
    for (int i = 0; i < *paddle_height; i++)
    {
        mvaddch(*paddle_y + i, *paddle_x,'#');
    }
}

int main()
{
    initscr();

    nodelay(stdscr, TRUE);
    signal(SIGINT, finish);

    keypad(stdscr, TRUE);
    noecho();
    cbreak();

    //BALL VARIABLES
    //ball position
    float ball_y = 0;
    float ball_x = COLS / 8;

    // ball velocity
    float ball_vel_x = 0.5;
    float ball_vel_y = 0.2;

    //PADDLE VARIABLES
    //paddle height 
    float paddle_height = 4;

    //paddle position
    float paddle_x = (COLS / 2) - (COLS / 2) + 10;
    float paddle_y = 0;

    for(;;)
    {
        ball(&ball_x, &ball_y, &ball_vel_x, &ball_vel_y,&paddle_height,&paddle_x, &paddle_y);
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