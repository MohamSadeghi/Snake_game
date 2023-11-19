#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>

bool End_game;
int Score;
int WIDTH = 30;
int HEIGHT = 20;
int snake_x, snake_y;
int fruit_x, fruit_y;
int Tail_x[40], Tail_y[40];
int len;
enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction r;

void Initialize()
{
    End_game = false;
    r = STOP;
    snake_x = WIDTH / 2;
    snake_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    Score = 0;
};

void Get_input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            r = LEFT;
            break;
        case 's':
            r = DOWN;
            break;
        case 'd':
            r = RIGHT;
            break;
        case 'w':
            r = UP;
            break;
        default:
            End_game = true;
            break;
        }
    }
};

void Logic()
{
    int prevx = Tail_x[0];
    int prevy = Tail_y[0];
    int prev_x2, prev_y2;
    Tail_x[0] = snake_x;
    Tail_y[0] = snake_y;

    for (int k = 1; k < len; k++)
    {
        prev_x2 = Tail_x[k];
        prev_y2 = Tail_y[k];
        Tail_x[k] = prevx;
        Tail_y[k] = prevy;
        prevx = prev_x2;
        prevy = prev_y2;
    }

    switch (r)
    {
    case LEFT:
        snake_x--;
        break;
    case UP:
        snake_y--;
        break;
    case DOWN:
        snake_y++;
        break;
    case RIGHT:
        snake_x++;
        break;
    default:
        break;
    }

    if (snake_x < 0 || snake_x > WIDTH || snake_y < 0 || snake_y > HEIGHT)
        End_game = true;

    for (int k = 0; k < len; k++)
    {
        if (Tail_x[k] == snake_x && Tail_y[k] == snake_y)
            End_game = true;
    }

    if (snake_x == fruit_x && snake_y == fruit_y)
    {
        len++;
        Score += 10;
        do
        {
            fruit_x = (rand() % (WIDTH - 1));
            fruit_y = (rand() % (HEIGHT - 1));
        } while (fruit_x < 0 || fruit_x > WIDTH || fruit_y < 0 || fruit_y > HEIGHT);
    }
};

void Update_Screen()
{
    system("cls");

    for (int i = 0; i < WIDTH + 1; i++)
        std::cout << '#';

    std::cout << std::endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)
                std ::cout << "#";
            if (j == snake_x && i == snake_y)
                std ::cout << "O";
            else if (i == fruit_y && j == fruit_x)
                std::cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < len; k++)
                {
                    if (Tail_x[k] == j && Tail_y[k] == i)
                    {
                        std::cout << 'o';
                        print = true;
                    }
                }
                if (!print)
                    std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < WIDTH + 1; i++)
        std::cout << '#';

    std ::cout << std::endl;
    std::cout << "Your Score is: " << Score;
};

int main()
{
    srand(time(NULL));
    Initialize();

    while (!End_game)
    {
        Update_Screen();
        Get_input();
        Logic();
        Sleep(10);
    }
    return 0;
}