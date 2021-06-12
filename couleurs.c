#include "couleurs.h"

void  tableau(int tab[100][3])
{
	/*couleur du ciel */
	tab[0][0]=51; tab[0][1]=102; tab[0][2]=255; 
	
	/*couleur du sol*/
	/*_marron_*/
	tab[1][0]=153;tab[1][1]=77;tab[1][2]=0;
	/*_vertforet_*/
	tab[2][0]=153;tab[2][1]=77;tab[2][2]=0;
	/*_sable_*/
	tab[3][0]=153;tab[3][1]=77;tab[3][2]=0;
	
	/*obstacle*/
	/*_pointe-acier_*/
	tab[20][0]=143;tab[20][1]=143;tab[20][2]=143;
	/*_pointe-bois_*/
	tab[21][0]=119;tab[21][1]=70;tab[21][2]=52;
	
	
}

