#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"


int main()
{
    int reponse = 0;
    graphe * g = NULL;

    do
    {

        //créer un graphe implique effacer le précédent
        printf("\n\n1. Creer un graphe vide"); // "(efface ancien graphe)"
        printf("\n2. Construire un graphe de N sommets"); //"(efface l'ancien graphe)"
        printf("\n3. Ajouter un sommet");
        printf("\n4. Ajouter une arete");
        printf("\n5. Afficher un graphe");
        printf("\n6. Donner le degre maximal du graphe");
        printf("\n7. Supprimer un sommet");
        printf("\n8. Verifier si le graphe contient une boucle");
        printf("\n9. Fusionner deux sommets");
        printf("\n10. Quitter");

        printf("\nEntrez votre choix : ");
        scanf("%d", &reponse);
        if(reponse) //Si l'utilisateur a donne une reponse
        {
            printf("Reponse saved");
            system("cls"); // efface console
        }
        switch(reponse)
        {
            case 1 : //Créer un graphe vide
                {
                    g = creerGraphe();
                    if (g != NULL) {
                        printf("\nLe graphe a bien ete cree");
                    } else {
                        printf("Erreur lors de la création du graphe. L'allocation de mémoire a échoué.\n");
                    }
                }
                break;
            case 2 :
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe vide avant");
                        break;
                    }
                    int N;
                    int valide = 0;
                    while (valide!=1) // Demande jusqu'a ce que la reponse soit valide
                    {
                        printf("\nNombre de sommets du graphe a creer ?: ");
                        scanf("%d",&N);
                        if (N <=0) printf("\nEntrez une taille >0");
                        else // reponse valide
                        {
                            valide = 1;
                            g=construireGraphe(N);
                        }
                    }
                } break;

            case 3 : // Ajouter un sommet
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe vide avant");
                        break;
                    }

                    else
                    {
                        int id;
                        printf("\nEntrez l'indice du sommet a creer: ");
                        scanf("%d",&id);
                        creerSommet(g, id);
                        afficherGraphe(*g);
                    }
                } break;

            case 4 :  //Ajouter une arete
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe vide avant");
                        break;
                    }
                    int id1, id2;
                    printf("\nEntrez l'indice du 1er sommet de l'arrete: ");
                    scanf("%d", &id1);
                    // vérifier que le sommet est dans le graphe :
                    if (rechercherSommet(*g,id1)==NULL)
                    {
                        printf("\nLe sommet %d n'existe pas",id1);
                    }
                    else // si le sommet id1 existe,
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
                            afficherGraphe(*g);
                        }

                    }break;
                }
            case 5 : // Afficher un graphe
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe avant");
                        break;
                    }
                    afficherGraphe(*g);
                }break;
            case 6 : //Donner le degre maximal du graphe
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe avant");
                        break;
                    }
                    int deg = rechercherDegre(*g);
                    printf("\nLe degre du graphe est %d", deg);
                }break;
            case 7 : // Supprimer un sommet
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe avant");
                        break;
                    }
                    int id_s;
                    printf("\nSommet a supprimer : ");
                    scanf("%d", &id_s);
                    supprimerSommet(g,id_s);
                }break;
            case 8 : // Verifier si le graphe contient une boucle
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe avant");
                        break;
                    }
                    if (contientBoucle(*g)) printf("\nLe graphe contient une boucle");
                    else printf("\nLe graphe ne contient pas de boucle");
                }break;
            case 9 : //Fusionner deux sommets
                {
                    if (g==NULL)
                    {
                        printf("\nVeuillez creer un graphe avant");
                        break;
                    }
                    int idS1, idS2;
                    printf("\nEntrez l'id du premier sommet : ");
                    scanf("%d", &idS1);
                    printf("\nEntrez l'id du deuxieme sommet : ");
                    scanf("%d", &idS2);
                    printf("\nGraphe avant fusion de %d et %d :", idS1, idS2);
                    afficherGraphe(*g);
                    fusionnerSommet(g, idS1, idS2);
                    printf("\n\nGraphe apres fusion de %d et %d :", idS1, idS2);
                    afficherGraphe(*g);
                }break;
        }

    } while(reponse != 10);
        return 0;
}
