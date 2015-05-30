/*
* This is The version of
* password set distance with all included
*/

#include <stdio.h>
#include <string.h>
#define psNum 20000000   //Password Set Total Number
#define maxDist 100     //the max distance expected
char pswd[psNum][30];
int psLen[psNum];

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
int levenshtein(char *s1, char *s2);

int main()
{
    FILE *fpin;
    FILE *fpout;
    FILE *fpresult;
    if(fpin=fopen("E:\\PassRankDataSet\\yahoo.txt","r"))
        puts("read Open Ready\n");
    else
        puts("Open Failed\n");

    if(fpout=fopen("E:\\PassRankDataSet\\yahoo_Distance_Matrix.csv","w"))
        puts("write Open Ready\n");
    else
        puts("Open Failed\n");

    if(fpresult=fopen("E:\\PassRankDataSet\\yahoo_Analyse_Result.txt","w"))
        puts("result Open Ready\n");
    else
        puts("Open Failed\n");

    int i,j;
    int distCnt[maxDist];
    for(i=0;i<maxDist;i++){
        distCnt[i]=0;
    }

    int totalNum=0;

    int maxLen =0;
    //To Detect any passwd longer than 30
    while(fscanf(fpin,"%s",pswd[totalNum]) != EOF){   //Read in the password set
        psLen[totalNum]=strlen(pswd[totalNum]);
        if(psLen[totalNum]>maxLen){
            maxLen=psLen[totalNum];
            printf("Line: %d \n",totalNum+1);
            printf("%s :Lenth is %d\n",pswd[totalNum],psLen[totalNum]);
        }
        //printf("%s : Lenth is %d\n",pswd[totalNum],psLen[totalNum]);
        totalNum++;
        if(totalNum>psNum){
                printf("Warning: The password has exceed the Total Number\n");
                return -1;
        }
    }
    fprintf(fpresult,"The totalNum is: %d\n",totalNum);
    fprintf(fpresult,"The maxLen is: %d\n",maxLen);

    for(i=0;i<totalNum;i++){
        int k;
        //complete the Matrix with leading 0
        for(k=0;k<i;k++){
            fprintf(fpout,"0");
            if(i<totalNum-1)
                fprintf(fpout,",");
            else
                fprintf(fpout,"\r\n");
        }
        //printf("Cmping Line:%d \n",i);
        for(j=i+1;j<totalNum;j++){
            //printf("Cmping:%d and %d\n",i,j);
            int dist_Temp= levenshtein(pswd[i],pswd[j]);
            //printf("The Dist of (%s,%s): %d\n",pswd[i],pswd[j],dist);
            if(dist_Temp>maxDist){
                printf("Warning: The dist_Temp has exceed the maxDist expected\n");
                return -1;
            }
            if(dist_Temp> -1)
                distCnt[dist_Temp]++;
            fprintf(fpout,"%d",dist_Temp);
            if(j<totalNum-1)
                fprintf(fpout,",");
            else
                fprintf(fpout,"\r\n");
        }
    }

    for(i=0;i<maxDist;i++){
        fprintf(fpresult,"%d,",distCnt[i]);
    }
    fprintf(fpresult,"\r\n");
    for(i=0;i<maxDist;i++){
        fprintf(fpresult,"Distance:%d   Ratio: %lf\r\n",i,distCnt[i]/(double)totalNum);
    }


    fclose(fpin);
    fclose(fpout);
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


