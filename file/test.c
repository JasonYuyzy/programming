struct universe {
/*Put some appropriate things here*/
    char **mat;
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
    struct universe u_new;
    struct universe u_previous;

    u_new.mat = (char **)malloc(sizeof(char *) * height(row));
    for (i = 0; i < 10; i ++)
    { //distribute every column base on each row
    	u_new.mat[i] = (char *)malloc(sizeof(char) * width(column));
    }

    u_previous.mat = (char **)malloc(sizeof(char *) * 10);
    for (i = 0; i < 10; i ++)
    { //distribute every column base on each row
    	u_previous.mat = (char *)malloc(sizeof(char) * 10);
    }
}

void write_out_file (FILE *outfile, struct universe *u)
{

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
    if (universe *u [(row-1+height)%height][(column-1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //top middle
    if (universe *u [(row-1+height)%height][(column+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //top right
    if (universe *u [(row-1+height)%height][(column+1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //left
    if (universe *u [(row+height)%height][(column-1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //right
    if (universe *u [(row+height)%height][(column+1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //down left
    if (universe *u [(row+1+height)%height][(column-1+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //down
    if (universe *u [(row+1+height)%height][(column+width)%width] == '*')
    {
        alive = alive + 1;
    }
    //down right
    if (universe *u [(row+1+height)%height][(column+1+width)%width] == '*')
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

}

void print_statistics (struct universe *u)
{

}