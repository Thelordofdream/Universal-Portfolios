//
//  main.c
//  多变量线性规划
//
//  Created by 张铭杰 on 15/7/28.
//  Copyright (c) 2015年 张铭杰. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
void CW(float x[2][100],float w[100]);
int main(int argc, const char * argv[]) {
    int a=0;
    float x[2][100]={0};//two day changes of stocks
    x[0][0]=0.9;
    x[0][1]=1.5;
    x[0][2]=0.9;
    x[1][0]=1.1;
    x[1][1]=0.6;
    x[1][2]=1.1;//example
    float w[100];//weight vector
    for(a=0;a<100;a++)
    {
        w[a]=1.0;
    }
    CW(x,w);
    for(a=0;a<5;a++)
    {
        printf("%f ",w[a]);//only show the frontest five weight
    }
    return 0;
}

void CW(float x[2][100],float w[100]){
    float s[100][100]={0};
    float transit[100][100];
    float m=0,n=0,l=0;//Coefficient of quadratic function with single variable
    float y=1;//Profit rate now
    float z0=0;//Change rate with t now
    float z1=0;//Maximum Change rate got
    float t=0;//Independent variable of the method of exhaustion
    float r=0;//the solution in every layer of iteration
    int k=2;//the layer number of iteration
    int a,b;
    for(a=0;a<100;a++)
    {
        for(b=0;b<100;b++)
        {
            transit[a][b]=1.0;
        }
    }

    for(a=0;a<2;a++)
    {
        for(b=0;b<100;b++)
        {
            printf("%f ",x[a][b]);
        }
        printf("\n");
    }

    for(a=0;a<100;a++)
    {
        for(b=0;b<100;b++)
        {
            s[a][b]=x[0][a]*x[1][b];
        }
    }
    y=s[0][0];
    while(k<=100)
    {
        l=s[k-1][k-1]*transit[k-1][k-1];
        
        m=y;
        for (a=0; a<k-1; a++) {
            m=m-s[a][k-1]*transit[a][k-1];
        }
        for (b=0;b<k-1;b++){
            m=m-s[k-1][b]*transit[k-1][b];
        }
        m=m+s[k-1][k-1]*transit[k-1][k-1];
        
        n=0;
        for (a=0; a<k-1; a++) {
            n=n+s[a][k-1]*transit[a][k-1];
        }
        for (b=0;b<k-1;b++){
            n=n+s[k-1][b]*transit[k-1][b];
        }
        n=n-2*s[k-1][k-1]*transit[k-1][k-1];
        
        z1=z0=0;
        for(t=0;t<=1;t=t+0.000001)
        {
            z0=m*t*t+n*t+l;
            if(z0>z1)
            {
                z1=z0;
                y=z1;
                r=t;
            }
        }
        
        for(a=0;a<k-1;a++)
        {
            w[a]=w[a]*r;
        }
        w[k-1]=w[k-1]*(1-r);
        for(a=0;a<100;a++)
        {
            for(b=0;b<100;b++)
            {
                transit[a][b]=w[a]*w[b];
            }
        }
        k++;
    }
    printf("%f\n",y);
    return ;
}
