#include<stdio.h>
#include<stdlib.h>

struct matrix{
    char **m;
};

void print_m (struct matrix *u);
void change_m (struct matrix *u);

int main()
{

    struct matrix u1;
    struct matrix u2;
    int i;

    u1.m = (char **)malloc(sizeof(char *) * 10);
    for (i = 0; i < 10; i ++)
    { // 按行分配每一列
    	u1.m[i] = (char *)malloc(sizeof(char) * 10);
    }

    u2.m = (char **)malloc(sizeof(char *) * 10);
    for (i = 0; i < 10; i ++)
    { // 按行分配每一列
    	u2.m[i] = (char *)malloc(sizeof(char) * 10);
    }
    //for (int i = 0; i < 10; ++i)
    //{
    	//free(*(u1.m + i));
    //}

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i%2 == 1 && j%2 == 0)
            {
                u1.m[i][j] = '*';
            }
            else
            {
                u1.m[i][j] = '.';
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i%2 == 1 && j%2 == 0)
            {
                u2.m[i][j] = '#';
            }
            else
            {
                u2.m[i][j] = ',';
            }
        }
    }

    print_m( &u1 );
    change_m( &u1 );
    print_m( &u1 );

    return 0;

/*
    char a[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i%2 == 1 && j%2 == 0) {
               a[i][j] = '*';
            } else {
               a[i][j] = '.';
            }
        }
    }

    a[2][1] = '&';

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (a[i][j] == '*')
            {
                printf("alive\n");
            }
            else if (a[i][j] == '.')
            {
                printf("dead\n");
            }
        }
    }
    printf("sp:%c\n", a[2][1]);
*/
}

void print_m (struct matrix *u)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (j == 9)
            {
                printf("%c\n", u->m[i][j]);
            }
            else
            {
                printf("%c", u->m[i][j]);
            }
        }
    }
}

void change_m (struct matrix *u)
{
    //struct matrix u1;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            u1.m[i][j] = '&';
        }
    }
}