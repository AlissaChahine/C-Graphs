#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

//sommet * rechercherSommet(graphe g, int id);

graphe* creerGraphe()
{
    graphe * g = malloc(sizeof(graphe));
    if (g==NULL) return NULL; // si echec de l'allocation mémoire

    g->liste_sommets = NULL;
    return g;
}

void creerSommet(graphe *g, int id)
{

	 if (g == NULL)
     {
         printf("Le graphe n'est pas initialise");
         return;
     }
     if (rechercherSommet(*g, id)!=NULL)
     {
         printf("Le sommet %d existe deja dans le graphe", id);
         return;
     }

     sommet * new_s = malloc(sizeof(sommet));
     if (new_s == NULL) return; //on vérifie l'allocation, return si echec

     new_s->indice = id;
	 new_s->voisins = NULL;
	 new_s->suivant = NULL;

     //Insertion dans le graphe
     sommet *  temp = g->liste_sommets;
     //On traite le cas où le graphe est vide ou si l'element à insérer est le plus petit
     if (temp == NULL || new_s->indice < temp->indice)
     {
         new_s -> suivant = temp;
         g->liste_sommets = new_s;
         return;
     }
     //on insère le sommet au bon endroit dans le graphe
     else
     {
         while (temp->suivant!=NULL && new_s->indice >= temp->suivant->indice)
         {
             temp = temp->suivant;
         }
         new_s->suivant = temp->suivant;
		 temp->suivant = new_s;
     }
}

sommet* rechercherSommet(graphe g, int id)
{
    if (g.liste_sommets == NULL) return NULL;

    sommet* temp = g.liste_sommets;
	while (temp!= NULL)
	{
		if (temp->indice == id) return temp;
        temp = temp->suivant;
	}
	return NULL;
}

void insererVoisin(sommet* s, int id_voisin)
{
    voisin * new_v = malloc(sizeof(voisin));
    if (new_v == NULL) return;

    new_v->indice = id_voisin;
    new_v->suivant = NULL;

    voisin * pnt_voisin = s-> voisins;
    if (pnt_voisin == 0 || id_voisin < pnt_voisin->indice)
    {
        new_v -> suivant = s->voisins;
        s->voisins = new_v;
    }
    else
    {
        while (pnt_voisin->suivant != 0 && id_voisin >= pnt_voisin->suivant->indice)
        {
            if (id_voisin == pnt_voisin->suivant->indice)
            {
                printf("\nLe voisin %d existe deja dans le sommet %d", id_voisin, s->indice);
                free(new_v);
                return;
            }
            else
            {
                pnt_voisin = pnt_voisin->suivant;
            }
        }

        if (id_voisin == pnt_voisin->indice) //pour tester le premier
        {
            printf("\nLe voisin %d existe deja dans le sommet %d", id_voisin, s->indice);
            free(new_v);
            return;
        }
        new_v->suivant = pnt_voisin->suivant;
        pnt_voisin->suivant = new_v;
    }
}

void ajouterArete(graphe *g, int id1, int id2)
{
    sommet * s1 = rechercherSommet(*g, id1);
    sommet * s2 = rechercherSommet(*g, id2);

    // on cherche l'existence des sommets
    if (s1==NULL || s2==NULL)
    {
        if (s1==NULL)
        {
            printf("\nLe sommet d'indice %d n'existe pas.", id1);
            return;
        }
        printf("\nLe sommet d'indice %d n'existe pas.", id2);
        return;
    }
    if (id1 == id2)
    {
        sommet * s1 = rechercherSommet(*g, id1);
        insererVoisin(s1, id1);
        // une seule insertion dans les voisins du sommet
        return;
    }
    // else
    insererVoisin(s1, id2);
    insererVoisin(s2, id1);
}

graphe* construireGraphe(int N)
{
    graphe* g = creerGraphe();
    int i;
    int id_sommet, id1, id2;
    int reponse;
    int bool_ajout = 1;

    // l'utilisateur saisit tous les indices de sommets
    for (i=1; i<=N;i++)
    {
        printf("\nEntrez l'indice du sommet %d : ",i);
        scanf("%d",&id_sommet);
        creerSommet(g, id_sommet);
    }

    // L'utilisateur donne les paires d'indices de sommets qui forment des arrêtes
    while (bool_ajout == 1)
    {
        printf("\nAjouter une arrete ?(1 pour OUI, 0 pour NON) : ");
        scanf("%d",&reponse);
        if (reponse == 0)
        {
            bool_ajout = 0;
        }
        else if (reponse == 1)
        {
            printf("\nEntrez l'indice du 1er sommet de l'arrete : ");
            scanf("%d", &id1);
            // vérifier que le sommet est dans le graphe :
            if (rechercherSommet(*g,id1)==NULL)
            {
                printf("\nLe sommet %d n'existe pas",id1);
            }
            else
            {
                printf("\nEntrez l'indice du 2eme sommet: ");
                scanf("%d", &id2);
                if (rechercherSommet(*g,id2)==NULL)
                {
                    printf("\nLe sommet %d n'existe pas",id2);
                }
                else // si les sommet id2 et id1 existent
                {
                    ajouterArete(g, id1, id2);
                }
            }
        }
        else // si reponse!=0 et reponse!=1
        {
            printf("\nEntrez une reponse valide");
        }
    }
    printf("\nLe graphe de taille %d a ete cree!", N);
    return g;
}

void afficherGraphe(graphe g)
{
    if (g.liste_sommets == NULL)
        {
            printf("\nLe graphe est vide");
            return;
        }
    sommet* pnt_s = g.liste_sommets;
    int id_s;

    printf("\nListe des sommets du graphe :\n");
    printf("\tSommet\tVoisins\n");
    while (pnt_s != NULL)
    {
        id_s = pnt_s->indice;
        voisin* pnt_v = pnt_s->voisins;
        printf("\t (%d)\t", id_s);
        while (pnt_v != NULL)
            {
                printf("-> (%d) ", pnt_v->indice);
                pnt_v = pnt_v->suivant;
            }
        pnt_s = pnt_s->suivant;
        printf("\n");
    }
}

int compteVoisins(sommet* s)
{
    if (s->voisins == NULL) return 0;

    voisin* temp_v = s->voisins;
    int compteur=0;
    while(temp_v!=NULL)
    {
        compteur ++;
        temp_v = temp_v->suivant;
    }
    return compteur;
}

int rechercherDegre(graphe g)
{
    sommet* temp_s = g.liste_sommets;
    int max = 0;
    int degre;
    while(temp_s != NULL)
    {
        degre = compteVoisins(temp_s);
        if (degre > max) max = degre;
        temp_s = temp_s->suivant;
    }
    return max;
}

void supprimerVoisin(sommet* s, int id)
{
     voisin* pred = NULL;
     voisin* courant = s->voisins;
     while(courant != NULL && courant->indice != id)
     {
         pred = courant;
         courant = courant->suivant;
     }
     if(courant==NULL)
     {
         return;
     }

     //cas ou id est en tete de liste
     if(pred == NULL) s->voisins = courant->suivant;
     //cas ou id est autre part dans la liste
     else pred->suivant = courant->suivant;

     free(courant);
}

void supprimerSommet(graphe *g, int id)
{
     //recherche du prédessesseur de la valeur id
     sommet* pred = NULL;
     sommet* courant = g->liste_sommets;
     while(courant != NULL && courant->indice != id)
     {
         pred = courant;
         courant = courant->suivant;
     }
     if(courant==NULL)
     {
         printf("\nle sommet %d n'est pas dans le graphe", id);
         return;
     }

     //cas ou id est en tete de liste
     if(pred == NULL) g->liste_sommets = courant->suivant;
     //cas ou id est autre part dans la liste
     else pred->suivant = courant->suivant;

     sommet* temp = g->liste_sommets;
     while(temp != NULL)
     {
         supprimerVoisin(temp, courant->indice);
         temp = temp->suivant;
     }

     printf("Le sommet %d a bien ete supprime !", courant->indice);
     free(courant);

}

voisin* rechercherVoisin(sommet s, int id)
{
    voisin* temp = s.voisins;
	while (temp!= NULL)
	{
		if (temp->indice == id) return temp;
        temp = temp->suivant;
	}
	return NULL;
}

int contientBoucle(graphe g)
{
    int bool_boucle = 0;
    sommet* temp = g.liste_sommets;
    while(temp != NULL && bool_boucle==0)
    {
        if(rechercherVoisin(*temp, temp->indice) != NULL)
        {
            // le voisin de même id que le sommet existe
            bool_boucle = 1;
            return bool_boucle;
        }
        temp = temp->suivant;
    }
    return bool_boucle;
}

void fusionnerSommet(graphe *g, int idSommet1, int idSommet2)
{
   if(idSommet1 == idSommet2)
   {
       printf("\nEntrez des sommets differents");
       return;
   }
   //recherche du sommet à l'id le plus petit
   int min_id, max_id;
   if(idSommet1 <  idSommet2)
   {
       min_id = idSommet1;
       max_id = idSommet2;
   }
   else
   {
       min_id = idSommet2;
       max_id = idSommet1;
   }
    sommet * s_min, * s_max;

   if (rechercherSommet(*g, min_id)!=NULL && rechercherSommet(*g, max_id)!=NULL)
   {
       s_min = rechercherSommet(*g, min_id);
       s_max = rechercherSommet(*g, max_id);
   }
   else
   {
       printf("\nUn des sommets n'existe pas");
       return;
   }

   //on ajoute a s_min tous les voisins de l'autre sommet
   voisin* temp = s_max->voisins;
   while(temp != NULL)
   {
       ajouterArete(g, temp->indice, s_min->indice);
       temp = temp->suivant;
   }
   supprimerSommet(g, max_id);
   printf("\nLes sommets ont bien ete fusionnes");
}

