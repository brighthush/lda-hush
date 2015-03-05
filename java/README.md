# lda-hush
Learn(read other's code) and Implement Latent Dirichlet Allocation Model  


# LdaGibbsSampler.java
## Variables
LdaGibbsSampler.java is a simple implementation of Gibbs Lda Model. There are some variables in the source code. In order to
understand this code, we should remember what does these variables mean.  
### Member variables
> V : vocabulary size  
> K : number of topics  
> alpha, beta : priori distribution of multinomial distribution, the parameter for Dirichlet distribution.  
> z[][] : topic assignments for each word.  
> nw[][] : nw[i][j] means the number of instances of word i assigned to topic j.  
> nd[][] : nd[i][j] means the number of words in document i assigned to topic j.  
> nwsum[] : nwsum[j] total number of words assigned to topic j.  
> ndsum[] : ndsum[i] total number of words in document i.  
> thetasum[][] : cumulative statistics of theta, theta means parameters set of document-topic distribution parameters.  
> phisum[][] : cumulative statistics of phi, phi means parameters set of topic-word distribution parameters.  
> numstats : size of statistics.  

### private static variables  
> THIN_INTERVAL = 20  
> BURN_IN = 100  
> ITERATIONS = 1000  
> SAMPLE_LAG  
> dispcol = 0  

### Full Conditional for Gibbs Sampling  
If you want to sample topic for a word in document, it means you want to sample from this distribution 
p(z_i | z_{-i}, w). In LDA, after simplication, we get this probabilisty proportion to p(w|z_{-i})p(z_{-i}).
This means this full conditional distribution looks like a postorial distribution. But in this eqation, {-i} means
the current word is ignored in this statistal distribution.

## Functions


