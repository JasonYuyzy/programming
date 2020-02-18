struct universe 
{
/*Put some appropriate things here*/
    char **mat;
    int column;
    int row;
	char *inputFileName;
	char *outputFileName;
	int generation_num;
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

void read_in_file (FILE *infile, struct universe *u)
{
    //read the file and get the row and column
    infile = fopen(u->inputFileName,"rt");

    char ch, ch_in;

    int i, j, row = 0, column = 0, check_column = 0;

    while( (ch=fgetc(infile)) != EOF )
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
                printf("the column is missing\n");
                return 0;
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

    u->mat = (char **)malloc(sizeof(char *) * u->row);
    for (i = 0; i < row; ++i)
    { //distribute every column base on each row
    	u->mat[i] = (char *)malloc(sizeof(char) * u->column);
    }

    row = 0;
    column = 0;
    while( (ch_in=fgetc(infile)) != EOF )
    {
        if (ch_in != '\n')
        {
            printf("%c", ch_in);
            u->mat[row][column] = ch_in;
            column = column + 1;
        }
        if (ch == '\n')
        {
            printf("\n");
            row = row + 1;
            column = 0;
        }
    }

}

void write_out_file (FILE *outfile, struct universe *u)
{
    outfile = fopen(u->outputFileName, "w+");
    fputs("this is the final life:\n", outfile);
    for (int i = 0; i < u->row; ++i)
    {
        for (int j = 0; j < u->column; ++j)
        {
            if (j == u->column - 1)
            {
                //change the line
                fputc(u->mat[i][j], outfile);
                fputs("\n", outfile);
            }
            else
            {
                fputc(u->mat[i][j], outfile);
            }
        }
    }
    fclose(outfile);
}

int is_alive (struct universe *u, int column, int row)
{
    if (u->mat[row][column] == '*')
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
    int alive = 0;
    if (row == 0 && column == 0)
    {
        //right
        if (u->mat[row][column+1] == '*')
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (row == 0)
    {
    //up row
        //left
        if (u->mat[row][column-1] == '*')
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1] == '*')
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (column == 0)
    {
    //right most column
        //top middle
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //top right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1] == '*')
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (row == 0 && column == u->column)
    {
    //the right up corner
        //left
        if (u->mat[row][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (row == u->row && column == u->column)
    {
    //in the down right corner
        //top middle
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (row == u->row && column == 0)
    {
    //the left down corner
        //top middle
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //top right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (row == u->row)
    {
    //in the bottom row
        //right
        if (u->mat[row][column+1] == '*')
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1] == '*')
        {
            alive = alive + 1;
        }
        //top middle
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //top right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
    }
    else if (column == u->column)
    {
    //in the left column
        //top middle
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
    }
    else
    {
        //top right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
        //top middle
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //top left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //right
        if (u->mat[row][column+1] == '*')
        {
            alive = alive + 1;
        }
        //left
        if (u->mat[row][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down left
        if (u->mat[row+1][column-1] == '*')
        {
            alive = alive + 1;
        }
        //down
        if (u->mat[row+1][column] == '*')
        {
            alive = alive + 1;
        }
        //down right
        if (u->mat[row+1][column+1] == '*')
        {
            alive = alive + 1;
        }
    }

    int check = is_alive ( &u, column, row);
    if (check == 1 && alive >= 2)
    {
        return 1;
    }
    else if ( check == 0 && alive >= 3)
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
    int alive = 0;
    if (u->mat[(row-1+(u->row))%(u->row)][(column-1+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //top middle
    if (u->mat[(row-1+(u->row))%(u->row)][(column+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //top right
    if (u->mat[(row-1+(u->row))%(u->row)][(column+1+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //left
    if (u->mat[(row+(u->row))%(u->row)][(column-1+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //right
    if (u->mat[(row+(u->row))%(u->row)][(column+1+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //down left
    if (u->mat[(row+1+(u->row))%(u->row)][(column-1+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //down
    if (u->mat[(row+1+(u->row))%(u->row)][(column+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }
    //down right
    if (u->mat[(row+1+(u->row))%(u->row)][(column+1+(u->column))%(u->column)] == '*')
    {
        alive = alive + 1;
    }

    int check = is_alive ( &u, column, row);
    if (check == 1 && alive >= 2)
    {
        return 1;
    }
    else if ( check == 0 && alive >= 3)
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
    char **u_will;
    int check, i, j;
    u_will = u->mat;
    for (i = 0; i < u->row; ++i)
    {
        for (j = 0; j < u->column; ++j)
        {
            check = rule( &u, j, i);
            if (check)
            {
                u_will[i][j] = '*';
            }
            else
            {
                u_will[i][j] = '.';
            }
        }
    }
    u->mat = u_will;
}

void print_statistics (struct universe *u)
{
    //release the space for the matrix when every time the program finished
    for (int i = 0; i < u->row; ++i)
    {
    	free(*(u->mat + i));
    }
}
