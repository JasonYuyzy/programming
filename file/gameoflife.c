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

    int opt, print_statistics=0, use_torus=0;

    char *optstr = "i:o:g:st";
    if (argc == 1)
    {
        printf("please enter the code ' -i input_fileName -o output_fileName -g number_of_generations -g -s'follow!!! \n");
        return 0;
    }
	//set the numbr to check the command line option
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
                u.inputFileName = optarg;
                printf("the opt i %s\n", u.inputFileName);

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
                u.inputFileName = optarg;
                printf("the opt i %s\n", u.inputFileName);

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
				else if (atoi(optarg) ==0 || optarg != int)
				{
					print("wrong input command line: please input the correct number of generation!\n");
					return 0;
				}
                u.generation_num = atoi(optarg);
                printf("the opt g %d\n", u.generation_num);
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
                    printf("option '-t' repeated!!\n");
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
	//check the option '-i' whether inputed
    if (i_num==1)
    {
        printf("the input file name need to be entered!!\n");
        return 0;
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