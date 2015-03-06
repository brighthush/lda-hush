#ifndef __COMM__H__
#define __COMM__H__

#include <cstdio>
#include <vector>

int readDocs(char *inPath, std::vector< std::vector<int> > &docs);

int randRange(int left, int right); // rand a int in [left, right]

template<typename T>
T* new1(int n, T value)
{
    T *p = new T[n];
    for(int i=0; i<n; ++i) p[i] = value;
    return p;
}

template<typename T>
void delete1(T *p)
{
    delete [] p;
}

template<typename T>
T** new2(int n, int m, T value)
{
    T **p = new T*[n];
    for(int i=0; i<n; ++i)
    {
        p[i] = new T[m];
        for(int j=0; j<m; ++j)
            p[i][j] = value;
    }
    return p;
}

template<typename T>
void delete2(T **p, int n)
{
    for(int i=0; i<n; ++i)
    {
        delete [] p[i];
    }
    delete [] p;
}

void set1(int *p, int n, int value);
void set2(int **p, int n, int m, int value);

#endif
