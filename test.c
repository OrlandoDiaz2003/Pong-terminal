#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
static void finish(int sig);

void ball(float *ball_x, float *ball_y, float *ball_vel_x, float *ball_vel_y)
{
    // deleting the last draw of the ball
    mvaddch(*ball_y, *ball_x, ' ');

    // ball speed

    *ball_x += *ball_vel_x;
    *ball_y += *ball_vel_y;

    // collision with borders
    if (*ball_x <= 0 || *ball_x >= COLS - 1)
    {
        *ball_vel_x *= -1;
        *ball_x = (COLS / 2) - 1;
        *ball_y = LINES / 2;
    }

    if (*ball_y <= 0 || *ball_y >= LINES - 1)
    {
        *ball_vel_y *= -1;
    }

    // drawing ball in the new position
    mvaddch(*ball_y, *ball_x, 'O');
}

void paddle_collision(float *ball_x, float *ball_y, float *ball_vel_x, float *paddle_x, float *paddle_y, float *paddle_height)
{
    bool collision_x = fabsf(*ball_x - *paddle_x) <= 1.0f ;
    bool collision_y = (*paddle_y <= *ball_y) && (*paddle_y + *paddle_height >= *ball_y);

    if(collision_x && collision_y){
        *ball_vel_x *= - 1;
    }
}

void paddle(float *paddle_height, float *paddle_x, float *paddle_y)
{
    // Delete
    for (int i = 0; i < *paddle_height; i++)
    {
        mvaddch(*paddle_y + i, *paddle_x, ' ');
    }

    // Draw paddle
    for (int i = 0; i < *paddle_height; i++)
    {
        mvaddch(*paddle_y + i, *paddle_x, '#');
    }
}

void controller(float *paddle_x, float *paddle_y, float *paddle_height, float *paddle2_x, float *paddle2_y, float *paddle2_height)
{
    int key = getch();

    switch (key)
    {
    // paddle 1
    case 'w':
        for (int i = 0; i < *paddle_height; i++)
        {
            mvaddch(*paddle_y + i, *paddle_x, ' ');
        }

        if (*paddle_y > 0)
            (*paddle_y)--;

        for (int i = 0; i < *paddle_height; i++)
        {
            mvaddch(*paddle_y + i, *paddle_x, '#');
        }
        break;
    case 's':
        for (int i = 0; i < *paddle_height; i++)
        {
            mvaddch(*paddle_y + i, *paddle_x, ' ');
        }

        if (*paddle_y + *paddle_height < LINES)
            (*paddle_y)++;

        for (int i = 0; i < *paddle_height; i++)
        {
            mvaddch(*paddle_y + i, *paddle_x, '#');
        }
        break;

    case KEY_UP:
        for (int i = 0; i < *paddle2_height; i++)
        {
            mvaddch(*paddle2_y + i, *paddle2_x, ' ');
        }
        if (*paddle2_y > 0)
            (*paddle2_y)--;
        for (int i = 0; i < *paddle2_height; i++)
        {
            mvaddch(*paddle2_y + i, *paddle2_x, '#');
        }
        break;
    case KEY_DOWN:
        for (int i = 0; i < *paddle2_height; i++)
        {
            mvaddch(*paddle2_y + i, *paddle2_x, ' ');
        }
        if (*paddle2_y + *paddle2_height < LINES)
            (*paddle2_y)++;
        for (int i = 0; i < *paddle2_height; i++)
        {
            mvaddch(*paddle2_y + i, *paddle2_x, '#');
        }

        break;
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

    // key
    int key = getch();

    // BALL VARIABLES
    // ball position
    float ball_y = 0;
    float ball_x = COLS / 8;

    // ball velocity
    float ball_vel_x = 1.0;
    float ball_vel_y = 0.8;

    // PADDLE VARIABLES
    // paddle height
    float paddle_height = 4;

    // paddle position
    float paddle_x = (COLS / 2) - (COLS / 2) + 10;
    float paddle_y = 0;

    float paddle2_x = (COLS / 2) + (COLS / 2) - 10;
    float paddle2_y = 0;

    float paddle2_height = 4;

    for (;;)
    {
        ball(&ball_x, &ball_y, &ball_vel_x, &ball_vel_y);
        paddle_collision(&ball_x, &ball_y, &ball_vel_x, &paddle_x, &paddle_y, &paddle_height);
        paddle_collision(&ball_x, &ball_y, &ball_vel_x, &paddle2_x, &paddle2_y, &paddle2_height);
        controller(&paddle_x, &paddle_y, &paddle_height, &paddle2_x, &paddle2_y, &paddle2_height);
        paddle(&paddle_height, &paddle_x, &paddle_y);
        paddle(&paddle2_height, &paddle2_x, &paddle2_y);

        refresh();
        usleep(33000);
    }

    finish(0);
}

static void finish(int sig)
{
    endwin();

    exit(0);
}
