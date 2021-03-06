//
// Created by Timur Kramar on 17/04/2022.
//

#include "stdio.h"

void pis_mnozinu(int *list, unsigned int list_length){
    for (int i = 0; i < list_length; i++){
        printf("%d\t", list[i]);
    }
    printf("\n");
}

void swap(unsigned int i, unsigned int j, int *list) {
    int aux = list[i];
    list[i] = list[j];
    list[j] = aux;
}

void remove_element(int *list, unsigned int *list_length, int index){
    for(int i = index + 1; i < *list_length; i++){
        list[i-1] = list[i];
    }
    *list_length -= 1;
}

void remove_duplicates(int *list, unsigned int *list_length){
    for(int i = 0; i < *list_length - 1; i++){
        if (list[i] == list[i+1]){
            remove_element(list, list_length, i);
            i--;
        }
    }
}

void heapify_node(int *list, unsigned int list_length, unsigned int root_index){
    unsigned int largest_index = root_index;
    unsigned int child1 = root_index*2 + 1;
    unsigned int child2 = root_index*2 + 2;

    // Porovnaj ho s deťmi, najväčšie nechaj pod largest
    if (child1 < list_length && list[child1] > list[largest_index]){
        largest_index = child1;
    }
    if (child2 < list_length && list[child2] > list[largest_index]){
        largest_index = child2;
    }
            // Ak nejaké dieťa je väčšie, vymeň ho s rodičom
            // a pokračuj v heapify o level hlbšie
    if (largest_index != root_index) {
//        pis_mnozinu(list, list_length);
        swap(largest_index, root_index, list);
//        pis_mnozinu(list, list_length);
        heapify_node(list, list_length, largest_index);
    }
}

void heap_sort(int *list, const unsigned int *list_length){
    // Konvertuj na heap
    // stačí začať od rodiča poslednej, čiže n/2-1
    for (unsigned int i = *list_length/2 - 1; i < *list_length; i--) {
        heapify_node(list, *list_length, i);
    }
    swap(0, *list_length-1, list);

    // Postupne vždy uprac heap a daj najväčšie na koniec
    for (unsigned int i = *list_length-1; i > 1; i--){
        heapify_node(list, i,0);
        swap(0, i-1, list);
//        pis_mnozinu(list, list_length);
    }
//    pis_mnozinu(list, list_length);
}

void set_from_list(int *list, unsigned int *list_length){
    heap_sort(list, list_length);
    remove_duplicates(list, list_length);
}

void Union(const int *a, const int *b, int *c,
           const unsigned int *a_l, const unsigned int *b_l, unsigned int *c_l){
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < *a_l && j < *b_l){
        if (a[i] == b[j]){
            c[k] = a[i];
            k++;
            i++;
            j++;
        }
        else if (a[i] <= b[j]){
            i++;
        }
        else if (a[i] >= b[j]){
            j++;
        }
    }
    *c_l = k;
}

void Intersection(const int *a, const int *b, int *c,
                  const unsigned int *a_l, const unsigned int *b_l, unsigned int *c_l){
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < *a_l && j < *b_l) {
        if (a[i] == b[j]){
            i++;
            j++;
        }
        else if (a[i] <= b[j]){
            c[k] = a[i];
            k++;
            i++;
        }
        else if (a[i] >= b[j]){
            c[k] = b[j];
            k++;
            j++;
        }
    }
    for (i = i; i < *a_l; i++){
        c[k] = a[i];
        k++;
    }
    for (j = j; j < *b_l; j++){
        c[k] = b[j];
        k++;
    }
    *c_l = k;
}
int main(void){
    unsigned int a_l = 5;
    unsigned int b_l = 7;
    unsigned int c_l = 12;
    unsigned int d_l = 7;

    int a[5] = {4, 2, 8, 4, 14};
    int b[7] = {6, 2, 16, 8, 9, 11, 20};
    int c[5+7];
    int d[7];
    pis_mnozinu(a, a_l);
    set_from_list(a, &a_l);
    pis_mnozinu(a, a_l);

    pis_mnozinu(b, b_l);
    set_from_list(b, &b_l);
    pis_mnozinu(b, b_l);

    pis_mnozinu(c, c_l);
    Union(a, b, c, &a_l, &b_l, &c_l);
    pis_mnozinu(c, c_l);

    pis_mnozinu(d, d_l);
    Intersection(a, b, d, &a_l, &b_l, &d_l);
    pis_mnozinu(d, d_l);
}