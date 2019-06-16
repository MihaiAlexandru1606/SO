/**
 * @author : Niculescu Mihai Alexandru
 */
#include "hashtable.h"

/**
 * functia care initializeaza tabela de dispersie
 * @param capacity dimensiunea initiala
 * @return NULL daca nu s-a reusit alocarea memorie pentru tabela
 *         adresa unde s-a alocat tabela creata
 */
HashTable *init_hash(unsigned int capacity) {
    HashTable *hash = malloc(sizeof(HashTable));

    if (hash == NULL)
        return NULL;

    hash->size = capacity;
    hash->buckets = calloc(capacity, sizeof(LinkedList));
    if (hash->buckets == NULL) {
        free(hash);
        return NULL;
    }

    return hash;
}


/**
 * functia care adauaga un cuvant in tabela
 * @param hashTable tabela de dispersie in care se adauga
 * @param word cuvantul de adaugat
 * @return rezultatul functie add_word();
 */
int add(HashTable *hashTable, char *word) {
    unsigned int hash_cod = hash(word, hashTable->size);

    return add_word(&hashTable->buckets[hash_cod], word);
}

/**
 * functia care cauta un cuvant in tabela
 * @param hashTable tabela de dispersie in care se cauta
 * @param word cuvantul de cautat
 * @return rezutatul find_word();
 */
BOOL find(HashTable *hashTable, char *word) {
    unsigned int hash_cod = hash(word, hashTable->size);

    return find_word(hashTable->buckets[hash_cod], word);
}

/**
 * fucntia care stege cuvantul din tabela
 * @param hashTable tabela de dispersie din care se sterge
 * @param word cuvantul care trebui sters, daca exista
 */
void delete(HashTable *hashTable, char *word) {
    unsigned int hash_cod = hash(word, hashTable->size);

    delete_word(&hashTable->buckets[hash_cod], word);
}

/**
 * functia care printeaza bucket-ul corespunzator
 * @param hashTable tabela de dispersie
 * @param indexBucket index-ul bucket-ului de printat
 * @param out fisierul de iesire
 */
void print_bucket(HashTable *hashTable, size_t indexBucket, FILE *out) {
    print_list(hashTable->buckets[indexBucket], out);
}

/**
 * functia care printeaza tabela de dispsie
 * @param hashTable tabela de dispersie
 * @param out fisierul de iesire
 */
void print(HashTable *hashTable, FILE *out) {
    size_t i;

    for (i = 0; i < hashTable->size; ++i) {
        print_bucket(hashTable, i, out);
    }
}

/**
 * functaia care realizeza redimensiunarea hash-ul
 * @param pHashTable adresa vechiului hash
 * @param new_size nou dimensiune a hash-ul
 * @return NULL sau noul hash
 */
static HashTable *resize(HashTable **pHashTable, unsigned int new_size) {
    HashTable *new_hashtable = init_hash(new_size);
    size_t i;
    LinkedList current;
    char *word;

    /** se verifica daca s-au reusit alocarile */
    if (new_hashtable == NULL) {

        destroy_hash(pHashTable);
        return NULL;
    }

    for (i = 0; i < (*pHashTable)->size; ++i) {
        for (current = (*pHashTable)->buckets[i]; current != NULL;
             current = current->next) {

            word = my_strdup(current->info);
            if (word == NULL || add(new_hashtable, word) != ADD_SUCCESS) {
                destroy_hash(&new_hashtable);
                destroy_hash(pHashTable);
                return NULL;
            }
        }
    }

    destroy_hash(pHashTable);
    *pHashTable = NULL;
    return new_hashtable;
}

/**
 * functia care înjumătățește dimensiunea hash-ului
 * @param pHashTable vechiul hash
 * @return noul hash sau NULL daca nu s-a putut aloca nou hash
 */
HashTable *resize_halve(HashTable **pHashTable) {
    return resize(pHashTable, (*pHashTable)->size / 2);
}

/**
 * functia care dublează dimensiunea hash-ului
 * @param pHashTable vechiul hash
 * @return noul hash sau NULL daca nu s-a putut aloca nou hash
 */
HashTable *resize_double(HashTable **pHashTable) {
    return resize(pHashTable, (*pHashTable)->size * 2);
}

/**
 * functia care goleste tabela de dispersie
 * @param hashTable
 */
void clear_hash(HashTable *hashTable) {
    size_t i;

    for (i = 0; i < hashTable->size; i++) {
        delete_list(&hashTable->buckets[i]);
    }

}

/**
 * functia care distruge tabela de dispersie
 * @param pHashTable adresa tabelei
 */
void destroy_hash(HashTable **pHashTable) {
    if (*pHashTable == NULL)
        return;

    if ((*pHashTable)->buckets != NULL) {
        clear_hash(*pHashTable);
        free((*pHashTable)->buckets);
    }

    free(*pHashTable);
    *pHashTable = NULL;
}