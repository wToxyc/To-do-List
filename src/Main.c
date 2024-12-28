#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    char option;
    char *todo = malloc(100 * sizeof(char));
    FILE *list;
    int index;
    char buffer[100];

    while (1)
    {
        printf("\033[0m\[1] Ajouter une tache\n[2] Supprimer une tache\n[3] Lister les taches\n> ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            printf("Entrez la tache : ");
            scanf("%*c");

            list = fopen("todo.txt", "a");
            fgets(todo, 100, stdin);
            fprintf(list, "%s", todo);
            fclose(list);

            printf("\033[32mTache enregistree avec succes !\n\n");
            break;

        case '2':

            printf("Entrez le numero de la tache : ");
            scanf(" %d", &index);

            int num = 1;
            FILE *tempFile = fopen("temp.txt", "w");
            list = fopen("todo.txt", "r");

            while (fgets(buffer, sizeof(buffer), list))
            {
                if (num != index)
                {
                    fprintf(tempFile, "%s", buffer);
                }
                num++;
            }

            if (fclose(tempFile) == 0 && fclose(list) == 0)
            {
                remove("todo.txt");
                rename("temp.txt", "todo.txt");
            }

            printf("\033[32mTache supprimee avec success !\n\n");
            break;

        case '3':
            list = fopen("todo.txt", "r");
            if (list == NULL)
            {
                printf("\033[31mImpossible de lister les taches, verifiez le fichier texte !\n\n");
                break;
            }
            printf("Liste des taches : \n\n");

            while (fgets(buffer, sizeof(buffer), list))
            {
                printf("- %s", buffer);
            }

            printf("\n");
            break;
        
        default:
            printf("\033[31mOption invalide !\n\n");
            break;
        }
    }

    return 0;
}