struct universe 
{
/*Put some appropriate things here*/
    int **mat;
    int column;
    int row;
	char *inputFileName;
	char *outputFileName;
	int inputFile;
	int outputFile;
	int generation_num;
	int alive_num;
	float alive_average;
	int whole_life;
	float statistic;
	int print_statistics;
};

/*Do not modify the next seven lines*/
void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
int will_be_alive_torus(struct universe *u,  int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);
/*You can modify after this line again*/


#define MAX 100
#define LEN 800

void read_in_file (FILE *infile, struct universe *u)
{
    //read the file and get the row and column
    int i, j, row = 0, column = 0, check_column = 0;
    char ch, ch_in;
    if (u->inputFile)
    {
        infile = fopen(u->inputFileName,"rt");

        while( (ch=fgetc(infile)) != EOF )
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
                    printf("the column is missing\n");
                    return;
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
                    printf("the input file is not correct\n");
                    return ;
                }
                column = column + 1;
            }
            if (ch_in == '\n')
            {
                row = row + 1;
                column = 0;
            }
        }
        printf("successfully read in file!!!\n");
    }
    else
    {
        //read the command line input
        char input[MAX][LEN];
        int check_len = 0;
        int len;
        for (i = 0; i < MAX; ++i)
        {
            gets(input[i]);
            if (!*input[i])
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
                printf("the length is not correct!\n");
                return;
            }
        }
        u->row = i;
        u->column = len;

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
                else
                {
                    printf("the input file is not correct\n");
                    return;
                }
            }
        }
        printf("input successfully!\n");
    }
}

void write_out_file (FILE *outfile, struct universe *u)
{
	if (u->outputFile)
	{
		//result put into the file
		outfile = fopen(u->outputFileName, "w+");
		fputs("this is the final life:\n", outfile);
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
		printf("the final result:\n");
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
        //for (int i = 0; i < u->row; ++i)
        //{
            //free(*(u->mat + i));
        //}
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
	struct universe check;
    check.mat = u->mat;
	
	int alive = 0;
    if (row == 0 && column == 0)
    {
    //top left
        //right
        if (u->mat[row][column+1])
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column])
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1])
        {
            alive = alive + 1;
        }
    }
    else if (row == 0 && column == u->column - 1)
    {
    //the top right corner
        //left
        if (u->mat[row][column-1])
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1])
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column])
        {
            alive = alive + 1;
        }
    }
    else if (row == u->row - 1 && column == u->column - 1)
    {
    //in the right down corner
        //top middle
        if (u->mat[row-1][column])
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row-1][column-1])
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1])
        {
            alive = alive + 1;
        }
    }
    else if (row == u->row - 1 && column == 0)
    {
    //the left down corner
        //top middle
        if (u->mat[row-1][column])
        {
            alive = alive + 1;
        }
        //top right
        if (u->mat[row-1][column+1])
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1])
        {
            alive = alive + 1;
        }
    }
    else if (row == 0)
    {
    //up row
        //left
        if (u->mat[row][column-1])
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1])
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1])
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column])
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1])
        {
            alive = alive + 1;
        }
    }
    else if (column == 0)
    {
    //left most column
        //top middle
        if (u->mat[row-1][column])
        {
            alive = alive + 1;
        }
        //top right
        if (u->mat[row-1][column+1])
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1])
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column])
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1])
        {
            alive = alive + 1;
        }
    }
    else if (row == u->row - 1)
    {
    //in the bottom row
        //right
        if (u->mat[row][column+1])
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1])
        {
            alive = alive + 1;
        }
        //top middle
        if (u->mat[row-1][column])
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row-1][column-1])
        {
            alive = alive + 1;
        }
        //top right
        if (u->mat[row-1][column+1])
        {
            alive = alive + 1;
        }
    }
    else if (column == u->column - 1)
    {
    //right most column
        //top middle
        if (u->mat[row-1][column])
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row-1][column-1])
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1])
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1])
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column])
        {
            alive = alive + 1;
        }
    }
    else
    {
        //top right
        if (u->mat[row-1][column+1])
        {
            alive = alive + 1;
        }
        //top middle
        if (u->mat[row-1][column])
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row-1][column-1])
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1])
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1])
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1])
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column])
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1])
        {
            alive = alive + 1;
        }
    }

    int self_alive = is_alive ( &check, column, row);
    if ( self_alive && alive >= 2)
    {
        return 1;
    }
    else if ( !self_alive && alive >= 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int will_be_alive_torus (struct universe *u, int column, int row)
{
	struct universe check;
	check.mat = u->mat;
	
    int alive = 0;
    if (u->mat[(row-1+(u->row))%(u->row)][(column-1+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //top middle
    if (u->mat[(row-1+(u->row))%(u->row)][(column+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //top right
    if (u->mat[(row-1+(u->row))%(u->row)][(column+1+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //left
    if (u->mat[(row+(u->row))%(u->row)][(column-1+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //right
    if (u->mat[(row+(u->row))%(u->row)][(column+1+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //down left
    if (u->mat[(row+1+(u->row))%(u->row)][(column-1+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //down
    if (u->mat[(row+1+(u->row))%(u->row)][(column+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }
    //down right
    if (u->mat[(row+1+(u->row))%(u->row)][(column+1+(u->column))%(u->column)])
    {
        alive = alive + 1;
    }

    //printf(" the alive num !!!!!%d\n", alive);

    int self_alive = 0;
    self_alive = is_alive ( &check, column, row);
    if ( self_alive && alive >= 2)
    {
        return 1;
    }
    else if ( !self_alive && alive >= 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void evolve (struct universe *u, int (*rule)(struct universe *u, int column, int row))
{
    struct universe u_will;
    int check, i, j;

    u_will.mat = u->mat;
    u_will.column = u->column;
    u_will.row = u->row;

    for (i = 0; i < u->row; ++i)
    {
        for (j = 0; j < u->column; ++j)
        {
            check = 0;
            check = rule( &u_will, j, i);
            if (check)
            {
                u->alive_num = u->alive_num + 1;
                u->mat[i][j] = 1;
            }
            else
            {
                u->mat[i][j] = 0;
            }
        }
    }
    printf("alive number%d\n", u->alive_num);
    return;
}

void print_statistics (struct universe *u)
{
    u->statistic = u->alive_num / u->whole_life;
    u->alive_average = u->alive_average + u->statistic/u->generation_num;
    u->alive_num = 0;
}

