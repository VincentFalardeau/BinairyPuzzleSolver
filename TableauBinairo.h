//  Tableau (matrice) du jeu Binairo
//
//  par Vincent Falardeau, 7 septembre 2018
//--------------------------------------------------
#include"Matrice.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iterator>
#include<algorithm>

const int NB_LIGNES = 10;
const int NB_COLONNES = 10;

const int UN = 1; 
const int UN_FIXE = 10;//correspond à un 1 vide
const int ZERO = 0; 
const int ZERO_FIXE = 100;//correspond à un 0 vide
const int NUL = -1;//correspond à une case vide

#pragma once
class TableauBinairo
{
public:
	TableauBinairo();
	TableauBinairo(string nomFichier);
	~TableauBinairo();
	string nbColonnesToString() const;
	string ligneToString(int iligne)const;
	string tableauToString()const;
	void resoudre();
private:
	//le jeu Binairo utilise un tableau de 10 par 10
	void initialiserDimensions();
	//initialise toutes les cases du tableau à NUL
	void initialiserValeurs();
	void traiterFichier(string nomFichier);
	void lireFichier(ifstream & ifs);
	void traiterLigneFichier(string ligne, int iLigne);
	//prend un string et verifie s'il correspond à UN_FIXE, ZERO_FIXE ou NUL
	//seulement utilisable lors de l'initialisation du tableau
	int verifierString(string s)const;
	//prend un int et si c'est un UN_FIXE ou un ZERO_FIXE,
	//le convertit en UN ou ZERO
	//utile lors de l'affichage de la matrice
	string convertirFixe(int nb)const;
	void remplirDeZeros();
	bool parcourirVerticalement();
	//vérifier si il y a le même nombre de uns et de zéros
	bool verifierSiUnsEgalZeros(vector<int> v);
	string vectorToString(vector<int> v);
	//verifier si il y a 3 symboles pareils d'affilé
	//Vérifie automatiquement si les nombre d'uns est égal aux nombre de zéros
	//avec bool verifierSiUnsEgalZeros(vector<int> v);
	bool verifierSymbolesDeSuite(vector<int> v);
	//diagnostique le problème avec la ligne ou la colonne
	//retourne 1 s'il n'y a pas le même nombre de uns et de zeros
	//retourne -1 s'il n'y a 3 symboles d'affilés
	//retourne 0 s'il n'y a aucun problèeme
	int diagnostiquer(vector<int> v);

	Matrice<int> mTableau;
};

ostream & operator <<(ostream& out, const TableauBinairo& tableau);

