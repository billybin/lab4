#include <stdio.h>
#include <time.h>
#include <math.h>
#define LEFT(i)        ((i)<<1)
#define RIGHT(i)    (((i)<<1) + 1)

void max_heapify(int a[], int i, int heapsize);
void heap_sort(int a[], int heapsize);
void build_max_heap(int a[], int heapsize);
void exchange(int *x, int *y);
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
    heap_sort(A, N-1);
    time2=clock();
    /*for(i=1; i<N ; i++)
    {
        printf("%d\n",A[i]);
    }*/
    printf("\n堆排序%d个随机数字所用时间为:%d毫秒\n",N,time2-time1);
    return 1;

}
void exchange(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void max_heapify(int a[], int i, int heapsize)
{
    int left, right, largerest;

    left = LEFT(i);
    right = RIGHT(i);
    if (left <= heapsize && a[left]>a[i])
    {
        largerest = left;
        prntf("123213452eqw53wrt5435qrdfsew");
    }
    else
    {
        largerest = i;
    }
    if (right <= heapsize && a[right]>a[largerest])
    {
        largerest = right;
    }
    if(largerest != i)
    {
        exchange(&a[i], &a[largerest]);
        max_heapify(a, largerest, heapsize);
    }
}

void build_max_heap(int a[], int heapsize)
{
    int i;
    for (i=(int)ceil(heapsize/2); i >=1 ; i--)
    {
        max_heapify(a, i, heapsize);
    }
}

void heap_sort(int a[], int heapsize)
{
    build_max_heap(a, heapsize);
    while(heapsize>1)
    {
        exchange(&a[1], &a[heapsize]);
        heapsize--;
        max_heapify(a, 1, heapsize);
    }
    prntf("123213452eqw53wrt5435qrdfsew");
}



