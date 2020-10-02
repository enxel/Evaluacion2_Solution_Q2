#include <iostream>
#define LENGTH 5          //Assumed value, it will be permitted
#define SENTINEL 999999   //Sentinel value for Merge Sort

typedef struct LabeledHeap{
    int label;
    int* heap;
}LabeledHeap;

using namespace std;

void MaxHeapify(int* A, int* i, int* n){
    int l = 2 * (*i) - 1;
    int r = l + 1;
    int largest;
    if(l < *n && A[l] > A[*i])
        largest = l;
    else
        largest = *i;
    if(r < *n && A[r] > A[largest])
        largest = r;
    if(largest != *i){
        int temp = A[*i];
        A[*i] = A[largest];
        A[largest] = temp;
        MaxHeapify(A, &largest, n);
    }
}

void HeapifyArrays(int** n, int** m){
    for(int k=0; k < **n; k++){
        int l = LENGTH;
        int* A = m[k];
        for(int i=l/2 - 1; i >= 0; i--)
            MaxHeapify(A, &i, &l);
    }
}

int Digits(int n){
    int d = 1;
    while(n >= 10){
        n = n/10;
        d++;
    }
    return d;
}

int CountNodes(int* H, int* l){
    int cont = 0;
    for(int k=0; k < *l; k++)
        if(Digits(H[k]) == 5) && 2*k < *l && H[2*k-1] == 2*H[2*k])
            cont++;
    return cont;
}

void CountConditionNodes(int** n, int** m, LabeledHeap* A){
    for(int k=0; k < **n; k++){
        int l = LENGTH;
        int* H = m[k];
        int label = CountNodes(H, &l);
        A[k].label = label;
        A[k].heap = H;
    }
}

void Merge(LabeledHeap* A, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int i, j;
    LabeledHeap L[n1+1], R[n2+1];
    for(i=0; i < n1; i++)
        L[i] = A[p+i];
    for(j=0; j < n2; j++)
        R[j] = A[q+j+1];
    L[n1].label = R[n2].label = SENTINEL;
    i = j = 0;
    for(int k=p; k <= r; k++)
        if(L[i].label <= R[j].label){
            A[k] = L[i];
            i++;
        }else{
            A[k] = R[j];
            j++;
        }
}

void MergeSort(LabeledHeap* A, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort(A, p, q);
        MergeSort(A, q+1, r);
        Merge(A, p, q, r);
    }
}

void Toby(int* n, int** holes){
    HeapifyArrays(&n, holes);
    LabeledHeap A[*n];
    CountConditionNodes(&n, holes, A);
    MergeSort(A, 0, *n - 1);
}

int main()
{
    int values[25] = {45879,254,78966,123,987,        //2
                      9,78966,12369,933,12347,        //3
                      12000,43,78966,333699,633,      //2
                      48889,2599,7896,123161564,333,  //1
                      45879,254,78966,12378,3};       //3

    int n = 5;
    
    int** m = new int* [n];
    for(int i=0; i < n; i++)
        m[i] = new int [LENGTH];
    
    for(int i=0; i < n; i++)
        for(int j=0; j < LENGTH; j++)
            m[i][j] = values[LENGTH*i + j];
    
    Toby(&n, m);

    return 0;
}
