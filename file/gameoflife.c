#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>

#include"gol.h"

int main(int argc, char *argv[])
{
    struct universe u;

    int opt, use_torus=0, print_stat=0, generation_num=0;

    char *optstr = "i:o:g:st";
	//set the number to check the command line option
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
                u.inputFile = 1;

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
                u.outputFileName = optarg;
                u.outputFile = 1;

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
				else if (atoi(optarg) ==0)
				{
					printf("wrong input command line: please input the correct number of generation!\n");
					return 0;
				}
                generation_num = atoi(optarg);
                g_num = 0;
                break;
            case 's':
                if (!s_num)
                {
                    printf("'-s' repeated!!\n");
                    return 0;
                }

                print_stat = 1;
                s_num = 0;
                break;
            case 't':
                if (!t_num)
                {
                    printf("option '-t' repeated!!\n");
                    return 0;
                }

                use_torus = 1;
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
        generation_num = 5;
    }

    FILE *infile = NULL;
    FILE *outfile = NULL;

    u.column = 0;
    u.row = 0;

    read_in_file(infile, &u);

    u.alive_num = 0;
    u.alive_average = 0;
    u.alive_average = 0;

    for (int i = 0; i < generation_num; ++i)
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
        //printf("%f of the cells currently alive \n", u.statistic);
        //write_out_file(outfile, &u);
    }
	
	if (print_stat)
	{
		printf("%f of cells alive on average\n", u.alive_average);
	}


    write_out_file(outfile, &u);


    return 0;
}
