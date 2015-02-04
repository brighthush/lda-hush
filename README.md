# lda-hush
Learn(read other's code) and Implement Latent Dirichlet Allocation Model  


# LdaGibbsSampler.java
## Variables
LdaGibbsSampler.java is a simple implementation of Gibbs Lda Model. There are some variables in the source code. In order to
understand this code, we should remember what does these variables mean.  
> V : vocabulary size  
> K : number of topics  
> alpha, beta : priori distribution of multinomial distribution, the parameter for Dirichlet distribution.  
> z[][] : topic assignments for each word.  
> nw[][] : nw[i][j] means the number of instances of word i assigned to topic j.  
> nd[][] : nd[i][j] means the number of words in document i assigned to topic j.  
> nwsum[] : nwsum[j] total number of words assigned to topic j.  
> ndsum[] : ndsum[i] total number of words in document i.  
> thetasum[][] : cumulative statistics of theta  
> phisum[][] : cumulative statistics of phi  
> numstats : size of statistics.  


## Functions


