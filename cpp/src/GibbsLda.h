/*
 * @author : brighthush at sina dot com
 * @des : Implementate Gibbs LDA in C++.
 */

#ifndef __GIBBS__LDA__H__
#define __GIBBS__LDA__H__

#include <vector>

class GibbsLda
{
private:
    // input related variables
    std::vector< std::vector<int> > documents;
    int M; // the size of documents
    int V; // vocabulary size
    int K; // the number of latent topic
    
    // lda related variables
    double alpha; // prior distribution parameters for document-topic
    double beta;  // prior distribution parameters for topic-word
    std::vector< std::vector<int> > z; // topic assignments for each word
    int **nw; // nw[i][j] means the number of word i assigned to topic j
    int **nd; // nd[i][j] means the number of words in document i assigned to topic j, 
              // the occurances of topic j in document i
    int *nwsum; // nwsum[j] total number of words assigned to topic j
    int *ndsum; // ndsum[i] total number of words in document i
    
    // variables for statistics, the following is used to calculate theta and phi
    // theta : multinominal parameters of document-topic distribution
    // phhi : multinominal parameters of topic-word distribution
    int statnum;       // the number of iteration in which we cumulate theta and phi
    double **thetasum; // this is used to calculate the mean of theta in some iterations
    double **phisum;   // this is used to calculate the mean of phi in some iterations

    // variables for algorithm running
    static int THIN_INTERVAL;  //= 20;
    static int BURN_IN;        // = 1000;
    static int ITERATIONS;     // = 10000;

public:
    GibbsLda(std::vector< std::vector<int> > &documents, int V);

    void init(int K);
    ~GibbsLda();

    void initState();
    void gibbs(double alpha, double beta);
    int sampleFullConditional(int m, int n);
    void updateParams()
    
    double** getTheta();
    double** getPhi();

    void display();

};

#endif
