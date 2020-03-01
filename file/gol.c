#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include"gol.h"

#define MAX 800
#define LEN 800

void read_in_file (FILE *infile, struct universe *u)
{
    //read the file and get the row and column
    int i, j, row = 0, column = 0, check_column = 0;
    char ch, ch_in;
    if (u->inputFile)
    {
        infile = fopen(u->inputFileName,"r");
		if (infile == NULL)
		{
		    perror("The input file name is not correct");
			exit(1);
		}
        while ( (ch=fgetc(infile)) != EOF )
        {
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
                    fprintf(stderr, "Error: The number of the row is different from others\n");
                    exit(1);
                }
                else
                {
                    row = row + 1;
                    check_column = column;
                    //set the column in the struct universe
                    u->column = column;
                    column = 0;
                }
            }
        }
        fseek(infile,0,SEEK_SET);
		
		if (row == 0 || u->column == 0)
		{
			fprintf(stderr, "Error: The input file is empty!\n");
			exit(1);
		}

		//if no blank in the last row, make the input file readable
		if ( column != 0)
		{
		    row = row + 1;
		}
        //set the row in the struct universe
        u->row = row;

        u->mat = (int **)malloc(sizeof(int *) * u->row);
        for (i = 0; i < u->row; ++i)
        { //distribute every column base on each row
        	u->mat[i] = (int *)malloc(sizeof(int) * u->column);
        }

        u->whole_life = u->row * u->column;

        row = 0;
        column = 0;

        while( (ch_in=fgetc(infile)) != EOF )
        {
            if (ch_in != '\n')
            {
                //printf("%c", ch_in);
                if (ch_in == '.')
                {
                    u->mat[row][column] = 0;
                }
                else if (ch_in == '*')
                {
                    u->mat[row][column] = 1;
                }
                else
                {
                    fprintf(stderr, "Error: The input file data is not correct\n");
                    exit(1);
                }
                column = column + 1;
            }
            if (ch_in == '\n')
            {
                row = row + 1;
                column = 0;
            }
            //printf("Yes %d, %d\n", row, column);
        }
		fclose(infile);

        printf("successfully read in file!\n");
    }
    else
    {
        //read the command line input file
        //printf("Please input the life map, press 'Enter' to finish the input:\n");
        char input[MAX][LEN];
        int check_len = 0;
        int len;
        for (i = 0; i < MAX; ++i)
        {
            fgets(input[i], sizeof(input[i]), stdin);
            if (strcmp(input[i], "\n") == 0)
            {
                break;
            }

            if (i == 0)
            {
                len = strlen(input[i]);
                check_len = len;
            }
            len = strlen(input[i]);
            if (check_len != len)
            {
                fprintf(stderr, "Error: The length is not match with other rows!\n");
                exit(1);
            }
            check_len = len;
        }
		
		if (i == 0)
		{
			fprintf(stderr, "Error: Nothing inputted!\n");
			exit(1);
		}
        u->row = i;
        u->column = len - 1;

        u->mat = (int **)malloc(sizeof(int *) * u->row);
        for (i = 0; i < u->row; ++i)
        { //distribute every column base on each row
        	u->mat[i] = (int *)malloc(sizeof(int) * u->column);
        }
        u->whole_life = u->row * u->column;

        row = 0;
        column = 0;

        for (i = 0; i < u->row; ++i)
        {
            for (j = 0; j < u->column; ++j)
            {
                if (input[i][j] == '.')
                {
                    u->mat[i][j] = 0;
                }
                else if (input[i][j] == '*')
                {
                    u->mat[i][j] = 1;
                }
                else if (input[i][j] == '\n')
                {
                    //printf("\n");
                    continue;
                }
                else
                {
                    fprintf(stderr, "Error: The input file data is not correct\n");
                    exit(1);
                }
            }
        }
        printf("Data input successfully!\n");
    }
	return;
}

void write_out_file (FILE *outfile, struct universe *u)
{
	if (u->outputFile)
	{
		//result put into the file
		outfile = fopen(u->outputFileName, "w");
		for (int i = 0; i < u->row; ++i)
		{
			for (int j = 0; j < u->column; ++j)
			{
				if (j == u->column - 1)
				{
					//change the line
					if (u->mat[i][j])
					{
						fputc('*', outfile);
						fputs("\n", outfile);
					}
					else
					{
						fputc('.', outfile);
						fputs("\n", outfile);
					}
				}
				else
				{
					if (u->mat[i][j])
					{
						fputc('*', outfile);
					}
					else
					{
						fputc('.', outfile);
					}
				}
			}
		}
		fclose(outfile);
        //free the matrix
		for (int i = 0; i < u->row; ++i)
        {
            free(*(u->mat + i));
        }
	}
	else
	{
		//the result put on screen
		printf("The final result on screen for %0.f generations:\n", u->generation_num);
		for (int i = 0; i < u->row; ++i)
		{
			for (int j = 0; j < u->column; ++j)
			{
				if (j == u->column - 1)
				{
					if (u->mat[i][j])
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
					if (u->mat[i][j])
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
		//free the matrix
        for (int i = 0; i < u->row; ++i)
        {
            free(*(u->mat + i));
        }
	}
}

int is_alive (struct universe *u, int column, int row)
{
    if (u->mat[row][column])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int will_be_alive (struct universe *u, int column, int row)
{
	int alive=0, i=0, j=0;
	if (row == 0 && column == 0)
	{//top left
		alive = alive + u->mat[0][0];
		alive = alive + u->mat[0][1];
		alive = alive + u->mat[1][0];
		alive = alive + u->mat[1][1];
	}
	else if (row == 0 && column == u->column-1)
	{//top right
		alive = alive + u->mat[0][column-1];
		alive = alive + u->mat[0][column];
		alive = alive + u->mat[1][column-1];
		alive = alive + u->mat[1][column];
	}
	else if (row == u->row - 1 && column == 0)
	{//button left
		alive = alive + u->mat[row-1][column];
		alive = alive + u->mat[row-1][column+1];
		alive = alive + u->mat[row][column];
		alive = alive + u->mat[row][column+1];
	}
	else if (row == u->row - 1 && column == u->column - 1)
	{//button right
		alive = alive + u->mat[row-1][column-1];
		alive = alive + u->mat[row-1][column];
		alive = alive + u->mat[row][column-1];
		alive = alive + u->mat[row][column];
	}
	else if (row == 0)
	{//top row
		for (i = row; i<= row + 1; ++i)
		{
			for (j = column - 1; j <= column + 1; ++j)
			{
				alive = alive + u->mat[i][j];
			}
		}		
	}
	else if (column == 0)
	{//leftmost column
		for (i = row - 1; i <= row + 1; ++i)
		{
			for (j = column; j <= column + 1; ++j)
			{
				alive = alive + u->mat[i][j];
		    }
		}
	}
	else if (row == u->row - 1)
	{//button row
		for (i = row - 1; i <= row; ++i)
		{
			for (j = column - 1; j <= column + 1; ++j)
			{
				alive = alive + u->mat[i][j];
			}
		}
	}
	else if (column == u->column - 1)
	{//rightmost column
		for (i = row - 1; i <= row + 1; ++i)
		{
			for (j = column - 1; j <= column; ++j)
			{
				alive = alive + u->mat[i][j];
			}
		}
	}
	else
	{//normal
		for (i = row - 1; i <= row + 1; ++i)
		{
			for (j = column - 1; j <= column + 1; ++j)
			{
				alive = alive + u->mat[i][j];
			}
		}
	}
	
	return alive;
}

int will_be_alive_torus (struct universe *u, int column, int row)
{
	int alive=0, i=0, j=0;
	for (i = row - 1; i <= row + 1; ++i)
	{
		for (j = column - 1; j <= column + 1; ++j)
		{
			alive = alive + u->mat[(i+u->row)%u->row][(j+u->column)%u->column];
		}
	}
	return alive;
}

void evolve (struct universe *u, int (*rule)(struct universe *u, int column, int row))
{
    //struct universe u_will;
    int check, i, j, self_alive, count=0;

	//second use the local matrix
	int **will;
	will = (int **)malloc(sizeof(int *) * u->row);
	for (i = 0; i < u->row; ++i)
    { //distribute every column base on each row
        will[i] = (int *)malloc(sizeof(int) * u->column);
    }

    if (u->finished)
     {
        for (int i = 0; i < u->row; ++i)
        {
            free(*(will + i));
        }
        exit(0);
    }

    for (i = 0; i < u->row; ++i)
    {
        for (j = 0; j < u->column; ++j)
        {
            check = rule( u, j, i);
            self_alive = is_alive ( u, j, i);
            if (check == 3 && self_alive == 0)
            {
                u->alive_num = u->alive_num + 1;
                will[i][j] = 1;
            }
            else if ((check == 3 || check == 4) && self_alive == 1)
            {
                u->alive_num = u->alive_num + 1;
                will[i][j] = 1;
            }
            else
            {
                will[i][j] = 0;
            }
        }
    }
	u->mat = will;
	
	count = count + 1;
}

void print_statistics (struct universe *u)
{
    u->statistic = u->alive_num/u->whole_life;
	printf("%.3f of cells currently alive\n", u->statistic);
    u->alive_average = u->alive_average + u->statistic/u->generation_num;
    u->alive_num = 0;
}
