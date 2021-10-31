#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int n;

    srand((unsigned)time(0));
    unsigned int r_int = rand()*rand();
    unsigned int key = r_int % 1001;

    for (int i = 0; i < 10; i++)
    {
        printf("Put your guess: ");
        scanf("%d", &n);
        if (i == 0)
        {
            if (n == key)
            {
                printf("Feeling lucky! the key was %d.\n", key);
                if (key == 0 || key == 1000)
                {
                    printf("You got the extreme number! the key was %d.\n", key);
                }
                break;
            }
        }
        if (i < 10)
        {
            if (n > key)
            {
                printf("The key is lower than %d\n", n);
                if (n > key - 10 && n < key + 10)
                {
                    printf("Lucky! the key is close to %d\n", n);
                }
            }
            else if (n < key)
            {
                printf("The key is higher than %d\n", n);
                if (n > key - 10 && n < key + 10)
                {
                    printf("Lucky! the key is close to %d\n", n);
                }
            }
            else
            {
                if (key == 0 || key == 1000)
                {
                    printf("You got the extreme number! the key was %d.\n", key);
                }
                else
                {
                    printf("Player won! the key was %d.\n", key);
                }
                break;
            }
        }
        if (i == 9)
        {
            printf("Computer won! the key was %d.\n", key);
        }
    }
    return 0;
}