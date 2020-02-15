#include<stdio.h>
#include<stdlib.h>

struct matrix{
    char **m;
    int column;
    int row;
};

void print_m (struct matrix *u);
void print_m1 (struct matrix *u, int column, int row);
void change_m (struct matrix *u);
FILE *fopen( const char * filename, const char * mode );

int main( int argc, char *argv[] )
{

    struct matrix u1;
    int i;

    printf("%s\n", argv[1]);
    //read the file and get the row and column
    FILE *fp;
    fp=fopen("glider.txt","rt");

    char ch;

    int row = 0, column = 0, check_column = 0;

    while( (ch=fgetc(fp)) != EOF )
    {
        if (ch != '\n' && (ch == '.' || ch == '*'))
        {
            column = column + 1;
        }
        else if (ch == '\n')
        {
            if (check_column == 0)
            {
                row = row + 1;
                check_column = column;
                column = 0;
            }
            else if (check_column != column)
            {
                printf("something in the column/row is missing\n");
                return 0;
            }
            else
            {
                row = row + 1;
                check_column = column;
                u1.column = column;
                column = 0;
            }
        }
        else
        {
            printf("the symble in the file is wrong!\n");
            return 0;
        }
    }

    fseek(fp,0,SEEK_SET);


    u1.row = row;

    printf("the column and row: %d,%d\n", u1.column, u1.row);

    u1.m = (char **)malloc(sizeof(char *) * row);
    for (i = 0; i < row; ++i)
    {
    	u1.m[i] = (char *)malloc(sizeof(char) * column);
    }

    row = 0;
    column = 0;

    while( (ch=fgetc(fp)) != EOF )
    {
        if (ch != '\n')
        {
            printf("%c", ch);
            u1.m[row][column] = ch;
            column = column + 1;
        }
        if (ch == '\n')
        {
            printf("\n");
            row = row + 1;
            column = 0;
        }
    }

    printf("print out the matrix\n");
    print_m( &u1 );

    //release the space for the matrix when every time the program finished
    for (int i = 0; i < row; ++i)
    {
    	free(*(u1.m + i));
    }

    printf("release the u1.m's space\n");

    print_m( &u1 );

    return 0;

}

void print_m (struct matrix *u)
{
    for (int i = 0; i < u->row; ++i)
    {
        for (int j = 0; j < u->column; ++j)
        {
            if (j == u->column - 1)
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

void print_m1 (struct matrix *u, int column, int row)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            if (j == column - 1)
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
