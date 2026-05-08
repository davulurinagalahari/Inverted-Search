#include "heder.h"
int save_database(Hash *arr)
{
    char filename[100];
    printf("Enter the filename:");
    scanf("%s",filename);
    if(strstr(filename,".txt")==NULL)
        return FAILURE;
    FILE *fptr=fopen(filename,"w");
    if (fptr == NULL)
    {
        printf("Error: Unable to create database file\n");
        return FAILURE;
    }
    fprintf(fptr,"**\n");
    for(int i=0;i<28;i++)
    {
        if(arr[i].link!=NULL)
        {
            Main_node *temp=arr[i].link;
            while(temp)
            {
                fprintf(fptr,"#");
                fprintf(fptr, "%d;%s;%d;", arr[i].index, temp->word, temp->f_count);
                Sub_node *stemp=temp->S_link;
                while(stemp)
                {
                    fprintf(fptr, "%s;%d;", stemp->f_name, stemp->w_count);
                    stemp=stemp->link;
                }   
                fprintf(fptr,"#\n");
                temp=temp->M_link;
            }
        }
    }
    fclose(fptr);
    return SUCCESS;
}