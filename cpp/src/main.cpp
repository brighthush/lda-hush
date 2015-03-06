#include <iostream>

#include "comm.h"
#include "GibbsLda.h"

using namespace std;

int main()
{
    cout << "Hello World." << endl;
    vector< vector<int> > docs;
    int V = readDocs((char *)"./documents.txt", docs);
    for(int i=0; i<docs.size(); ++i)
    {
        printf("document[%d]\t", i);
        for(int j=0; j<docs[i].size(); ++j)
        {
            printf("%d ", docs[i][j]);
        }
        printf("\n");
    }
    GibbsLda gibbsLda(docs, V);
    gibbsLda.init(3);
    gibbsLda.initState();
    return 0;
}

