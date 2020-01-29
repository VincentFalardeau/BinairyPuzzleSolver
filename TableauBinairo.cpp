//  Tableau (matrice) du jeu Binairo
//
//  par Vincent Falardeau, 7 septembre 2018
//--------------------------------------------------

#include "TableauBinairo.h"



TableauBinairo::TableauBinairo()
{
	initialiserDimensions();
	initialiserValeurs();
}

TableauBinairo::TableauBinairo(string nomFichier)
{
	initialiserDimensions();
	traiterFichier(nomFichier);
}


TableauBinairo::~TableauBinairo()
{
}

string TableauBinairo::nbColonnesToString() const
{
	string str = "   ";
	for (int i = 0; i < mTableau.GetNbColonnes(); i++)
	{
		str += " ";
		str += to_string(i);
		str += "  ";
	}
	str += '\n';
	return str;
}

string TableauBinairo::ligneToString(int iligne) const
{
	string str = "|";
	for (int iColonne = 0; iColonne < mTableau.GetNbColonnes(); iColonne++)
	{
		if (mTableau[iligne][iColonne] == -1)
		{
			str += " ";
		}
		else
		{
			str += convertirFixe(mTableau[iligne][iColonne]);
		}
		
		str += " | ";
	}
	str += '\n';
	return str;
}

string TableauBinairo::tableauToString() const
{
	string str = nbColonnesToString();
	str += "   ---------------------------------------";
	str += '\n';
	for (int iligne = 0; iligne < mTableau.GetNbLignes(); iligne++)
	{
		str += to_string(iligne);
		str += "  ";
		str += ligneToString(iligne);
		str+= "   ---------------------------------------";
		str += '\n';
	}
	return str;
}

void TableauBinairo::resoudre()
{
	try 
	{
		remplirDeZeros();
		while (parcourirVerticalement());
		
	}
	catch (exception e)
	{
		cout << "Erreur lors de la résolution du tableau" << endl;
	}
}

void TableauBinairo::initialiserDimensions()
{
	mTableau.SetNbLignes(NB_LIGNES);
	mTableau.SetNbColonnes(NB_COLONNES);
}

void TableauBinairo::initialiserValeurs()
{
	for (int iLigne = 0; iLigne < mTableau.GetNbLignes(); iLigne++)
	{
		for (int iColonne = 0; iColonne < mTableau.GetNbColonnes(); iColonne++)
		{
			mTableau[iLigne][iColonne] = NUL;
		}
	}
}

void TableauBinairo::traiterFichier(string nomFichier)
{
	try 
	{
		ifstream ifs(nomFichier);
		lireFichier(ifs);
	}
	catch (exception e)
	{
		cout << "Erreur, le fichier n'a pas pu être ouvert" << endl;
	}
}

void TableauBinairo::lireFichier(ifstream & ifs)
{
	try
	{
		string ligne = "";
		for (int iLigne = 0; iLigne < mTableau.GetNbLignes(); iLigne++)
		{
			getline(ifs, ligne);
			traiterLigneFichier(ligne, iLigne);
		}
		ifs.close();
	}
	catch (exception e)
	{
		cout << "Erreur lors de la lecture du fichier" << endl;
	}
}

void TableauBinairo::traiterLigneFichier(string ligne, int iLigne)
{
	string s = "";
	for (int iColonne = 0; iColonne < mTableau.GetNbColonnes(); iColonne++)
	{
		s = ligne[iColonne];
		mTableau[iLigne][iColonne] = verifierString(s);
	}

}

int TableauBinairo::verifierString(string s)const
{
	if (s == "1")
	{	
		return UN_FIXE;
	}
	if (s == "0")
	{
		return ZERO_FIXE;
	}
	else
	{
		return NUL;
	}
}

string TableauBinairo::convertirFixe(int nb)const
{
	if (nb == 10)
	{
		return to_string(UN);
	}
	else if (nb == 100)
	{
		return to_string(ZERO);
	}
	else 
	{
		return to_string(nb);
	}
}

void TableauBinairo::remplirDeZeros()
{
	for (int iLigne = 0; iLigne < mTableau.GetNbLignes(); iLigne++)
	{
		for (int iColonne = 0; iColonne < mTableau.GetNbColonnes(); iColonne++)
		{
			if(mTableau[iLigne][iColonne] != UN_FIXE && mTableau[iLigne][iColonne] != ZERO_FIXE)
				mTableau[iLigne][iColonne] = ZERO;
		}
	}
}

bool TableauBinairo::parcourirVerticalement()
{
	bool valide = true;
	for (int iligne = 0; iligne < mTableau.GetNbLignes(); iligne++)
	{
		if (diagnostiquer(mTableau[iligne]) != 0)
		{
			valide = false;
			if (diagnostiquer(mTableau[iligne]) == -1)
				
			else

		}
	}
	return valide;
}

int TableauBinairo::diagnostiquer(vector<int> v)
{
	if (!verifierSiUnsEgalZeros(v))
		return 1;
	else if (!verifierSymbolesDeSuite(v))
		return -1;
	else
		return 0;
}

bool TableauBinairo::verifierSiUnsEgalZeros(vector<int> v)
{
	return count(v.begin(), v.end(), UN) + count(v.begin(), v.end(), UN_FIXE)
		== count(v.begin(), v.end(), ZERO) + count(v.begin(), v.end(), ZERO_FIXE);
}

string TableauBinairo::vectorToString(vector<int> v)
{
	stringstream ss;
	copy(v.begin(), v.end(), ostream_iterator<int>(ss, ""));
	return ss.str();
}

bool TableauBinairo::verifierSymbolesDeSuite(vector<int> v)
{
	if (verifierSiUnsEgalZeros(v))
	{
		size_t unsDeSuite = vectorToString(v).find("111");
		size_t zerosDeSuite = vectorToString(v).find("000");
		if (unsDeSuite != string::npos && zerosDeSuite != string::npos)
			return false;
		else
			return true;
	}
	else
		return false;
}

ostream & operator<<(ostream & out, const TableauBinairo & tableau)
{
	out << tableau.tableauToString();
	return out;
}
