#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main (const int argc, const char** argv)
{
    FILE *fp1;
    FILE *fp2;
    char buffer[BUFFER_SIZE];
    char ch;
    long length, k=0;
    int n, m, i, pos = 1;
    int read;
    fp1 = fopen(argv[1],"r");
    fp2 = fopen(argv[2],"w");
    if(fp1==NULL){
        return 0;
    }
    fseek(fp1,0, SEEK_END);
    length = ftell(fp1);
    printf("%ld",length);
    if(length==0)
    {
        //printf("empty file");
        return 0 ;
    }
    
    n = length/BUFFER_SIZE;
    m = length%BUFFER_SIZE;
    
    if(n==0)
    {
        fseek(fp1,0,SEEK_SET);
        read = fread(buffer, 1, length,fp1);
        //printf("%d", read);
        //j = 0;
        for(i=0; i<length/2;i++)
        {
            ch = buffer[i];
            buffer[i] = buffer[length-i-1];
            buffer[length-i-1] = ch;
        }
        fwrite(buffer, 1, length, fp2);
    }
    else{
        do{
            fseek(fp1,-(pos*BUFFER_SIZE), SEEK_END);
            read = fread(buffer, 1, BUFFER_SIZE,fp1);
            for(i=0; i<BUFFER_SIZE/2;i++)
            {
                ch = buffer[i];
                buffer[i] = buffer[BUFFER_SIZE-i-1];
                buffer[BUFFER_SIZE-i-1] = ch;
            }
            
            fwrite(buffer, 1, read, fp2);
            //printf("%ld\n", ftell(fp2));
            pos = pos + 1;
            //memset(buffer,0,BUFFER_SIZE);
        }while(pos<=n);
        if(m!=0){
            fseek(fp1, 0,SEEK_SET);
            
            read = fread(buffer, 1, m, fp1);
            
            for(i=0; i<m/2;i++)
            {
                ch = buffer[i];
                buffer[i] = buffer[m-i-1];
                buffer[m-i-1] = ch;
            }
            
            fwrite(buffer, 1, read, fp2);
        }
    }
   
    fclose(fp1);
    fclose(fp2);
    
}
