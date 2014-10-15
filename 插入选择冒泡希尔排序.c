#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Sort(int A[],int N);
void InsertSort(int A[],int N);
void ChoiceSort(int A[],int N);
void hillsort(int *p,int n);
int main()
{
    int i,N;
    clock_t time1,time2;
    int *A=NULL;
    printf("请输入数据的个数:");
    scanf("%d",&N);
    A=(int*)malloc(N*sizeof(int));
    for(i=0; i<N; i++)
    {
        A[i]=rand()%N;
    }
    time1=clock();
    //InsertSort(A,N);//插入排序
    //ChoiceSort(A,N);//选择排序
    //Sort(A,N);//冒泡排序
    hillsort(A,N);//希尔排序
    time2=clock();
    /*for(i=0; i<N; i++)
    {
        printf("%d ",A[i]);
    }*/
    printf("排%d个数所需的时间为:%d毫秒\n",N,time2-time1);
    return 0;
}
public void printsttt(){
        System.out.print("qweqwrqewtrdsaerty");
    }
void Sort(int A[],int N)
{
    int i,j,Temp;
    for(i=0;i<N;i++)
    {
        for(j=N-1;j>i;j--)
        {
            if(A[j]<A[j-1])//判断与前一个数的大小，然后交换
            {
                Temp=A[j];
                A[j]=A[j-1];
                A[j-1]=Temp;
            }
        }
    }
}
void InsertSort(int A[],int N)
{
    int i,j,Temp;
    for(i=1; i<N; i++)
    {
        j=i;
        while(j>0)
        {
            if(A[j]<A[j-1])
            {
                Temp=A[j];
                A[j]=A[j-1];
                A[j-1]=Temp;
            }
            j--;
        }
    }
}
void ChoiceSort(int A[],int N)
{
    int i,j,Min,Temp;
    for(i=0;i<N;i++)
    {
        Min=i;
        for(j=i+1;j<N;j++)
        {
            if(A[Min]>A[j])
            {
                Min=j;
            }
        }
        if(Min!=i)
        {
            Temp=A[i];
            A[i]=A[Min];
            A[Min]=Temp;
        }
    }
}
void hillsort(int *p,int n)
{
    int i,j,m;
    int t;
    int d = n/2;
    while(d > 0)
    {
        for(i=0; i<d; i++)
        {
            for(j=d; j<n; j+=d)
            {
                t = p[j];
                for(m=j; m>0; m-=d)
                {
                    if(t < p[m-d])
                        p[m] = p[m-d];
                    else
                    {
                        p[m] = t;
                        break;
                    }
                }
                if(m == 0)
                    p[m] = t;
            }
        }
        d = d/2;
    }
}








