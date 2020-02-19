#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>

#include"gol.h"


void print_m (struct matrix *u);

int main(int argc, char *argv[])
{
    struct universe u;

    int opt, print_statistics, use_torus;

    char *string = "sti:o:g:";

    while ((opt = getopt(argc, argv, string))!= -1)
    {
        switch (opt)
        {
            case 'i':
                if (optarg)
                {
                    u.inputFileName = optarg;
                    printf("the opt i %s\n", u.inputFileName);
                }
                else
                {
                    printf("Please input the file name: \n");
                }
                continue;
            case 'o':
                if (optarg)
                {
                    u.outputFileName = optarg;
                    printf("the opt o %s\n", u.outputFileName);
                }
                else
                {
                    u.outputFile = 0;
                    printf("the opt o %d\n", outputFile);
                }
                continue;
            case 'g':
                if (optarg)
                {
                    u.generation_num = atoi(optarg);
                    printf("the opt g %d\n", u.generation_num);
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

    read_in_file(FILE *infile, &u);

    for (int i = 0; i < u.generation_num; ++i)
    {
        if (use_tours)
        {
            evolve(&u,will_be_alive);
        }
        else
        {
            evolve(&u,will_be_alive_torus);
        }
    }

    if (print_statistics)
    {
        write_out_file(FILE *outfile, &u);
    }
    else
    {
        print_m(&u);
    }

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