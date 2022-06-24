#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <Windows.h>

// Suppression du using namespace std puisque son usage est déconseillé.

int gagne(int c,int l,int J,int tab[7][6])  // renvoie J si le joueur gagne, sinon 1.
{
	// Optimisation du nombre de variables utilisées.
	int j[4];
	int k[3];

	// Optimisation de l'initialisation des tableaux
	for(int i=0;i<4;i++)
	{
		j[i]=1;
	}
	for(int i=0;i<3;i++)
	{
		k[i]=1;
	}

	for (int i=1; i<4; i++)
	{
		if (c-i>-1)
		{
			if ((tab[c-i][l]==J)&&(j[0]==i)) 
				j[0]++;
			if ((l-i>-1)&&(j[1]==i)) 
			{
				if(tab[c-i][l-i]==J) 
					j[1]++;
			}
			if ((l+i<6)&&(j[2]==i)) 
			{
				if(tab[c-i][l+i]==J) 
					j[2]++;
			}
		}
		if ((l-i>-1)&&(j[3]==i)) 
		{
			if(tab[c][l-i]==J) 
				j[3]++;
		}
	}
	for (int i=1; i<4; i++)
	{
		if (c+i<7)
		{
			if ((tab[c+i][l]==J)&&(k[0]==i)) 
				k[0]++;
			if ((l-i>-1)&&(k[2]==i)) 
			{
				if(tab[c+i][l-i]==J) 
					k[2]++;
			}
			if ((l+i<6)&&(k[1]==i)) 
			{
				if(tab[c+i][l+i]==J) 
					k[1]++;
			}
		}
	}
	// Modification de la valeur renvoyé si aucun joueur ne gagne.
	if ((k[0]+j[0]>=5)||(k[1]+j[1]>=5)||(k[2]+j[2]>=5)||(j[3]==4)) 
		return J;
	else
		return -1;
}

int IA(int I,int J,int tab[7][6],int nbJetonsByColonne[7],int c)
{
	I--;        //  on descend dans la profondeur du calcul
	int s=0;
	if (gagne(c,nbJetonsByColonne[c],J,tab)==-1)    // si ce que je joue ne me fait pas tout de suite gagner
	{
		if (I!=0)
		{
			int r=0,l,g,h;
			l=nbJetonsByColonne[c];   // on joue la nbJetonsByColonne c
			tab[c][l]=J;
			nbJetonsByColonne[c]++;
			// changement de joueur
			if (J==0) 
				J++;
			else
				J--;
			for (int i=0;i<7;i++)       //  on regarde tous les coups possibles
			{
				if (nbJetonsByColonne[i]==6) 
					r++;
				else
				{
					g=IA(I,J,tab,nbJetonsByColonne,i);
					if (g==J) 
						s=J; 
					else 
					{
						if (g!=0) 
							r++;
					}
				}
			}
			J++;
			if (J==3) 
				J=1;
			if (r==7) 
				s=J;   // si toutes les solutions mènent à perdre...
			nbJetonsByColonne[c]--;
			tab[c][l]=0;
		}
	}
		else s=J;
	I++;
	return s;   // s prend la valeur du joueur qui gagne, 0 si personne ne gagne
}

void affichageTab(int tab[7][6])   // affiche le tableau!!!
{
	// Modification de l'affichage pour que la console soit plus propre et claire.
	system("cls");
	std::cout<<std::endl<<std::endl<<std::endl;
	for (int i=5;i>=0;i--)
	{
		std::cout<<"          | ";
		for (int j=0;j<7;j++)
		{
			if (tab[j][i]==-1) 
				std::cout<<" ";
			if (tab[j][i]==0) 
				std::cout<<"X";
			if (tab[j][i]==1) 
				std::cout<<"O";
			std::cout<<" ";
		}
		std::cout<<"|"<<std::endl<<"          |---------------|"<<std::endl;
	}
	std::cout<<"          # 0 1 2 3 4 5 6 #"<<std::endl<<std::endl;
}


void jeu(int mode)
{
	//  Optimisation du nombre de variables utilisées.
	int nbJetonsByColonne[7];   // donne le nombre de jetons sur chaque colonne

	
	std::string tabJoueurs[2];
	int tab[7][6];
	int iaOrdinateur,J;
	int g=-1,c,l,compteur=0;                //g=0 => le jeu continue ; g=1 => ordi gagne ; g=2 => tu gagnes ; g=3 => égalité

	//: Ajout pour gérer si on est en mode 2 joueurs ou en mode contre l'ordinateur
	bool mode2joueurs=false;
	for (int i=0; i<7; i++)  // mise a zéro du tableau et des colonnes
	{
		nbJetonsByColonne[i]=0;
		for (int j=0; j<6; j++)
		{
			tab[i][j]=-1;
		}
	}
	system("cls");

	//Ajout pour obtenir le nom du ou des joueurs qui joueront la partie.
	if(mode==1)
	{
		mode2joueurs=true;
		std::cout	<< "Quel est le nom du premier joueur ?" << std::endl;
		std::cin>>tabJoueurs[0];
		std::cout<<std::endl<<std::endl <<"Quel est le nom du second joueur ?" << std::endl;
		std::cin>>tabJoueurs[1];  
		system("cls");
	}
	else
	{
		if(mode==2)
		{
			std::cout	<< "Quel est le nom du joueur ?" << std::endl;
			std::cin>>tabJoueurs[0];
			std::cout<<std::endl<<std::endl	<< "Niveau de difficulte de l'ordinateur? (1 a 10)" << std::endl;
			std::cin>>iaOrdinateur;                 //intelligence ordi
		}
	}

	// : Détermine qui débute la partie au hasard au lieu de choisir.
	srand(time(NULL));
	J=rand()%2;
	if(J==0)
		std::cout<<"C'est " << tabJoueurs[0] << " qui debute"<<std::endl;
	else
	{
		if(mode2joueurs)
			std::cout<<"C'est " << tabJoueurs[1] << " qui debute"<<std::endl;
		else
			std::cout<<"C'est l'ordinateur qui debute"<<std::endl;
	}
	system("pause");

	while (g==-1)         //  tant que personne n'a gagné...
	{
		if (compteur==42)  // égalité
		{
			g=-1;
			break;
		} 
		affichageTab(tab);

		// Ajout(s) pour la gestion du mode 2 joueurs.
		if (J==0 || mode2joueurs)            //  si c'est toi qui joue...
		{
			std::cout<<std::endl<<"C'est ton tour "<<tabJoueurs[J]<< " ! \nDans quel colonne veux-tu placer ton jeton?(0 à 6) (Tes jetons sont les ";
			if(J==0)
				std::cout<<"X)"<<std::endl;
			else
				std::cout<<"O)"<<std::endl;
			do
			{
				std::cin>>c;             //nbJetonsByColonne
				if(nbJetonsByColonne[c]>5) 
				{
					std::cout<<"Cette colonne est deja pleine."<<std::endl;
				}
			}
			while(nbJetonsByColonne[c]>5);
		}
		else            //  si c'est l'ordi qui joue
		{
			std::cout<<std::endl<<"Laisse-moi le temps de réfléchir..."<<std::endl;
			int c3[7]={0,6,5,1,2,4,3},r[7];   // c3 désigne l'ordre de préférence, du moins vers le plus.
			c=-1;       //  nbJetonsByColonne qu'on va jouer
			
			for (int j=0;j<7;j++)             // on regarde d'abord si l'ordi peut gagner en un endroit
			{
				if (nbJetonsByColonne [c3[j]]==6) 
					r[c3[j]]=-1;
				else 
				{
					r[c3[j]]=IA(iaOrdinateur,J,tab,nbJetonsByColonne,c3[j]); 
					if (r[c3[j]]==J) 
					{
						c=c3[j];
						break;
					}
				}
			}

		

			
			if (c==-1) 
			{
				for (int j=0;j<7;j++) 
				{
					if (r[c3[j]]!=-1) 
						c=c3[j];
				}
			}   
					std::cout<<"Je place mon jeton dans la colonne "<<c<<std::endl;
		}

		l=nbJetonsByColonne[c];         //ligne
		tab [c][l]=J;
		nbJetonsByColonne[c]++;
		g=gagne(c,l,J,tab);

		// Modification pour gestion plus logique des tours des joueurs.
		if (J==1) 
			J--;
		else
			J++;
		compteur++;
	}

	affichageTab(tab);

	// Modification des messages affichés et des valeurs pour chacune des cases puisque que la numérotation des joueurs a été changée.
	switch(g)
	{
		case -1 :std::cout<<std::endl<<"Desole, partie nulle..."<<std::endl;
				break;
		case 0:std::cout<<std::endl<<"Bravo ! Tu as gagne "<<tabJoueurs[0]<<std::endl;
				break;

// Ajout pour la gestion du mode 2 joueurs
		case 1:if(mode2joueurs)
					std::cout<<std::endl<<"Bravo ! Tu as gagne "<<tabJoueurs[1]<<std::endl;
				else
					std::cout<<std::endl<<"Desole, un ordinateur avec un QI de "<<iaOrdinateur*10<< " t'as battu... meilleure chance la prochaine fois"<<std::endl;
				break;
	}

	system("PAUSE");
}

int main()
{
		int c;


		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console,&r);

		MoveWindow(console,r.left,r.top,800,500,TRUE);

	
		std::cout << std::endl << "     *****************" << std::endl << "     *  puissance 4  *" << std::endl << "     *****************" << std::endl << std::endl;
		std::cout<<"1: Mode 2 joueurs\n2: Mode contre l'ordinateur\n0: Quitter"<<std::endl;
		do
		{
			std::cin>>c;
		}while(c<0 || c>2);
		system("cls");

		
		if(c!=0)
		{
			jeu(c);
		}
		
	return 0;
}