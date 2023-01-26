#include <cs50.h>
#include <stdio.h>

void Loop(int Width);

int main(void)
{
   int Height = get_int("Enter Height");
   if (Height <= 0 || Height > 8)
   {
        Height = get_int("Enter Height");
   }
   int Width = 1;
   for (int i = 0; i < Height; i++ )
   {
        for (int l = 0; l < (Height-Width); l++ )
            printf(" ");
        Loop(Width);
        printf("  ");
        Loop(Width);
    Width = Width + 1;
    printf("\n");
   }
}

void Loop(int Width)
{
    for (int j = 0; j < Width; j++)
    {
        printf("#");
    }
}