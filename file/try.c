#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>

struct matrix
{
    char **m;
    int column;
    int row;
    char *inputFileName;
    char *outputFileName;
    int generation_num;
};


void print_m (struct matrix *u);
void print_m1 (char **will);
void change_m (struct matrix *u);
void write_out_file (FILE *outfile, struct matrix *u);
void read_in_file (FILE *infile, struct matrix *u);

int main( int argc, char *argv[] )
{

    struct matrix u1;
    int i;

    //read the file and get the row and column
    FILE *fp;
    fp = fopen("glider.txt","rt");

    int opt, print_statistics, use_torus;

    char *string = "sti:o:g:";
/*
    while ((opt = getopt(argc, argv, string))!= -1)
    {
        printf("opt = %c\t\t", opt);
        printf("optarg = %s\t\t",optarg);
        printf("optind = %d\t\t",optind);
        printf("argv[optind] = %s\n",argv[optind]);
    }*/

    while ((opt = getopt(argc, argv, string))!= -1)
    {
        switch (opt)
        {
            case 'i':
                if (optarg)
                {
                    u1.inputFileName = optarg;
                    printf("the opt i %s\n", u1.inputFileName);
                }
                else
                {
                    printf("Please input the file name: \n");
                }
                continue;
            case 'o':
                if (optarg)
                {
                    u1.outputFileName = optarg;
                    printf("the opt o %s\n", u1.outputFileName);
                }
                else
                {
                    int outputFileName = 0;
                    printf("the opt o %d\n", outputFileName);
                }
                continue;
            case 'g':
                if (optarg)
                {
                    u1.generation_num = atoi(optarg);
                    printf("the opt g %d\n", u1.generation_num);
                }
                else
                {
                    int generation_num = 5;
                    printf("the opt g %d\n", generation_num);
                }
                continue;
            case 's':
                print_statistics = 1;
                printf("the opt s %d\n", print_statistics);
                continue;
            case 't':
                use_torus = 1;
                printf("the opt t %d\n", use_torus);
                continue;
        }
    }
    read_in_file(stdin,&u1);
    //char n = argv[1];
    //printf("%c\n", n);


    char ch, ch_in;

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

    //printf("the column and row: %d,%d\n", u1.column, u1.row);

    u1.m = (char **)malloc(sizeof(char *) * u1.row);
    for (i = 0; i < row; ++i)
    {
    	u1.m[i] = (char *)malloc(sizeof(char) * u1.column);
    }

    row = 0;
    column = 0;

    while( (ch_in=fgetc(fp)) != EOF )
    {
        if (ch_in != '\n')
        {
            //printf("%c", ch_in);
            u1.m[row][column] = ch_in;
            if (row==3 && column == 19)
            {
                //printf("\n%c\n", ch_in);
                //printf("\n0 %c,%c", u1.m[row][column], u1.m[3][19]);
            }
            column = column + 1;
        }
        if (ch_in == '\n')
        {
            //printf("\n");
            row = row + 1;
            column = 0;
        }
    }


    char **will;

    will = u1.m;
    //printf("print out the will matrix\n");
    //print_m1( will );

    //printf("print out the matrix\n");
    //print_m( &u1 );

    //release the space for the matrix when every time the program finished
    for (int i = 0; i < row; ++i)
    {
    	free(*(u1.m + i));
    }

    //printf("release the u1.m's space\n");

    //print_m( &u1 );

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

void print_m1 (char **will)
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            if (j == 19)
            {
                printf("%c\n", will[i][j]);
            }
            else
            {
                printf("%c", will[i][j]);
            }
        }
    }
}

void write_out_file (FILE *outfile, struct matrix *u)
{
    outfile = fopen("test.txt", "w+");
    fputs("this is the final life:\n", outfile);
    for (int i = 0; i < u->row; ++i)
    {
        for (int j = 0; j < u->column; ++j)
        {
            if (j == u->column - 1)
            {
                fputc(u->m[i][j], outfile);
                fputs("\n", outfile);
            }
            else
            {
                fputc(u->m[i][j], outfile);
            }
        }
    }
    fclose(outfile);

}

void read_in_file (FILE *infile, struct matrix *u)
{
    char ch_in;
    infile = fopen(u->inputFileName,"rt");
    printf("%s\n", u->inputFileName);
    printf("%s\n", u->outputFileName);
    printf("%d\n", u->generation_num);

    while( (ch_in=fgetc(infile)) != EOF )
    {
        if (ch_in != '\n')
        {
            printf("%c", ch_in);
        }
        if (ch_in == '\n')
        {
            printf("\n");
        }
    }
}
