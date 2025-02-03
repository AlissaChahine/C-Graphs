#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

typedef struct sommet sommet;
struct sommet
{
    int indice;
    struct sommet* suivant; //besoi de struct même si on a typedef struct ?
    struct voisin* voisins;
};

typedef struct voisin voisin;
struct voisin
{
    int indice;
    struct voisin* suivant;
};

typedef struct graphe graphe;
struct graphe
{
    struct sommet* liste_sommets;
};

graphe* creerGraphe();
void creerSommet(graphe *g, int id);
sommet* rechercherSommet(graphe g, int id);
void insererVoisin(sommet* s, int id_voisin);
void ajouterArete(graphe *g, int id1, int id2);
graphe* construireGraphe(int N);
void afficherGraphe(graphe g);
int compteVoisins(sommet* s);
int rechercherDegre(graphe g);
void supprimerVoisin(sommet* s, int id);
void supprimerSommet(graphe *g, int id);
voisin* rechercherVoisin(sommet s, int id);
int contientBoucle(graphe g);
void fusionnerSommet(graphe *g, int idSommet1, int idSommet2);





#endif // TP3_H_INCLUDED
