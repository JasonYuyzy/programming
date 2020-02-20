#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include<string.h>

struct matrix
{
    int **m;
    int column;
    int row;
    char *inputFileName;
    char *outputFileName;
    int outputFile;
    int generation_num;
};


void print_m (struct matrix *u);
void print_char (struct matrix *u);
void print_m1 (char **will);
void change_m (struct matrix *u);
void write_out_file (FILE *outfile, struct matrix *u);
void read_in_file (FILE *infile, struct matrix *u);

int main( int argc, char *argv[] )
{

    struct matrix u1;
    int i;



    int opt, print_statistics, use_torus;

    //read and analyse the command line
/*
    while ((opt = getopt(argc, argv, "i::g::o::st"))!= -1)
    {
        printf("opt = %c\t\t", opt);
        printf("optarg = %s\t\t",optarg);
        printf("optind = %d\t\t",optind);
        printf("argv[optind] = %s\n",argv[optind]);
    }




    for (int q = 1; q < argc; ++q)
    {
        printf("the command line input: %s\n", argv[q]);
    }
*/
    char sha[100];
    char *optstr = "i:o:g:st";
    if (argc == 1)
    {
        printf("please enter the code ' -i input_fileName -o output_fileName -g number_of_generations -g -s'follow!!! \n");
        return 1;
    }
    int i_num=1, o_num=1, g_num=1, s_num=1, t_num=1;
    while ((opt = getopt(argc, argv, optstr))!= -1)
    {
        switch (opt)
        {
            case 'i':
                if (!i_num)
                {
                    printf("'-i' repeated!!\n");
                    return 0;
                }

                if(!strcmp("-s", optarg) || !strcmp("-g", optarg) || !strcmp("-o", optarg) || !strcmp("-t", optarg))
                {
                    printf("wrong input command line: please input the correct input file name!\n");
                    return 0;
                }
                u1.inputFileName = optarg;
                printf("the opt i %s\n", u1.inputFileName);

                i_num = 0;
                break;
            case 'o':
                if (!o_num)
                {
                    printf("'-o' repeated!!\n");
                    return 0;
                }

                if(!strcmp("-s", optarg) || !strcmp("-g", optarg) || !strcmp("-i", optarg) || !strcmp("-t", optarg))
                {
                    printf("wrong input command line: please input the correct output file name!\n");
                    return 0;
                }
                u1.inputFileName = optarg;
                printf("the opt i %s\n", u1.inputFileName);

                o_num = 0;
                break;
            case 'g':
                if (!g_num)
                {
                    printf("'-g' repeated!!\n");
                    return 0;
                }
				
				if(!strcmp("-s", optarg) || !strcmp("-i", optarg) || !strcmp("-o", optarg) || !strcmp("-t", optarg))
                {
                    printf("wrong input command line: please input the correct number of generation!\n");
                    return 0;
                }
				
                u1.generation_num = atoi(optarg);
                printf("the opt g %d\n", u1.generation_num);
				
                g_num = 0;
                break;
            case 's':
                if (!s_num)
                {
                    printf("'-s' repeated!!\n");
                    return 0;
                }

                print_statistics = 1;
                printf("has s%d\n", print_statistics);
                s_num = 0;
                break;
            case 't':
                if (!t_num)
                {
                    printf("'-t' repeated!!\n");
                    return 0;
                }

                use_torus = 1;
                printf("has t %d\n", use_torus);
                t_num = 0;
                break;

            default:
                if(strchr(optstr, optopt) == NULL)
                {
                    fprintf(stderr, "unknown option '-%c'\n", optopt);
                }
                else
                {
                    fprintf(stderr, "option '-%c' requires an argument \n", optopt);
                }
                return 0;
        }
    }
    if (i_num==1)
    {
        printf("the input file name need to be entered!!\n");
        return 0;
    }
    //read_in_file(stdin,&u1);


    //read the file and get the row and column
    FILE *fp;
    fp = fopen("glider.txt","rt");

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

    u1.m = (int **)malloc(sizeof(int *) * u1.row);
    for (i = 0; i < row; ++i)
    {
    	u1.m[i] = (int *)malloc(sizeof(int) * u1.column);
    }

    row = 0;
    column = 0;

    while( (ch_in=fgetc(fp)) != EOF )
    {
        if (ch_in != '\n')
        {
            //printf("%c", ch_in);
            if (ch_in == '.')
            {
                u1.m[row][column] = 0;
            }
            else if (ch_in == '*')
            {
                u1.m[row][column] = 1;
            }
            else
            {
                printf("the input file is not correct\n");
                return 0;
            }
            column = column + 1;
        }
        if (ch_in == '\n')
        {
            row = row + 1;
            column = 0;
        }
    }

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
    struct matrix u_will;

    u_will.m = u->m;
    u_will.row = u->row;
    u_will.column = u->column;
    print_char (&u_will);
    printf("print the will matrix in int\n");
    for (int i = 0; i < u->row; ++i)
    {
        for (int j = 0; j < u->column; ++j)
        {
            if (j == u->column - 1)
            {
                printf("%d\n", u_will.m[i][j]);
            }
            else
            {
                printf("%d", u_will.m[i][j]);
            }
        }
    }
}

void print_char (struct matrix *u)
{
    printf("print the will matrix in char\n");
    for (int i = 0; i < u->row; ++i)
    {
        for (int j = 0; j < u->column; ++j)
        {
            if (j == u->column - 1)
            {
                if (u->m[i][j])
                {
                    printf("*\n");
                }
                else
                {
                    printf(".\n");
                }
            }
            else
            {
                if (u->m[i][j])
                {
                    printf("*");
                }
                else
                {
                    printf(".");
                }
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
    printf("%d\n", u->outputFile);
    printf("%d\n", u->generation_num);

    /*while( (ch_in=fgetc(infile)) != EOF )
    {
        if (ch_in != '\n')
        {
            printf("%c", ch_in);
        }
        if (ch_in == '\n')
        {
            printf("\n");
        }
    }*/
}
