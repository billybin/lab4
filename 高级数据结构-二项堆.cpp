#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<climits>
using namespace std;

typedef struct BinHeapNode BinNode;
typedef struct BinHeapNode * BinHeap;
typedef struct BinHeapNode * Position;

struct BinHeapNode//结点ADT
{
    int key;
    int degree;
    Position parent;
    Position leftChild;
    Position sibling;
};
BinHeap MakeBinHeapWithArray(int keys[], int n);//用数组内的值建堆
BinHeap BinHeapUnion(BinHeap &H1, BinHeap &H2);//两个堆合并
BinHeap BinHeapMerge(BinHeap &H1, BinHeap &H2);//将H1, H2的根表合并成一个按度数的单调递增次序排列的链表
void BinLink(BinHeap &H1, BinHeap &H2);//使H2成为H1的父节点
BinHeap BinHeapMin(BinHeap heap);//返回最小根节点的指针
void BinHeapDecreaseKey(BinHeap heap, BinHeap x, int key);//减少关键字的值
BinHeap BinHeapDelete(BinHeap &heap, int key);//删除一个关键字
BinHeap BinHeapFind(BinHeap &heap, int key);//找出一个关键字
void PrintBinHeap(BinHeap heap);//打印输出堆结构
void DestroyBinHeap(BinHeap &heap);//销毁堆
void CreateArray(int A[],int N);//建数组
BinHeap BinHeapExtractMin(BinHeap &heap);
BinHeapNode* BinHeapInsert(int key,BinHeapNode *heap);//插入元素

int main()
{
    BinHeap H1 = NULL;
    int N,*A=NULL,*B=NULL,*C=NULL;
    int Sum;
    printf("开始建H1堆：\n");
    printf("请输入数据个数:");
    scanf("%d",&N);
    A=(int*)malloc(N*sizeof(int));
    CreateArray(A,N);
    H1 = MakeBinHeapWithArray(A,N);
    puts("第一个二叉堆H1:");
    PrintBinHeap(H1);

    BinHeap H2 = NULL;
    printf("\n开始建H2堆：\n");
    printf("\n请输入数据个数:");
    scanf("%d",&N);
    B=(int*)malloc(N*sizeof(int));
    CreateArray(B,N);
    H2 = MakeBinHeapWithArray(B,N);
    puts("\n\n第二个二叉堆H2:");
    PrintBinHeap(H2);

    BinHeap H3 = NULL;
    H3 = BinHeapUnion(H1, H2);
    puts("\n\n合并H1,H2后，得到H3:");
    PrintBinHeap(H3);
    BinHeap extractNode = BinHeapExtractMin(H3);
    if (extractNode != NULL)
    {
        printf("\n抽取最小的值%d后：\n", extractNode->key);
        PrintBinHeap(H3);
    }
    printf("\n请输入要删除的数:");
    printf("\n开始建H2堆：\n");
    printf("\nwqrewtrreytterturtyiu:");
    while(1)
    {
        scanf("%d",&Sum);
        if(Sum>0)
        {
            BinHeapDelete(H3, Sum);
            printf("\n删除%d后：",Sum);
            PrintBinHeap(H3);
            printf("\n");
        }
        else
            break;
    }
    int key;
    Position H4=NULL;
    while(1)
    {
        printf("\n请输入要插入的数:");
        printf("\n开始建H2堆：\n");
        printf("\n请输入数据个数:");
        scanf("%d",&key);
        if(key>0)
        {
            H4=BinHeapInsert(key,H3);
            PrintBinHeap(H4);
            H3=H4;
        }
        else
            break;

    }
    return 0;
}
BinHeap MakeBinHeapWithArray(int keys[], int n)
{
    BinHeap heap = NULL, newHeap = NULL;
    for (int i = 0; i < n; i++)
    {
        newHeap = (BinHeap) malloc(sizeof(BinNode));
        if (newHeap == NULL)
        {
            puts("Out of the Space");
            exit(1);
        }
        memset(newHeap, 0, sizeof(BinNode));
        newHeap->key = keys[i];
        if (NULL == heap)
        {
            heap = newHeap;
        }
        else
        {
            heap = BinHeapUnion(heap, newHeap);
            newHeap = NULL;
        }
    }
    return heap;
}
BinHeap BinHeapUnion(BinHeap &H1, BinHeap &H2)//两个堆合并
{
    Position heap = NULL, pre_x = NULL, x = NULL, next_x = NULL;
    heap = BinHeapMerge(H1, H2);
    if (heap == NULL)
    {
        return heap;
    }
    pre_x = NULL;
    x = heap;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) ||//Cases 1 and 2
                ((next_x->sibling != NULL) && (next_x->degree == next_x->sibling->degree)))
        {
            pre_x = x;
            x = next_x;
        }
        else if (x->key <= next_x->key)    //Cases 3
        {
            x->sibling = next_x->sibling;
            BinLink(next_x, x);
        }
        else    //Cases 4
        {
            if (pre_x == NULL)
            {
                heap = next_x;
            }
            else
            {
                pre_x->sibling = next_x;
            }
            BinLink(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
    return heap;
}
BinHeap BinHeapMerge(BinHeap &H1, BinHeap &H2)//将H1, H2的根表合并成一个按度数的单调递增次序排列的链表
{
    //heap->堆的首地址，H3为指向新堆根结点
    BinHeap heap = NULL, firstHeap = NULL, secondHeap = NULL,
                                     pre_H3 = NULL, H3 = NULL;

    if (H1 != NULL && H2 != NULL)
    {
        firstHeap = H1;
        secondHeap = H2;
        //整个while，firstHeap, secondHeap, pre_H3, H3都在往后顺移
        while (firstHeap != NULL && secondHeap != NULL)
        {
            if (firstHeap->degree <= secondHeap->degree)
            {
                H3 = firstHeap;
                firstHeap = firstHeap->sibling;
            }
            else
            {
                H3 = secondHeap;
                secondHeap = secondHeap->sibling;
            }

            if (pre_H3 == NULL)
            {
                pre_H3 = H3;
                heap = H3;
            }
            else
            {
                pre_H3->sibling = H3;
                pre_H3 = H3;
            }
            if (firstHeap != NULL)
            {
                H3->sibling = firstHeap;
            }
            else
            {
                H3->sibling = secondHeap;
            }
        }//while
    }
    else if (H1 != NULL)
    {
        heap = H1;
    }
    else
    {
        heap = H2;
    }
    H1 = H2 = NULL;
    return heap;
}
void BinLink(BinHeap &H1, BinHeap &H2)//使H2成为H1的父节点
{
    H1->parent = H2;
    H1->sibling = H2->leftChild;
    H2->leftChild = H1;
    H2->degree++;
}
BinHeap BinHeapMin(BinHeap heap)//返回最小根节点的指针
{
    Position y = NULL, x = heap;
    int min = INT_MAX;

    while (x != NULL)
    {
        if (x->key < min)
        {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}
BinHeap BinHeapExtractMin(BinHeap &heap)//抽取有最小关键字的结点
{
    BinHeap pre_y = NULL, y = NULL, x = heap;
    int min = INT_MAX;
    while (x != NULL)
    {
        if (x->key < min)
        {
            min = x->key;
            pre_y = y;
            y = x;
        }
        x = x->sibling;
    }

    if (y == NULL)
    {
        return NULL;
    }

    if (pre_y == NULL)
    {
        heap = heap->sibling;
    }
    else
    {
        pre_y->sibling = y->sibling;
    }

    //将y的子结点指针reverse
    BinHeap H2 = NULL, p = NULL;
    x = y->leftChild;
    while (x != NULL)
    {
        p = x;
        x = x->sibling;
        p->sibling = H2;
        H2 = p;
        p->parent = NULL;
    }

    heap = BinHeapUnion(heap, H2);
    return y;
}
void BinHeapDecreaseKey(BinHeap heap, BinHeap x, int key)//减少关键字的值
{
    if(key > x->key)
    {
        puts("new key is greaer than current key");
        exit(1); //不为降键
    }
    x->key = key;

    BinHeap z = NULL, y = NULL;
    y = x;
    z = x->parent;
    while(z != NULL && z->key > y->key)
    {
        swap(z->key, y->key);
        y = z;
        z = y->parent;
    }
}
BinHeap BinHeapDelete(BinHeap &heap, int key)//删除一个关键字
{
    BinHeap x = NULL;
    x = BinHeapFind(heap, key);
    if (x != NULL)
    {
        BinHeapDecreaseKey(heap, x, INT_MIN);
        return BinHeapExtractMin(heap);
    }
    return x;
}
BinHeap BinHeapFind(BinHeap &heap, int key)//找出一个关键字
{
    Position p = NULL, x = NULL;
    p = heap;
    while (p != NULL)
    {
        if (p->key == key)
        {
            return p;
        }
        else
        {
            if((x =BinHeapFind(p->leftChild, key)) != NULL)
            {
                return x;
            }
            p = p->sibling;
        }
    }
    return NULL;
}
void PrintBinHeap(BinHeap heap)//打印输出堆结构
{
    if (NULL == heap)
    {
        return ;
    }
    Position p = heap;
    while (p != NULL)
    {
        printf(" (");
        printf("%d", p->key);//显示其孩子
        if(NULL != p->leftChild)
        {
            PrintBinHeap(p->leftChild);
        }
        printf(") ");
        p = p->sibling;
    }
}
void CreateArray(int A[],int N)
{
    int i;
    for(i=0; i<N; i++)
    {
        scanf("%d",&A[i]);
    }
}
BinHeapNode* BinHeapInsert(int key,BinHeapNode *heap)
{
    BinHeapNode *newHeap = NULL;
    newHeap = new BinHeapNode;
    memset(newHeap,0,sizeof(BinHeapNode));//初始化新节点的值，degree,leftChild,sibling等
    newHeap->key = key;
    if(heap == NULL) heap = newHeap;
    else
    {
        heap = BinHeapUnion(heap,newHeap);
        newHeap = NULL;
        delete newHeap;
    }
    return heap;
}
