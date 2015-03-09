#include "GibbsLda.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "comm.h"

using namespace std;

int GibbsLda::THIN_INTERVAL = 20;
int GibbsLda::BURN_IN = 1000;
int GibbsLda::ITERATIONS = 10000;

GibbsLda::GibbsLda(vector< vector<int> > &documents, int V)
{
    this->documents = documents;
    this->V = V;
    this->M = documents.size();
    //srand(1234);
    srand((unsigned)time(NULL));
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
    printf("M %d, V %d, K %d.\n", M, V, K);
    for(int i=0; i<M; ++i)
    {
        int m = documents[i].size();
        vector<int> topics;
        for(int j=0; j<m; ++j)
        {
            int topic = randRange(0, K-1);
            //printf("rand topic %d for word [%d, %d].\n", topic, i, j);
            topics.push_back(topic);
            nw[documents[i][j]][topic]++;
            nd[i][topic]++;
            nwsum[topic]++;
        }
        z.push_back(topics);
        ndsum[i] = m;
    }
}

void GibbsLda::gibbs(double alpha, double beta)
{
    this->alpha = alpha;
    this->beta = beta;

    printf("randomly assign topic to every word...\n");
    initState();
    printf("finished randomly assign topic.\n");
    printf("begin MCMC with total %d iterations, and the first %d iterations as Burn In.\n", ITERATIONS, BURN_IN);
    for(int iteration=0; iteration<GibbsLda::ITERATIONS; ++iteration)
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
        if(iteration<GibbsLda::BURN_IN && iteration%GibbsLda::THIN_INTERVAL==0)
        {
            printf("B");
        }
        if(iteration>=GibbsLda::BURN_IN && iteration%GibbsLda::THIN_INTERVAL==0)
        {
            printf("S");
            updateParams();
        }
    }
    printf("\nFinished gibbs with %d iterations.\n", ITERATIONS);
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
    val *= p[K-1];
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

double** GibbsLda::getTheta()
{
    printf("getTheta ...\n");
    if(statnum == 0)
    {
        printf("statnum == 0, exit().\n");
        exit(-1);
    }
    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<K; ++j)
        {
            thetasum[i][j] /= statnum;
        }
    }
    return thetasum;
}

double** GibbsLda::getPhi()
{
    printf("getPhi ...\n");
    if(statnum == 0)
    {
        printf("statnum == 0, exit().\n");
        exit(-1);
    }
    for(int i=0; i<K; ++i)
    {
        for(int j=0; j<V; ++j)
        {
            phisum[i][j] /= statnum;
        }
    }
    return phisum;
}

void GibbsLda::display(double **theta, double **phi)
{
    printf("display model info.\n");
    printf("**********document-topic**********\n");
    for(int i=0; i<M; ++i)
    {
        printf("document-%04d\t", i);
        for(int j=0; j<K; ++j)
        {
            printf("%.06f\t", theta[i][j]);
        }
        printf("\n");
    }
    printf("**********topic-word**********\n");
    for(int i=0; i<K; ++i)
    {
        printf("topic-%04d\t", i);
        for(int j=0; j<V; ++j)
        {
            printf("%.06f\t", phi[i][j]);
        }
        printf("\n");
    }
}

