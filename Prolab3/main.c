#include <stdio.h>
#include <string.h>
#include <conio.h>

struct node//Alýnan Kodun Kaynaðý: https://meminoglu.medium.com/tek-y%C3%B6nl%C3%BC-ba%C4%9Fl%C4%B1-listeler-hakk%C4%B1nda-her-%C5%9Fey-1-2-a7b0ab95a0a0
{
    const char *data;
    struct node* next;
};

struct node* Start;
void traverseList()
{
    struct node* temp = Start;
    while(temp != NULL)
    {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
}
struct node* yeniDugum(const char *data)
{
    struct node* dugum = (struct node*)malloc(sizeof(struct node));
    dugum->data = data;
    dugum->next = NULL;
    return(dugum);
}
void sonaElemanEkle(const char *data)
{
    struct node* eklenecekDugum = yeniDugum(data);
    if(Start == NULL)
    {
        Start = eklenecekDugum;
    }
    else
    {
        struct node* temp = Start;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = eklenecekDugum;
    }

}
void basaEkle(const char *data)
{
    struct node* eklenecekDugum = yeniDugum(data);
    if(Start == NULL)
        Start = eklenecekDugum;
    else
    {
        struct node* temp = Start;
        Start = eklenecekDugum;
        Start->next = temp;
    }

}
void arayaElemanEkle(const char *eklenecekData, const char *onuneEklenecekData)
{
    struct node* eklenecekDugum = yeniDugum(eklenecekData);
    if(Start == NULL)
        basaEkle(eklenecekData);
    else
    {
        struct node* temp = Start;
        while(temp->data != onuneEklenecekData)
        {
            temp = temp->next;
        }
        if(temp->next == NULL)
            sonaElemanEkle(eklenecekData);
        else
        {
            struct node* sonrakiEleman = temp->next;
            temp->next = eklenecekDugum;
            eklenecekDugum->next = sonrakiEleman;
        }
    }
}
struct node* q=NULL;
void yazdir(int sayi[])
{
    int z=0;
    int a=0;
    q=Start;
    while(q->next!=NULL)
    {
        z++;
        printf("%d. %s:%d\n",z,q->data,sayi[a]);
        q=q->next;
        a++;
    }
    printf("%d. %s:%d\n",z+1,q->data,sayi[a]);

}

int main()
{
    const char*bosluk=" ";
    char birsatir[5000];
    char* birkelime=NULL;
    char *dizi[5000];
    int x=0;
    int say[5000];
    int y=0;
    int i=0;
    char *h;
    int t;
    FILE *fp=fopen("kou.txt","r");
    while(!feof(fp))
    {
        if(fgets(birsatir,500,fp)==NULL)
            break;
        fscanf(fp,"%c",&birsatir);
        birkelime=strtok(birsatir,bosluk);
        while(birkelime!=NULL)
        {
            dizi[i]=birkelime;
            birkelime=strtok(NULL,bosluk);
            i++;
            y++;
        }
    }
    for(int a=0; a<y; a++)
    {
        for(int b=0; b<y; b++)
        {
            if(strcmp(dizi[a],dizi[b])==0)
            {
                x++;
            }
        }
        say[a]=x;
        x=0;
    }
    for(i=0; i<y; i++)
    {
        for(int j=0; j<y; j++)
        {
            if(say[j]<=say[i])
            {
                t=say[i];
                h=dizi[i];
                say[i]=say[j];
                dizi[i]=dizi[j];
                say[j]=t;
                dizi[j]=h;
            }
        }
    }
    for (int g = 0; g < y; g++)
    {
        for (int j = g + 1; j < y;)
        {
            if (strcmp(dizi[j],dizi[g])==0)
            {
                for (int k = j; k <y; k++)
                {
                    dizi[k] = dizi[k + 1];
                    say[k] = say[k+1];
                }
                y--;
            }
            else
                j++;
        }
    }

basaEkle(dizi[0]);


    for(int t=0; t<y-1; t++)
    {

        if(say[t+1]<=say[t])
        {
            sonaElemanEkle(dizi[t+1]);

        }
        else if(say[t+1]>=say[t-1]&&say[t]<say[t+1]&&say[t-2]>=say[t+1]&&say[0]>=say[t+1])
        {
            arayaElemanEkle(dizi[t+1],dizi[t-2]);


        }
        else
        {
            if(say[t+1]>=say[0])
            {
                basaEkle(dizi[t+1]);

                say[0]=say[t+1];
            }

        }
    }
    yazdir(say);

    return 0;
}



