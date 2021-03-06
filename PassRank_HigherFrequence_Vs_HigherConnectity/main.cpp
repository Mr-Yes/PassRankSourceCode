/*
* This is The version of
* password set distance with all included
*/
#include <stdio.h>
#include <string.h>
#define psNum 20000000   //Password Set Total Number
#define maxDist 100     //the max distance expected

#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 

char pswd[psNum][30];
int psWeight[psNum];
int psDegree[psNum];

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
int levenshtein(char *s1, char *s2);

int main()
{
    FILE *fpin;
    FILE *fpFrequence;
    FILE *fpDegree;
    if(fpin=fopen("E:\\OneDrive\\Laboratory\\PassRankPaper\\PassRankDataSet\\testYahoo_top1000_frequence_count.txt","r"))
        puts("read Open Ready\n");
    else
        puts("Open Failed\n");

    if(fpFrequence=fopen("E:\\OneDrive\\Laboratory\\PassRankPaper\\PassRankDataSet\\Yahoo_Frequence_2Dplot.csv","w"))
        puts("Frequence Open Ready\n");
    else
        puts("Open Failed\n");
    
    if(fpDegree=fopen("E:\\OneDrive\\Laboratory\\PassRankPaper\\PassRankDataSet\\Yahoo_Degree_2Dplot.csv","w"))
        puts("Frequence Open Ready\n");
    else
        puts("Open Failed\n");


    //fprintf(fpout,"Source,Target,Type,Weight\n");
    //fprintf(fpnode,"Id,Weight\n");

    int i,j;
	
    int totalNum=0;
    //To Detect any passwd longer than 30
    while(fscanf(fpin,"%d\t%s",&(psWeight[totalNum]),pswd[totalNum]) != EOF){   //Read in the password set
        fprintf(fpFrequence,"%d,%d\n",totalNum,psWeight[totalNum]);
        //printf("%s,%d\n",pswd[totalNum],psWeight[totalNum]);
        if(psWeight[totalNum]== 0) return -1;
        psDegree[totalNum]=0;
        totalNum++;
        if(totalNum>psNum){
                printf("totalNum is: %d\n",totalNum);
                printf("Warning: The password has exceed the Total Number\n");
                return -1;
        }
    }
    printf("The totalNum is: %d\n",totalNum);

    //srand (time(NULL));
    //totalNum=3000;   
	
    for(i=0;i<totalNum;i++){
    	//if(i%100 == 0)
        printf("Cmping Line:%d \n",i);
		//fprintf(fpMatrix,"\n\n");
        //int demo_limit=0;
        //if(rand()%10 <9 ) continue;
        int i_degree=0;
        for(j=i+1;j<totalNum;j++){

            //printf("Cmping:%d and %d\n",i,j);
            int dist_Temp= levenshtein(pswd[i],pswd[j]);
            if(dist_Temp >0 && dist_Temp<4){
            	psDegree[i]++;
				psDegree[j]++;            	
        	}
            //printf("The Dist of (%s,%s): %d\n",pswd[i],pswd[j],dist);            
        }
        fprintf(fpDegree,"%d,%d\n",i,psDegree[i]);
    }
    fclose(fpin);
    fclose(fpFrequence);
    fclose(fpDegree);
    return 0;
}

int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    if(  (s1len-s2len >3) || (s2len-s1len >3)  )
        return -1;
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}



/*
#include <stdio.h>
#include <string.h>
#define psNum 20000000   //Password Set Total Number
#define maxDist 100     //the max distance expected

#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 

char pswd[psNum][30];
int psWeight[psNum];

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
int levenshtein(char *s1, char *s2);

int main()
{
    FILE *fpin;
    FILE *fpout;
    FILE *fpnode;
    if(fpin=fopen("E:\\OneDrive\\Laboratory\\PassRankPaper\\PassRankDataSet\\yahoo_frequence_count.txt","r"))
        puts("read Open Ready\n");
    else
        puts("Open Failed\n");

    if(fpout=fopen("E:\\OneDrive\\Laboratory\\PassRankPaper\\PassRankDataSet\\yahoo_Dist1_Edge_demo.csv","w"))
        puts("Edge Open Ready\n");
    else
        puts("Open Failed\n");

    if(fpnode=fopen("E:\\OneDrive\\Laboratory\\PassRankPaper\\PassRankDataSet\\yahoo_Dist1_node_demo.csv","w"))
        puts("Node Open Ready\n");
    else
        puts("Open Failed\n");

    fprintf(fpout,"Source,Target,Type,Weight\n");
    fprintf(fpnode,"Id,Weight\n");

    int i,j;

    int totalNum=0;
    //To Detect any passwd longer than 30
    while(fscanf(fpin,"%d\t%s",&(psWeight[totalNum]),pswd[totalNum]) != EOF){   //Read in the password set
        fprintf(fpnode,"%s,%d\n",pswd[totalNum],psWeight[totalNum]);
        //printf("%s,%d\n",pswd[totalNum],psWeight[totalNum]);
        if(psWeight[totalNum]== 0) return -1;
        totalNum++;
        if(totalNum>psNum){
                printf("totalNum is: %d\n",totalNum);
                printf("Warning: The password has exceed the Total Number\n");
                return -1;
        }
    }
    printf("The totalNum is: %d\n",totalNum);

    //srand (time(NULL));
    for(i=0;i<totalNum;i++){
        printf("Cmping Line:%d \n",i);

        //int demo_limit=0;
        //if(rand()%10 <9 ) continue;
        for(j=i+1;j<totalNum;j++){

            //if(i<3000 || i>5000) continue;
            //if(rand()%10 <9 ) continue;

            //printf("Cmping:%d and %d\n",i,j);
            int dist_Temp= levenshtein(pswd[i],pswd[j]);
            //printf("The Dist of (%s,%s): %d\n",pswd[i],pswd[j],dist);
            if(dist_Temp>maxDist){
                printf("Warning: The dist_Temp has exceed the maxDist expected\n");
                return -1;
            }
            if(dist_Temp<2 && dist_Temp>0){
                fprintf(fpout,"%s,%s,Undirected,%d\n",pswd[i],pswd[j],dist_Temp);
            }
            //if(++demo_limit  > (totalNum-i)/1000) break;
        }
    }
    fclose(fpin);
    fclose(fpout);
    fclose(fpnode);
    return 0;
}

int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    if(  (s1len-s2len >1) || (s2len-s1len >1)  )
        return -1;
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}

*/

/*
int editDistance(char *s,char *t,int j,int i){
    int a,b,c,min;
    if(i>0 && j>0){
        a=t[i-1]==s[j-1]?editDistance(s,t,j-1,i-1):editDistance(s,t,j-1,i-1)+1;
        b=editDistance(s,t,j,i-1)+1;
        c=editDistance(s,t,j-1,i)+1;
        min=a>b?b:a;
        return min>c?c:min;
    }else if(i==0 && j==0){
        return t[0]==s[0]?0:1;
    }else if(i==0){
        return j;
    }else if(j==0){
        return i;
    }
}*/


