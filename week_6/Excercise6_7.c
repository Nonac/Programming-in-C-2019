#include<stdlib.h>
#include<stdio.h>
#define SIZE 81

void sierpinski(int square[SIZE][SIZE], int size, int x, int y);
void display(int square[SIZE][SIZE]);

int main()
{
    int x=0, y=0;
    int square[SIZE][SIZE] = {0};
    sierpinski(square, SIZE, x, y);
    display(square);
    return 0;
}

void sierpinski(int square[SIZE][SIZE], int size, int x, int y)
{
    if(size == 1){
        square[y][x] = 1;
        return;
    }
    else{
        sierpinski(square, size/3, x, y);
        sierpinski(square, size/3, x+size/3, y);
        sierpinski(square, size/3, x+(2*(size/3)), y);
        sierpinski(square, size/3, x, y+size/3);
        sierpinski(square, size/3, x+(2*(size/3)), y+size/3);
        sierpinski(square, size/3, x, y+(2*(size/3)));
        sierpinski(square, size/3, x+size/3, y+(2*(size/3)));
        sierpinski(square, size/3, x+(2*(size/3)), y+(2*(size/3)));
    }

}

void display(int square[SIZE][SIZE])
{
    int r,c;
    for(r=0;r<SIZE;++r)
    {
        for(c=0;c<SIZE;++c)
        {
            if(square[r][c] == 1)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}