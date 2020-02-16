struct universe {
/*Put some appropriate things here*/
    char **mat;
    int column;
    int row;
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
    struct universe u_now;

    //read the file and get the row and column
    infile = fopen("glider.txt","rt");

    char ch;

    int row = 0, column = 0, check_column = 0;

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
                printf("%d, %d", row, column);
                check_column = column;
                column = 0;
            }
            else if (check_column != column)
            {
                return error;
            }
            else
            {
                row = row + 1;
                check_column = column;
                //set the column in the struct universe
                u_new.column = column;
                column = 0;
            }
        }
    }
    fseek(infile,0,SEEK_SET);

    //set the row in the struct universe
    u_now.row = row;

    u_now.mat = (char **)malloc(sizeof(char *) * row);
    for (i = 0; i < row; i ++)
    { //distribute every column base on each row
    	u_now.mat[i] = (char *)malloc(sizeof(char) * column);
    }

    while( (ch=fgetc(infile)) != EOF )
    {
        if (ch != '\n')
        {
            printf("%c", ch);
            u_now.mat[row][column] = ch;
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
    outfile = fopen("test.txt", "w+");
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
    if (u->mat[(row-1+height)%height][(column-1+width)%width] == '*')
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
    else if (row == 0 && column == width)
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
    else if (row == height && column == width)
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
    else if (row == height && column == 0)
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
    else if (row == height)
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
    else if (column == width)
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

    if (is_alive && alive > 2)
    {
        return 1;
    }
    else if ( !is_alive && alive > 3)
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
    if (u->mat[(row-1+height)%height][(column-1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //top middle
    if (u->mat[(row-1+height)%height][(column+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //top right
    if (u->mat[(row-1+height)%height][(column+1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //left
    if (u->mat[(row+height)%height][(column-1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //right
    if (u->mat[(row+height)%height][(column+1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //down left
    if (u->mat[(row+1+height)%height][(column-1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //down
    if (u->mat[(row+1+height)%height][(column+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //down right
    if (u->mat[(row+1+height)%height][(column+1+width)%width] == '*')
    {
        alive = alive + 1;
    }

    if (is_alive && alive > 2)
    {
        return 1;
    }
    else if ( !is_alive && alive > 3)
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
    int check;
    u_will = u->mat;
    if (chose the normal)
    {
        for (int i = 0; i < n->row; ++i)
        {
            for (int j = 0; j < u->column; ++j)
            {
                check = will_be_alive ( &->mat, j, i);
                if (check)
                {
                    u_will.mat[i][j] = '*';
                }
                else
                {
                    u_will.mat[i][j] = '.';
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < n->row; ++i)
        {
            for (int j = 0; j < u->column; ++j)
            {
                check = will_be_alive_torus ( &u->mat, j, i);
                if (check)
                {
                    u_will.mat[i][j] = '*';
                }
                else
                {
                    u_will.mat[i][j] = '.';
                }
            }
        }
    }
}

void print_statistics (struct universe *u)
{

    //release the space for the matrix when every time the program finished
    for (int i = 0; i < u->row; ++i)
    {
    	free(*(u->mat + i));
    }
}