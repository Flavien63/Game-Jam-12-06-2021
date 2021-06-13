#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*Compile avec : gcc level_editor.c -o level_design -g -Wall -Wextra*/

void ajout_sol_vie(int mat[200][300], int pos_x_deb, int pos_y_deb, int pos_x_fin, int pos_y_fin)
{
    srand(time(0));
    int r = rand();

    if ((pos_x_deb >= 0) && (pos_y_deb >= 0) && (pos_x_fin < 200) && (pos_y_fin < 300))
    {
        for (int i = pos_x_deb; i < pos_x_fin + 1; i++)
        {
            for (int j = pos_y_deb; j < pos_y_fin + 1; j++)
            {
                if ((i < pos_x_deb + 3) && (mat[i][j] == 0))
                    mat[i][j] = 2;
                else
                {
                    if ((i == pos_x_deb + 3) && (mat[i][j] == 0) && (j % 2 == 1))
                        mat[i][j] = 2;
                    else
                    {
                        if (r % 25 == 1)
                            mat[i][j] = 5;
                        else
                            mat[i][j] = 1;
                    }
                    r = rand();
                }
            }
        }
    }
}

void ajout_sol_mort(int mat[200][300], int pos_x_deb, int pos_y_deb, int pos_x_fin, int pos_y_fin)
{
    srand(time(0));
    int r = rand();

    if ((pos_x_deb >= 0) && (pos_y_deb >= 0) && (pos_x_fin < 200) && (pos_y_fin < 300))
    {
        for (int i = pos_x_deb; i < pos_x_fin + 1; i++)
        {
            for (int j = pos_y_deb; j < pos_y_fin + 1; j++)
            {
                if ((i < pos_x_deb + 3) && (mat[i][j] == 0))
                    mat[i][j] = 2;
                else
                {
                    if ((i == pos_x_deb + 3) && (mat[i][j] == 0) && (j % 2 == 1))
                        mat[i][j] = 2;
                    else
                    {
                        if (r % 25 == 1)
                            mat[i][j] = 5;
                        else
                            mat[i][j] = 1;
                    }
                    r = rand();
                }
            }
        }
    }
}

void ajout_cadre_noir(int mat[200][300])
{
    for (int i = 0; i < 200; i ++)
    {
        for (int j = 0; j < 300; j ++)
        {
            if ((i == 0) || (j == 0) || (i == 199) || (j == 299))
                mat[i][j] = 6;
        }
    }
}

void ajout_coupe(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_x + 14 < 200) && (pos_y >= 0) && (pos_y + 14 < 300))
    {
        for (int i = pos_x; i < pos_x + 14; i++)
        {
            for (int j = pos_y; j < pos_y + 14; j++)
            {
                if ((i == pos_x) && (j <= pos_y + 12) && (j >= pos_y + 2))
                    mat[i][j] = 32;
                if ((i == pos_x + 1) && (j <= pos_y + 13) && (j >= pos_y + 1))
                    mat[i][j] = 32;
                if (((i == pos_x + 2) || (i == pos_x + 3)) && ((j == pos_y) || (j == pos_y + 13) || ((j <= pos_y + 10) && (j >= pos_y + 3))))
                    mat[i][j] = 32;
                if ((i == pos_x + 4) && ((j == pos_y + 1) || ((j <= pos_y + 9) && (j >= pos_y + 4)) || (j == pos_y + 12)))
                    mat[i][j] = 32;
                if ((i == pos_x + 5) && ((j == pos_y + 2) || ((j <= pos_y + 8) && (j >= pos_y + 5)) || (j == pos_y + 11) || (j == pos_y + 10) || (j == pos_y + 3)))
                    mat[i][j] = 32;
                if (((i >= pos_x + 6) && (i <= pos_x + 9)) && ((j == pos_y + 6) || (j == pos_y + 7)))
                    mat[i][j] = 32;
                if (((i >= pos_x + 10) && (i <= pos_x + 13)) && ((j >= pos_y + 4) && (j <= pos_y + 9)))
                    mat[i][j] = 32;
            }
        }
    }
}

void ajout_bulle(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_x + 14 < 200) && (pos_y >= 0) && (pos_y + 14 < 300))
    {
        for (int i = pos_x; i < pos_x + 14; i++)
        {
            for (int j = pos_y; j < pos_y + 14; j++)
            {
                if (((i == pos_x) || (i == pos_x + 13)) && ((j >= pos_y + 5) && (j <= pos_y + 8)))
                    mat[i][j] = 30;
                if (((i == pos_x + 1) || (i == pos_x + 12)) && ((j == pos_y + 3) || (j == pos_y + 4) || (j == pos_y + 9) || (j == pos_y + 10)))
                    mat[i][j] = 30;
                if (((i == pos_x + 2) || (i == pos_x + 11)) && ((j == pos_y + 2) || (j == pos_y + 11)))
                    mat[i][j] = 30;
                if (((j == pos_y + 1) || (j == pos_y + 12)) && ((i == pos_x + 3) || (i == pos_x + 4) || (i == pos_x + 9) || (i == pos_x + 10)))
                    mat[i][j] = 30;
                if (((j == pos_y) || (j == pos_y + 13)) && ((i >= pos_x + 5) && (i <= pos_x + 8)))
                    mat[i][j] = 30;
                if (((i == pos_x + 4) || (i == pos_x + 5)) && ((j == pos_y + 4) || (j == pos_y + 5)))
                    mat[i][j] = 30;
            }
        }
    }
}

void ajout_caillou(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_y >= 0) && (pos_x + 7 < 200) && (pos_y + 6 < 300))
    {
        for (int i = pos_x; i < pos_x + 7; i++)
        {
            for (int j = pos_y; j < pos_y + 6; j++)
            {
                if ((i == pos_x) && ((j == pos_y + 1) || (j == pos_y + 2)))
                    mat[i][j] = 4;
                if (((i == pos_x + 1) && (j < pos_y + 4)))
                    mat[i][j] = 4;
                if (((i == pos_x + 2) || (i == pos_x + 3)) && (j < pos_y + 5))
                    mat[i][j] = 4;
                if ((i == pos_x + 4) || (i == pos_x + 5))
                    mat[i][j] = 4;
                if ((i == pos_x + 6) && (j > pos_y + 1) && (j < pos_y + 5))
                    mat[i][j] = 4;
            }
        }
    }
}

void ajout_pic_vie(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_y>=0))
    {
        for (int i = 0; i< 8; i++)
        {
            for (int j = 0; j<5; j++)
            {
                if (((i==4) && (j == 2)) || (((i == 5) || (i == 6)) && (j>0) && (j<4)))
                    mat[pos_x + i][pos_y + j] = 20;
                else
                {
                    if ((i == 7))
                        mat[pos_x + i][pos_y + j] = 21;
                    else 
                        mat[pos_x + i][pos_y + j] = 0;
                }
            }
        }
    }
}

void ajout_pic_mort(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_y>=0))
    {
        for (int i = 0; i< 8; i++)
        {
            for (int j = 0; j<5; j++)    
                mat[pos_x + i][pos_y + j] = 0;
        }
    }
}

void ajout_plateforme_mort(int mat[200][300], int pos_x, int pos_y, int longueur)
{
    if ((pos_x >= 0) && (pos_x < 198) && (pos_y >= 0) && (pos_y < 300))
    {
        for (int i = pos_x; i < pos_x + 7; i++)
        {
            for (int j = pos_y; j < pos_y + longueur; j++)
            {
                if (i == pos_x)
                    mat[i][j] = 5;
                else
                {
                    if ((i == pos_x + 1) && (j != pos_y) && (j != pos_y + longueur - 1))
                        mat[i][j] = 1;
                    else
                    {
                        if ((i == pos_x + 2) && (j>= pos_y + 1) && (j <= pos_y + longueur -2))
                            mat[i][j] = 5;
                        else
                        {
                            if ((i == pos_x + 3) && (j>= pos_y + 3) && (j <= pos_y + longueur - 4))
                                mat[i][j] = 2;
                            else
                            {
                                if ((i == pos_x + 4) && ((j == pos_y + 2) || (j == pos_y + (longueur/2) - 1) || (j == pos_y + (longueur/2) + 1) || (j == pos_y + longueur - 3)))
                                    mat[i][j] = 2;
                                else
                                {
                                    if ((i == pos_x + 5) &&((j == pos_y + 3) || (j == pos_y + (longueur / 2) - 2) || (j == pos_y + (longueur / 2) + 2) || (j == pos_y + longueur - 4) || (j == pos_y + (longueur/2))))
                                        mat[i][j] = 2;
                                    else
                                    {
                                        if ((i == pos_x + 6) && ((j == pos_y + (longueur / 2) - 3) || (j == pos_y + (longueur / 2) + 3) || (j == pos_y + (longueur/2))))
                                            mat[i][j] = 2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ajout_nuage(int mat[200][300],int  x,int y)
{
   if ((x>=0) && (x<286) && (y>=0) && (y<184))
   {   
   int i; int j=0;
   for (i=8;i<12;i++)
      mat[y+j][x+i]=31;
   j++;
   for (i=6;i<13;i++)
      mat[y+j][x+i]=31;
   j++;
   for (i=4;i<14;i++)
      mat[y+j][x+i]=31;
   j++;
   for (i=2;i<16;i++)
      mat[y+j][x+i]=31;
   j++;
   for (i=1;i<17;i++)
      mat[y+j][x+i]=31;
   j++;
   for (i=0;i<17;i++)
      mat[y+j][x+i]=31;
   j++;
   for (i=1;i<16;i++)
      mat[y+j][x+i]=31;
   j++;
   }   
}

void mat_to_file(int mat[200][300], const char * file, int pos_x, int pos_y)
{
    FILE * level1_a = fopen(file, "w");

    if (level1_a)
    {
        fprintf(level1_a, "%d %d\n", pos_x, pos_y);

        for (int i=0;i<200;i++)
        {
            for (int j=0;j<300;j++)
            {
                fprintf(level1_a, "%d ", mat[i][j]);
            }
            fprintf(level1_a, "\n");
        }

        fclose(level1_a);
    }
}


int main()
{
    int i,j;

    int mat1[200][300];
    int mat2[200][300];

    for (i=0;i<200;i++)
    {
        for (j=0; j<300; j++)
        {
            mat1[i][j] = 0;
            mat2[i][j] = 0;
        }
    }

    ajout_sol_vie(mat1, 70, 230, 199, 299);
    ajout_sol_vie(mat1, 180, 0, 199, 299);

    ajout_sol_mort(mat2, 70, 230, 199, 299);
    ajout_sol_mort(mat2, 180, 0, 199, 299);

    ajout_pic_vie(mat1, 180, 20);
    ajout_pic_vie(mat1, 180, 25);
    ajout_pic_vie(mat1, 180, 30);
    ajout_pic_vie(mat1, 180, 35);

    ajout_pic_mort(mat2, 180, 20);
    ajout_pic_mort(mat2, 180, 25);
    ajout_pic_mort(mat2, 180, 30);
    ajout_pic_mort(mat2, 180, 35);

    ajout_plateforme_mort(mat2, 160, 55, 15);
    ajout_plateforme_mort(mat2, 140, 90, 15);
    ajout_plateforme_mort(mat2, 120, 120, 15);
    ajout_plateforme_mort(mat2, 100, 150, 15);
    ajout_plateforme_mort(mat2, 80, 180, 15);
    
    ajout_coupe(mat1, 55, 280);
    ajout_bulle(mat2, 55, 260);

    ajout_caillou(mat1, 85, 250);
    ajout_caillou(mat1, 190, 25);
    ajout_caillou(mat1, 187, 240);
    ajout_caillou(mat1, 105, 250);
    ajout_caillou(mat1, 115, 280);
    ajout_caillou(mat1, 135, 240);
    ajout_caillou(mat1, 185, 290);
    
    ajout_nuage(mat1, 20,70);
    ajout_nuage(mat1, 90,30);
    ajout_nuage(mat1,150,80);
    ajout_nuage(mat1,280,30);
    
    mat_to_file(mat1, "level1_alive.txt", 50, 179);
    mat_to_file(mat2, "level1_death.txt", 50, 179);

    return 0;
}
