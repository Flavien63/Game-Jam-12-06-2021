#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*Compile avec : gcc level_editor.c -o level_design -g -Wall -Wextra*/

void ajout_bouton(int mat[200][300], int pos_x_deb, int pos_y_deb, int pos_x_fin, int pos_y_fin)
{
    if ((pos_x_deb >= 0) && (pos_y_deb >= 0) && (pos_x_fin < 200) && (pos_y_fin < 300))
    {
        for (int i = pos_x_deb; i <= pos_x_fin; i++)
        {
            for (int j = pos_y_deb; j <= pos_y_fin; j++)
            {
                mat[i][j] = 7;
            }
        }
        for (int i = pos_x_deb; i <= pos_x_fin; i ++)
        {
            for (int j = pos_y_deb; j <= pos_y_fin; j ++)
            {
                if ((i == pos_x_deb) || (j == pos_y_deb) || (i == pos_x_fin) || (j == pos_y_fin))
                    mat[i][j] = 6;
            }
        }
    }
}

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

void ajout_pic_droite(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_y>=0))
    {
        for (int i = 0; i< 5; i++)
        {
            for (int j = 0; j<4; j++)
            {
                if (((i==2) && (j == 0)) || (((i >= 1) && (i <= 3)) && ((j == 1) || (j == 2))))
                    mat[pos_x + i][pos_y + j] = 20;
                else
                {
                    if ((j == 3))
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

void ajout_plateforme_vie(int mat[200][300], int pos_x, int pos_y, int longueur)
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

    int mat0[200][300];
    int mat1[200][300];
    int mat1bis[200][300];
    int mat2[200][300];
    int mat2bis[200][300];
    int mat3[200][300];
    int mat3bis[200][300];

    for (i=0;i<200;i++)
    {
        for (j=0; j<300; j++)
        {
            mat0[i][j] = 0;
            mat1[i][j] = 0;
            mat1bis[i][j] = 0;
            mat2[i][j] = 0;
            mat2bis[i][j] = 0;
            mat3[i][j] = 0;
            mat3bis[i][j] = 0;
        }
    }

    /****Menu****/
    ajout_sol_vie(mat0, 180, 0, 199, 299);

    ajout_nuage(mat0, 20, 37);
    ajout_nuage(mat0, 264, 37);

    ajout_bouton(mat0, 35, 75, 70, 225);
    ajout_bouton(mat0, 85, 75, 120, 225);
    ajout_bouton(mat0, 135, 75, 170, 225);
    
    ajout_pic_droite(mat0, 100, 285);
    ajout_pic_droite(mat0, 105, 285);
    ajout_pic_droite(mat0, 110, 285);
    ajout_pic_droite(mat0, 115, 285);
    ajout_pic_droite(mat0, 120, 285);

    ajout_bulle(mat0, 165, 20);
    ajout_coupe(mat0, 165, 265);

    ajout_caillou(mat0, 190, 60);
    
    /****Niveau 1 vivant****/
    ajout_sol_vie(mat1, 70, 230, 199, 299);
    ajout_sol_vie(mat1, 180, 0, 199, 299);

    ajout_pic_vie(mat1, 180, 20);
    ajout_pic_vie(mat1, 180, 25);
    ajout_pic_vie(mat1, 180, 30);
    ajout_pic_vie(mat1, 180, 35);

    ajout_coupe(mat1, 55, 280);

    ajout_caillou(mat1, 85, 250);
    ajout_caillou(mat1, 190, 25);
    ajout_caillou(mat1, 187, 240);
    ajout_caillou(mat1, 105, 250);
    ajout_caillou(mat1, 115, 280);
    ajout_caillou(mat1, 135, 240);
    ajout_caillou(mat1, 185, 290);

    ajout_cadre_noir(mat1);
    
    /****Niveau 1 mort****/
    ajout_sol_mort(mat1bis, 70, 230, 199, 299);
    ajout_sol_mort(mat1bis, 180, 0, 199, 299);

    ajout_pic_mort(mat1bis, 180, 20);
    ajout_pic_mort(mat1bis, 180, 25);
    ajout_pic_mort(mat1bis, 180, 30);
    ajout_pic_mort(mat1bis, 180, 35);

    ajout_plateforme_mort(mat1bis, 160, 60, 15);
    ajout_plateforme_mort(mat1bis, 140, 95, 15);
    ajout_plateforme_mort(mat1bis, 120, 125, 15);
    ajout_plateforme_mort(mat1bis, 100, 155, 15);
    ajout_plateforme_mort(mat1bis, 80, 185, 15);

    ajout_bulle(mat1bis, 55, 260);

    ajout_cadre_noir(mat1bis);
    
    /****Niveau 2 vivant****/
    ajout_sol_vie(mat2, 150, 0, 199, 49);
    ajout_sol_vie(mat2, 180, 50, 199,269);
    ajout_sol_vie(mat2, 150, 270, 199, 299);

    for (int i=0; i<44; i++)
        ajout_pic_vie(mat2, 180, 50+5*i);

    for (int i=0; i<4; i++)
        ajout_pic_vie(mat2,142,30+5*i);

    ajout_coupe(mat2,136,285);

    ajout_cadre_noir(mat2);
 
    /****Niveau 2 mort****/
    ajout_sol_mort(mat2bis, 150, 0, 199, 49);
    ajout_sol_mort(mat2bis, 180, 50, 199, 269);
    ajout_sol_mort(mat2bis, 150, 270, 199, 299);
    ajout_sol_mort(mat2bis, 150, 90, 169, 269);

    ajout_pic_mort(mat2bis, 142, 30);
    ajout_pic_mort(mat2bis, 142, 35);
    ajout_pic_mort(mat2bis, 142, 40);
    ajout_pic_mort(mat2bis, 142, 45);

    for (int i = 0; i < 44; i++)
    {
        ajout_pic_mort(mat2bis, 180, 50 + 5*i);
    }

    ajout_plateforme_mort(mat2bis, 170, 55, 15);

    for (int i = 0; i < 5; i++)
    {
        ajout_bulle(mat2bis, 135, 110 + 40 * i);
    }

    ajout_cadre_noir(mat2bis);
    
    /****Niveau 3 vivant****/
    ajout_sol_vie(mat3, 180, 0, 199, 49);
    ajout_sol_vie(mat3, 150, 220, 199, 259);
    ajout_sol_vie(mat3, 180, 260, 199, 279);
    ajout_sol_vie(mat3, 110, 210, 129, 249);
    ajout_sol_vie(mat3, 40, 0, 59, 49);

    for (int i = 0; i < 34; i++)
    {
        ajout_pic_vie(mat3, 191, 50 + i * 5);
    }

    for (int i = 0; i < 4; i++)
    {
        ajout_pic_vie(mat3, 110, 220 + i * 5);
    }

    for (int i = 0; i < 4; i++)
    {
        ajout_pic_vie(mat3, 191, 280 + i * 5);
    }

    ajout_plateforme_vie(mat3, 160, 280, 15);
    ajout_plateforme_vie(mat3, 120, 280, 15);

    ajout_coupe(mat3, 25, 5);

    ajout_cadre_noir(mat3);

    /****Niveau 3 mort****/
    ajout_sol_mort(mat3bis, 180, 0, 199, 49);
    ajout_sol_mort(mat3bis, 150, 220, 199, 259);
    ajout_sol_mort(mat3bis, 180, 260, 199, 279);
    ajout_sol_mort(mat3bis, 110, 210, 129, 249);
    ajout_sol_mort(mat3bis, 40, 0, 59, 49);

    for (int i = 0; i < 34; i++)
    {
        ajout_pic_mort(mat3bis, 180, 50 + i * 5);
    }

    for (int i = 0; i < 4; i++)
    {
        ajout_pic_mort(mat3bis, 110, 220 + i * 5);
    }

    for (int i = 0; i < 4; i++)
    {
        ajout_pic_mort(mat3bis, 191, 280 + i * 5);
    }

    ajout_bulle(mat3bis, 135, 230);
    ajout_bulle(mat3bis, 25, 25);

    ajout_plateforme_mort(mat3bis, 160, 190, 15);


    ajout_plateforme_mort(mat3bis, 90, 205, 15);
    ajout_plateforme_mort(mat3bis, 60, 175, 15);
    ajout_plateforme_mort(mat3bis, 90, 145, 15);
    ajout_plateforme_mort(mat3bis, 60, 115, 15);
    ajout_plateforme_mort(mat3bis, 50, 75, 15);

    ajout_cadre_noir(mat3bis);

    mat_to_file(mat0, "menu.txt", 0,0);
    mat_to_file(mat1, "level1_alive.txt", 50, 179);
    mat_to_file(mat1bis, "level1_death.txt", 50, 179);
    mat_to_file(mat2, "level2_alive.txt", 20, 149);
    mat_to_file(mat2bis, "level2_death.txt",50,179);
    mat_to_file(mat3, "level3_alive.txt", 20, 179);
    mat_to_file(mat3bis, "level3_death.txt", 20, 179);

    return 0;
}
