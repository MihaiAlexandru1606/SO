/**
 * @author : Niculescu Mihai Alexandru
 */
#include "linkedlist.h"

/**
 * functia care adauga un nou nod in lista
 * @param pList adresa de inceput al liste in care se insereaza
 * @param info cuvantul adaugat
 * @return ADD_SUCCESS daca s-a adaugat in lista sau exista
 *         ADD_ERROR in caz de esec
 */
int add_word(LinkedList *pList, char *info) {
    LinkedList *current = pList;
    Node *new_node;

    while (*current != NULL) {
        /** cautam sa vedem daca nu exista deja in lista **/
        if (strcmp(info, (*current)->info) == 0) {
            free(info);
            return ADD_SUCCESS;
        }

        current = &(*current)->next;
    }

    new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        /** daca nu am putut aloca memorie pentru noul nod returna erorea */
        return ADD_ERROR;
    }

    /** se insereaza noul nod creat */
    new_node->info = info;
    new_node->next = NULL;
    *current = new_node;

    return ADD_SUCCESS;
}

/**
 * functia care cauta un cuvant in lista
 * @param list lista in care cautam cuvantul
 * @param word cuvantul de cautat
 * @return TRUE  daca este gasit
 *         FALSE daca nu exista
 */
BOOL find_word(LinkedList list, char *word) {
    Node *current = list;

    for (; current != NULL; current = current->next) {
        if (strcmp(word, current->info) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}


/**
 * functia care printeaza lista in fiserul specificat pe o linie
 * @param list lista curenta
 * @param out fisiera de iesire
 */
void print_list(LinkedList list, FILE *out) {
    Node *current = list;
    int lenght = SIZE_VID_LIST;

    for (; current != NULL; current = current->next) {
        fprintf(out, "%s ", current->info);
        ++lenght;
    }

    /** daca nu este o lista vida */
    if (lenght != SIZE_VID_LIST) {
        fprintf(out, "\n");
    }
}


/**
 * functia elimina cuvantul din lista, daca exista
 * @param pList adresa de inceput a listei
 * @param word cuvantul care trebuie eliminat
 */
void delete_word(LinkedList *pList, char *word) {
    Node *aux;
    LinkedList *current = pList;

    while (*current != NULL) {
        if (strcmp((*current)->info, word) == STRING_EQUAL) {
            /** daca am gasit cuvantul in lista */
            /** eliminarea celulei */
            aux = *current;
            *current = aux->next;

            free(aux->info);
            free(aux);
            return;
        }

        current = &(*current)->next;
    }

}

/**
 * functia care distruge lista
 * @param pList adresa de inceput a listei
 */
void delete_list(LinkedList *pList) {
    LinkedList current = *pList;
    Node *aux;

    while (current != NULL) {
        aux = current;
        current = aux->next;
        free(aux->info);
        free(aux);
    }

    *pList = NULL;
}
