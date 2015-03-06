#include "GibbsLda.h"

#include <iostream>
#include <cstdlib>

#include "comm.h"

using namespace std;

GibbsLda::GibbsLda(vector< vector<int> > &documents, int V)
{
    this->documents = documents;
    this->V = V;
    this->M = documents.size();
    srand(1234);
}

void GibbsLda::init(int K)
{
    this->K = K;
    
    nw = new2(V, K, 0);
    nd = new2(M, K, 0);

    nwsum = new1(K, 0);
    ndsum = new1(M, 0);

    statnum = 0;
    thetasum = new2(M, K, 0.0);
    phisum = new2(K, V, 0.0);
}

GibbsLda::~GibbsLda()
{
    delete2(nw, V);
    delete2(nd, M);
    
    delete1(nwsum);
    delete1(ndsum);

    delete2(thetasum, M);
    delete2(phisum, K);
}

void GibbsLda::initState()
{
    for(int i=0; i<M; ++i)
    {
        int m = documents[i].size();
        vector<int> topics;
        for(int j=0; j<m; ++j)
        {
            int topic = randRange(0, K-1);
            topics.push_back(topic);
            nw[documents[i][j]][topic]++;
            nd[i][topic]++;
            nwsum[topic]++;
        }
        ndsum[i] = m;
    }
}

void gibbs(double alpha, double beta)
{
    this->alpha = alpha;
    this->beta = beta;
    
    printf("randomly assign topic to every word...\n");
    initState();
    printf("begin MCMC with total %d iterations, and the \
            first %d iterations as Burn In", ITERATION, BURN_IN);
    for(int iteration=0; iteration<ITERATIONS; ++iteration)
    {
        for(int i=0; i<M; ++i)
        {
            int m = documents[i].size();
            for(int j=0; j<m; ++j)
            {
                int topic = sampleFullConditional(i, j);
                z[i][j] = topic;
            }
        }
        if(iteration<BURN_IN && iteration%THIN_INTERVAL==0)
        {
            printf("B");
        }
        if(iteration>=BURN_IN && iteration%THIN_INTERVAL==0)
        {
            printf("S");
            updateParams();
        }

    }
}

int GibbsLda::sampleFullConditional(int m, int n)
{
    int topic = z[m][n];
    int term = documents[m][n];
    nw[term][topic]--;
    nd[m][topic]--;
    nwsum[topic]--;
    ndsum[m]--;

    double *p = new1(K, 0.0);
    for(int k=0; k<K; ++k)
    {
        p[k] = (nw[term][k] + beta) / (double)(nwsum[k] + V*beta) * \
               (double)(nd[m][k] + alpha) / (double)(ndsum[m] + K * alpha);
    }
    for(int k=1; k<K; ++k)
        p[k] += p[k-1];
    double val = rand() / (double)RAND_MAX;
    topic = -1;
    for(int k=0; k<K; ++k)
    {
        if(p[k] > val)
        {
            topic = k;
            break;
        }
    }
    if(topic == -1)
        topic = K - 1;
    nw[term][topic]++;
    nd[m][topic]++;
    nwsum[topic]++;
    ndsum[m]++;

    delete1(p);
    return topic;
}

void GibbsLda::updateParams()
{
    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<K; ++j)
        {
            thetasum[i][j] += (nd[i][j] + alpha) / (double)(ndsum[i] + K * alpha);
        }
    }
    for(int i=0; i<K; ++i)
    {
        for(int j=0; j<V; ++j)
        {
            phisum[i][j] += (nw[j][i] + beta) / (double)(nwsum[i] + V * beta);
        }
    }
    statnum++;
}

void GibbsLda::display()
{
    cout << "display hello." << endl;
}
