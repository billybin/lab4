#include <stdio.h>
#include <stdlib.h>

void CreatHash(int A[],int N);
int prime(int N);
int search(int key,int A[],int N);

int main()
{
    int N,i,key;
    int *A=NULL;
    printf("请输入数据的个数:");
    scanf("%d",&N);
    A=(int*)calloc(N,sizeof(int));
    CreatHash(A,N);
    for(i=0; i<N; i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n请输入要查找的元素:");
    scanf("%d",&key);
    if(search(key,A,N)==-1)
    {
        printf("该元素不存在！\n");
    }
    else
    {
        printf("%d",search(key,A,N));
    }
}
void CreatHash(int A[],int N)
{
    int i,temp,index,j,p;
    p=prime(N);
    for(i=0; i<N; i++)
    {
        scanf("%d",&temp);
        index=temp%p;
        if(A[index-1]==0)
        {
            A[index-1]=temp;
        }
        else
        {
            for(j=index; j<N; j++)
            {
                if(A[j]==0)
                {
                    A[j]=temp;
                    break;
                }
            }
        }
    }
}
int search(int key,int A[],int N)
{
    int index,i;
    index=key%N;
    if(A[index-1]==key)
    {
        return (index-1);
    }
    else
    {
        for(i=index;i<N;i++)
        {
            if(A[i]==key)
            {
                return i;
            }
        }
        return -1;
    }
}
int prime(int N)
{
    int i,j;
    for(i=N;i>2;i--)
    {
        for(j=2;j<N/2;j++)
        {
            if(i%j==0)
            {
                break ;
            }
            if((i%j!=0)&&(j==N/2-1))
            {
                return i;
            }
        }
    }
    return i;
}

