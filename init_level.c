#include "init_level.h"

void import_level(int mat[200][300], FILE * level_file)
{
    int pos_x, pos_y;
    int i = 0, j = 0;

    fscanf(level_file, "%d", &pos_x);
    fscanf(level_file, "%d", &pos_y);
    
    for (i=0; i < 200; i++)
    {
        for (j=0;j < 300; j++)
        {
            fscanf(level_file, "%d", &mat[i][j]);
        }
    }
}

void import_file(int mat[200][300], FILE * level_file)
{
    FILE * file = fopen(level_file, "r");
    if (file)
    {
        import_level(mat, file);
    }

    fclose(file);
}