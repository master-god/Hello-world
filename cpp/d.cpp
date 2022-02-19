#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
void bestFit(int bS[], int m, int pS[], int n) {
    vector<int> a(n,-1);
    for (int i = 0; i < n; i++) {
        int id = -1;
        for (int j = 0; j < m; j++) {
            if (bS[j] >= pS[i]) {
                if (id == -1)
                    id = j;
                else if (bS[id] > bS[j]) 
                    id = j;
            }
        }
        if (id != -1) {
            a[i] = id;
            bS[id] -= pS[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d \t\t %d\t\t", i + 1, pS[i]);
        if (a[i] != -1) printf("%d\n", a[i] + 1);
        else printf("Not Allocated\n");
    }
}
void worstFit(int bS[], int m, int pS[], int n) {
    vector<int> a(n,-1);
    for (int i = 0; i < n; i++) {
        int id = -1;
        for (int j = 0; j < m; j++) {
            if (bS[j] >= pS[i]) {
                if (id == -1)
                    id = j;
                else if (bS[id] < bS[j])
                    id = j;
            }
        }

        if (id != -1) {
            a[i] = id;

            bS[id] -= pS[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d \t\t %d\t\t", i + 1, pS[i]);
        if (a[i] != -1) printf("%d\n", a[i] + 1);
        else printf("Not Allocated\n");
    }
}
void firstFit(int bS[], int m, int pS[], int n) {
    vector<int> a(n,-1);    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (bS[j] >= pS[i]) {
                a[i] = j;
                bS[j] -= pS[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d \t\t %d\t\t", i + 1, pS[i]);
        if (a[i] != -1) printf("%d\n", a[i] + 1);
        else printf("Not Allocated\n");
    }
}
int main() {
    /*int n, m, i;
    printf("Enter no of Memory Blocks:");
    scanf("%d", & n);
    vector<int> bS(n);
    for (i = 0; i < n; i++) {
        printf("Enter the size of Block %d:", i+1);
        scanf("%d", & bS[i]);
    }
    printf("\nEnter no of Processes:");
    scanf("%d", & m);
    vector<int> pS(m);
    for (i = 0; i < m; i++) {
        printf("Enter the size of Process %d:", i+1);
        scanf("%d", & pS[i]);
    }*/
    int bS[] = {100, 500, 200, 300, 600};
    int pS[] = {212, 417, 112, 426};
    int m = 5;
    int n = 4;
    printf("\nWORST FIT");
    worstFit(bS, m, pS, n);
    printf("\nBEST FIT");
    bestFit(bS, m, pS, n);
    printf("\nFIRST FIT");
    firstFit(bS, m, pS, n);
    return 0;
}
