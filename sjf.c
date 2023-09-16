#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid;
    int bt;
    int at;
    int ft;
    int tat;
    int wt;
    
} Process;

void sort(int n, Process p[n])
{
    int i, j;
    Process temp;
    
    for(i=0; i<n-1; i++)
        for(j=0; j<(n-1-i); j++)
            if((p[j].at > p[j + 1].at) || ((p[j].at == p[j+1].at) && (p[j].bt > p[j+1].bt)))
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            } 
}

int execute(int t, int n, Process p[n])
{
    //fills in values for tat and wt for each process
    int i;
    for(i=0; i<n; i++)
    {
        if(i==0)
            t = p[i].at;
        
        t = t +p[i].bt;
        
        p[i].ft = t;
        p[i].tat = p[i].ft - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    return t;
}

void print_table(int n,Process p[n])
{
    int i, avgw = 0, avgt = 0;
    printf("\n\n\tpid\tAt\tBt\tFt\tTAt\tWt\n");
    for(i=0;i<n;i++)
    {
        avgw = avgw + p[i].wt;
        avgt = avgt + p[i].tat;
        if(p[i].pid != -1)
            printf("\n\t%d\t%d\t%d\t%d\t %d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ft,p[i].tat,p[i].wt);
    }
    avgw = (avgw/n);
    avgt = (avgt/n);
    printf("\n\n\tAverage waiting time: %d units\n\tAverage turn-around time: %d units",avgw,avgt);
}

void print_chart(int n, Process p[n])
{
    int i, j;
    printf("\n\t+");
    for(i=0; i<n; i++)
    {   for(j=1; j<=p[i].bt; j++)
            printf("---");
        printf("+");    
    }
    printf("\n\t|");
    for(i=0; i<n; i++)
    {
        printf(" P%d",p[i].pid);
        for(j=1; j<p[i].bt; j++)
            printf("   ");
        printf("|");
    }
    printf("\n\t+");    
    for(i=0; i<n; i++)
    {   for(j=1; j<=p[i].bt; j++)
            printf("---");
        printf("+");    
    }
    
    int check = 0;
    printf("\n\t%d",p[0].at);
    if(p[0].at > 9)
        check = 1;
    for(i=0; i<n; i++)
    {   for(j=1; j<=p[i].bt; j++)
            if(check == 1)      //try commenting for here
            {
                printf("  ");
                check = 0;
            }
            else            
                printf("   ");  //to here and just keep printf("   ");
        printf("%d",p[i].ft);
        if(p[i].ft > 9)
            check = 1;
    }

}

int main()
{
    int n, i, j ;
    printf("\n\t\t\t\tSJF\n\n\t Enter the total number of processes: "); scanf("%d",&n);
    Process p[n];

    printf("\n\t Enter the following data for each process: ");
    for(i=0; i<n; i++)
    {
        printf("\n\t Process %d:\n\tArrival time: ",i+1);
        scanf("%d",&p[i].at);
        printf("\tBurst time: ");
        scanf("%d",&p[i].bt);
        p[i].pid = i+1;
    }
    sort(n,p); //sorted on burst time
    
    int t = 0;
    t = execute(t,n,p); //calculating wt and tat for each process
    //tat = ft - at
    //wt = tat - bt
    //printf("\n\t %d \n",t);
    print_table(n,p);
    printf("\n\n\t Gnatt chart\n");
    print_chart(n,p);
    
    int upbt = 5,  lowbt = 1, rand_at, rand_bt;
    
    int s = t + 2;
    int m;
    printf("\n\n\n\t\t\tRandom CPU Burst\n\n\t Enter the total number of processes: "); scanf("%d",&m);
    int o = n+m;
    Process q[m];
    for(i=0; i<m; i++)
    {
        rand_at = s;
        s++;                
        rand_bt = (rand() % (upbt - lowbt + 1)) + lowbt;
        q[i].at = rand_at; 
        q[i].bt = rand_bt;
        q[i].pid = i+1;
    }
    
    sort(m,q);
    
    
    t = execute(t,m,q);
    

    print_table(m,q);
    printf("\n\n\t Gnatt chart\n");
    print_chart(m,q);

    printf("\n\n");
    
    printf("\n\n\t Combined Gnatt chart\n");
    print_chart(n,p);
    printf("\n\n\t\t--IO of 2 units--\n");
    print_chart(m,q);
    
    return 0;
}





