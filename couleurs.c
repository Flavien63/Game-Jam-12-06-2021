#include "couleurs.h"

void  tableau_vivant(int tab[100][3])
{
	/*couleur du ciel */
	tab[0][0]=51; tab[0][1]=102; tab[0][2]=255; 
	
	/*couleur du sol*/
	/*_marron_*/
	tab[1][0]=153;tab[1][1]=77;tab[1][2]=0;
	/*_vertforet_*/
	tab[2][0]=0;tab[2][1]=86;tab[2][2]=27;
	/*_sable_*/
	tab[3][0]=198;tab[3][1]=166;tab[3][2]=100;
	/*_gris-cailloux_*/
	tab[4][0]=69;tab[4][1]=69;tab[4][2]=69;
	/*marron_fonce_*/
	tab[5][0]=115;tab[5][1]=61;tab[5][2]=61;
	/*_noir_*/
	tab[6][0]=0;tab[75][1]=0;tab[75][2]=0;
	
	/*obstacle*/
	/*_pointe-acier_*/
	tab[20][0]=143;tab[20][1]=143;tab[20][2]=143;
	/*_pointe-bois_*/
	tab[21][0]=119;tab[21][1]=70;tab[21][2]=52;
	
	/*trophee*/
	tab[30][0]=251;tab[30][1]=255;tab[30][2]=0;
	
}


void  tableau_mort(int tab[100][3])
{
	/*couleur du ciel */
	 tab[0][0]=84;tab[0][1]=2;tab[0][2]=33;
	
	/*couleur du sol*/
	/*_rouge_foncé_*/
	tab[1][0]=117;tab[1][1]=40;tab[1][2]=40;
	/*_orange_*/
	tab[2][0]=250;tab[2][1]=139;tab[2][2]=35;
	/*_sable_*/
	tab[3][0]=198;tab[3][1]=166;tab[3][2]=100;
	/*_gris-cailloux_*/
	tab[4][0]=69;tab[4][1]=69;tab[4][2]=69;
	/*_rouge-plus-clair*/
	tab[5][0]=204;tab[5][1]=69;tab[5][2]=69;
	/*_noir_*/
	tab[6][0]=0;tab[75][1]=0;tab[75][2]=0;
	
	
	/*obstacle*/
	/*_pointe-acier_*/
	tab[20][0]=143;tab[20][1]=143;tab[20][2]=143;
	/*_pointe-bois_*/
	tab[21][0]=119;tab[21][1]=70;tab[21][2]=52;
	
	/*bulle*/
	/*_contour-de-la-bulle*/
	tab[30][0]=255;tab[30][1]=255;tab[30][2]=255;
	
	
	
}


