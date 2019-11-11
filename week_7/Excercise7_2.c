#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAXARRAY 362880

typedef struct node
{
    int data[3][3];
    int level;
    int pro;
}listarray[MAXARRAY],*list;
/*it is used in calculating the priority value of a node for comparative checking*/
struct c
{
    int row;
    int col;
}check[9];

void assign();
void eightpuzzle(int m[3][3]);
int getinversion(int a[]);
int solvable(int a[3][3]);
void priority(list t);
void printout(int x[3][3]);
void result(list t);
int compare(int x[3][3],int y[3][3]);
int goaltest(list t);
list insert(list head,list parent,int plev,int temp[3][3]);
list movegen(list t);
list proenqueue(list head,list temp,int flag);
list dequeue(list t);

int main(int argc, char **argv)
{
    clock_t startTime,endTime;
    int i,j,cnt=0;
    int m[3][3];
    /*p is for temporaraly handling closed,t is for holding open,
     * temp is return movgen,q for temporarily holding movgen*/
    if(argc==2)
    {
        startTime = clock();

        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(argv[1][cnt]>='1' && argv[1][cnt]<='9')
                {
                    m[i][j]=argv[1][cnt]-'1'+1;
                    cnt++;
                } else if(argv[1][cnt]==' ')
                {
                    m[i][j]=0;
                    cnt++;
                } else{
                    printf("Error input.\n");
                }
            }
        }
        assign();
        /*used in calculating the hash value*/
        eightpuzzle(m);
        endTime = clock();
        printf("Total time is:%fs\n",(double)(endTime - startTime) / CLOCKS_PER_SEC);
    } else{
        printf("Error argv.");
    }
    return 0;
}

void eightpuzzle(int m[3][3])
{
    int flag;
    list open,closed,t,temp,p,q;
    closed=open=NULL;
    if(solvable(m))
    {
        open=insert(open,NULL,0,m);
        while(open!=NULL)
        {
            if(!goaltest(open))
            {
                temp=movegen(open);
                t=open;
                open=dequeue(open);
                t->next=NULL;
                if(closed==NULL)
                {
                    closed=t;
                }
                else
                {
                    p=closed;
                    while(p->next!=NULL)
                    {
                        p=p->next;
                    }

                    p->next=t;
                }
                while(temp!=NULL)
                {
                    q=temp;
                    temp=dequeue(temp);
                    q->next=NULL;
                    t=open;
                    while(t!=NULL&&!(compare(t->data,q->data)))
                    {
                        t=t->next;
                    }
                    if(t==NULL)
                    {
                        p=closed;
                        while(p!=NULL&&(!compare(p->data,q->data)))
                        {
                            p=p->next;
                        }
                        if(p==NULL)
                        {
                            if(solvable(q->data))
                            {
                                flag=0;
                                open=proenqueue(open,q,flag);
                            }
                        }
                    }
                }
            }
            else
            {
                result(open);
                return;
            }
        }
    }
    else
    {
        printf("\nnot solvable.");
    }
}

list dequeue(list t)
{
    return t->next;
}

list proenqueue(list head,list temp,int flag)
{
    list t=head;
    if(t!=NULL)
    {
        if(flag==0)
        {
            if(t->pro>temp->pro)
            {
                temp->next=t;
                return temp;
            }
            else if(t->pro==temp->pro)
            {
                if(t->level<=temp->level)
                {
                    temp->next=t;
                    return temp;
                }
                else
                    flag=1;
            }
            else
                flag=1;
        }
        if(t->next!=NULL)
        {
            if(t->next->pro<temp->pro)
            {
                t->next=proenqueue(t->next,temp,flag);
            }
            else if(t->next->pro==temp->pro)
            {
                if(t->next->level<=temp->level)
                {
                    temp->next=t->next;
                    t->next=temp;
                }
                else {
                    t->next = proenqueue(t->next, temp, flag);
                }
            }
            else
            {
                temp->next=t->next;
                t->next=temp;
            }
        }
        else
        {
            if(t->pro<temp->pro)
            {
                t->next=temp;
            }
            else if(t->pro==temp->pro)
            {
                if(t->level<temp->level)
                {
                    temp->next=t;
                    return temp;
                }
                else
                {
                    t->next=temp;
                }
            }
            else
            {
                temp->next=t;
                return temp;
            }
        }
    }
    else
    {
        return temp;
    }
    return t;
}
list movegen(list t)
{
    list head;
    int i,j,itemp=0,jtemp=0,temp[3][3];
    head=NULL;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            temp[i][j]=t->data[i][j];
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(temp[i][j]==0)
            {
                itemp=i;
                jtemp=j;
            }
        }
    }
    i=itemp;
    j=jtemp;
    if((i-1)>=0)
    {
        temp[i][j]=temp[i-1][j];
        temp[i-1][j]=0;
        head=insert(head,t,t->level,temp);
        temp[i-1][j]=temp[i][j];
        temp[i][j]=0;
    }
    if((i+1)<3)
    {
        temp[i][j]=temp[i+1][j];
        temp[i+1][j]=0;
        head=insert(head,t,t->level,temp);
        temp[i+1][j]=temp[i][j];
        temp[i][j]=0;
    }
    if((j-1)>=0)
    {
        temp[i][j]=temp[i][j-1];
        temp[i][j-1]=0;
        head=insert(head,t,t->level,temp);
        temp[i][j-1]=temp[i][j];
        temp[i][j]=0;
    }
    if((j+1)<3)
    {
        temp[i][j]=temp[i][j+1];
        temp[i][j+1]=0;
        head=insert(head,t,t->level,temp);
        temp[i][j+1]=temp[i][j];
        temp[i][j]=0;
    }
    t=head;
    return t;
}
list insert(list head,list parent,int plev,int temp[3][3])
{
    list t=head;
    list tnode;
    int i,j;
    if(t!=NULL)
    {
        t->next=insert(t->next,parent,plev,temp);
    }
    else
    {
        tnode=malloc(sizeof(struct node));
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                tnode->data[i][j]=temp[i][j];
            }
        tnode->level=plev+1;
        tnode->parent=parent;
        tnode->next=NULL;
        priority(tnode);
        t=tnode;
    }
    return t;
}
int goaltest(list t)
{
    int test[3][3]={{1,2,3},{4,5,6},{7,8,0}};

    if(compare(test,t->data))
        return 1;
    else
        return 0;
}

int compare(int x[3][3],int y[3][3])
{
    int i,j=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(x[i][j]!=y[i][j])
            {
                return 0;
            }
        }
    }
    if(i==3 && j==3)
        return 1;
    else
        return 0;
}
void result(list t)
{
    if(t!=NULL)
    {
        result(t->parent);
        printout(t->data);
    }
}

void printout(int x[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {for(j=0;j<3;j++)
        {
            if(x[i][j]==0)
                printf("  ");
            else
                printf("%d ",x[i][j]);
        }
        if(i!=2)
            printf("\n");
    }
    printf("\n\n");
}

void priority(list t)
{
    int i,j;
    t->pro=t->level;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            t->pro=t->pro+abs(check[t->data[i][j]].row-i)+abs(check[t->data[i][j]].col-j);
        }
}
int solvable(int a[3][3])
{
    int inv=getinversion((int *)a);
    if(inv%2==0)
        return 1;
    else
        return 0;
}
int getinversion(int a[])
{
    int i,j;
    int inv=0;
    for(i=0;i<8;i++)
        for(j=i+1;j<9;j++)
        {
            if(a[i]&&a[j]&&a[i]>a[j])
            {
                inv++;
            }
        }
    return inv;
}
void assign()
{
    int goal[3][3]={{1,2,3},{4,5,6},{7,8,0}};
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            check[goal[i][j]].row=i;
            check[goal[i][j]].col=j;
        }
}