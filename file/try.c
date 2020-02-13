#include<stdio.h>
#include<stdlib.h>

struct matrix{
    char **m;
    int column;
    int row;
};

void print_m (struct matrix *u);
void change_m (struct matrix *u);
FILE *fopen( const char * filename, const char * mode );

int main()
{

    struct matrix u1;
    int i;


    //read the file and get the row and column
    FILE *fp;
    fp=fopen("glider.txt","rt");

    char ch;

    int row = 0, column = 0, check_column = 0;

    while( (ch=fgetc(fp)) != EOF )
    {
        putchar(ch);
        if (ch != '\n')
        {
            column = column + 1;
        }
        if (ch == '\n')
        {
            if (check_column == 0)
            {
                row = row + 1;
                check_column = column;
                column = 0;
            }
            else if (check_column != column)
            {
                printf("the column is not correct");
                return 0;
            }
            else
            {
                row = row + 1;
                check_column = column;
                column = 0;
            }
        }
    }

    u1.row = row;
    u1.column = column;

    u1.m = (char **)malloc(sizeof(char *) * row);
    for (i = 0; i < row; i ++)
    { // 按行分配每一列
    	u1.m[i] = (char *)malloc(sizeof(char) * column);
    }


    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
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
/*
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
*/
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
    for (int i = 0; i < u->row; i++)
    {
        for (int j = 0; j < u->column; j++)
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
