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
    gibbsLda.init(2);
    //gibbsLda.initState();

    gibbsLda.gibbs(2.0, 0.5);
    double **theta = gibbsLda.getTheta();
    double **phi = gibbsLda.getPhi();
    gibbsLda.display(theta, phi);

    return 0;
}

