#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include"gol.h"

int main(int argc, char *argv[])
{
    struct universe u;

    int i_num=1, o_num=1, g_num=1, s_num=1, t_num=1;
    int i, use_torus=0, print_stat=0;
    char *include = ".txt";

    for (i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-' && !argv[1][2])
        {
            switch (argv[i][1])
            {
                case 'i':
                    //if(!strcmp("-s", argv[i+1]) || !strcmp("-g", argv[i+1]) || !strcmp("-o", argv[i+1]) || !strcmp("-t", argv[i+1]))
                    //{
                        //perror("Error: Wrong input command line, please input the correct input file name if you have '-i'!\n");
                        //exit(1);
                    //}

                    if (!argv[i+1])
                    {
                        fprintf(stderr, "Error: The file name can not use with empty string!\n");
                        exit(1);
                    }

                    if (i_num == 0)
                    {
                        if (strcmp(u.inputFileName, argv[i+1]) != 0)
                        {
                            fprintf(stderr, "Error: The file name input is not correct!\n");
                            exit(1);
                        }
                    }
                    u.inputFileName = argv[i+1];
                    u.inputFile = 1;

                    //if (!strstr (u.inputFileName, include))
            		//{
            			//perror("Error: The input file name need to include with '.txt', please try again!\n");
            			//exit(1);
            		//}

            		i_num = 0;
                    break;
                case 'o':
                    if (!o_num)
                    {
                        fprintf(stderr, "Error: The option '-o' repeated!!\n");
                        exit(1);
                    }

                    if(!strcmp("-s", argv[i+1]) || !strcmp("-g", argv[i+1]) || !strcmp("-i", argv[i+1]) || !strcmp("-t", argv[i+1]))
                    {
                        fprintf(stderr, "Error: Wrong input command line, please input the correct output file name!\n");
                        exit(1);
                    }
                    if (!argv[i+1])
                    {
                        fprintf(stderr, "Error: the output file name is empty!\n");
                        exit(1);
                    }
                    u.outputFileName = argv[i+1];
                    u.outputFile = 1;


            		if (!strstr (u.outputFileName, include))
            		{
            			fprintf(stderr, "Error: The output file name need to include with '.txt', please try again!\n");
            			exit(1);
            		}

                    o_num = 0;
                    break;
                case 'g':
                    if (!g_num)
                    {
                        fprintf(stderr, "Error: The option '-g' repeated!!\n");
                        exit(1);
                    }

    				/*if(!strcmp("-s", argv[i+1]) || !strcmp("-i", argv[i+1]) || !strcmp("-o", argv[i+1]) || !strcmp("-t", argv[i+1]))
                    {
                        perror("Error: wrong input command line, please input the correct number of generation!\n");
                        exit(1);
                    }*/
                    if (!argv[i+1])
    				{
    				    fprintf(stderr, "Error: The generation number is empty!\n");
    				    exit(1);
    				}
    				if (atoi(argv[i+1]) == 0)
    				{
    					perror("Error argument of the generation number");
    					exit(1);
    				}

                    u.generation_num = atof(argv[i+1]);
                    if ( atof(argv[i+1]) != (int)atof(argv[i+1]) )
                    {
                        fprintf(stderr, "Error: Please input the integer for the generation number!\n");
                        exit(1);
                    }
                    g_num = 0;
                    break;
                case 's':
                    if (!s_num)
                    {
                        fprintf(stderr, "Error: The option '-s' repeated!!\n");
                        exit(1);
                    }

                    print_stat = 1;
                    s_num = 0;
                    break;
                case 't':
                    if (!t_num)
                    {
                        fprintf(stderr, "Error: The option '-t' repeated!\n");
                        exit(1);
                    }

                    use_torus = 1;
                    t_num = 0;
                    break;
                default:
                    fprintf(stderr, "Error: unknown option '-%c'\n", argv[i][1]);
                    exit(1);
            }
        }
    }
    if (i_num)
    {
        u.inputFile = 0;
    }
    if (o_num)
    {
        u.outputFile = 0;
    }
    if (t_num)
    {
        use_torus = 0;
    }
    if (s_num)
    {
        print_stat = 0;
    }
    if (g_num)
    {
        u.generation_num = 5;
    }

    FILE *infile = NULL;
    FILE *outfile = NULL;

    u.alive_num = 0;
    u.alive_average = 0;
    u.column = 0;
    u.row = 0;
    u.finished = 0;
    read_in_file(infile, &u);

    for ( i = 0; i < u.generation_num; ++i)
    {
        if (use_torus)
        {
            evolve(&u,will_be_alive_torus);
		}
        else
        {
            evolve(&u,will_be_alive);
		}
		
		if (print_stat)
		{
			print_statistics (&u);
		}
    }
	
	if (print_stat)
	{
		printf("%.3f of cells alive on average\n", u.alive_average);
	}
    write_out_file(outfile, &u);

    //free the matrix will and exit(0);
    u.finished = 1;
    evolve( &u, will_be_alive);
}
