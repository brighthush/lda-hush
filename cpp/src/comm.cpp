#include "comm.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int readDocs(char *inPath, vector< vector<int> > &docs)
{
    FILE *fin = fopen(inPath, "r");
    if( fin == NULL ) { printf("open file %s failed.\n", inPath); exit(-1); }
    // rows V
    // cols col_1 col_2 ...
    // cols col_1 col_2 ...
    // ...
    int rows, V;
    fscanf(fin, "%d %d", &rows, &V);
    while(rows--)
    {
        int cols, t;
        vector<int> doc;
        fscanf(fin, "%d", &cols);
        while(cols--)
        {
            fscanf(fin, "%d", &t);
            doc.push_back(t);
        }
        docs.push_back(doc);
    }
    fclose(fin);
    return V;
}

int randRange(int left, int right)
{
    double val = rand() / (double)RAND_MAX;
    val *= (right - left + 1);
    val += left;     //[left, right+1]
    return (int)val; //[left, right]
}

void set1(int *p, int n, int value)
{
    for(int i=0; i<n; ++i) p[i] = value;
}

void set2(int **p, int n, int m, int value)
{
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            p[i][j] = value;
}

