#include "heder.h"
int is_file_already_indexed(Hash *HT, char *filename)
{
    for(int i = 0; i < 28; i++)
    {
        Main_node *temp = HT[i].link;
        while(temp)
        {
            Sub_node *stemp = temp->S_link;
            while(stemp)
            {
                if(strcmp(stemp->f_name, filename) == 0)
                    return SUCCESS;
                stemp = stemp->link;
            }
            temp = temp->M_link;
        }
    }
    return FAILURE;
}
int create_database(Hash *HT,Node *head)
{
    if(head == NULL)
    {
        printf("No files are available from command line to create database\n");
        return FAILURE;
    }

    int is_new_file_added = 0;
    while(head)
    {
        if(is_file_already_indexed(HT, head->f_name) == SUCCESS)
        {
            head = head->link;
            continue;
        }

        FILE *fptr;
        fptr=fopen(head->f_name,"r");
        if(fptr==NULL)  return FAILURE;
        char word[100];
        while(fscanf(fptr,"%99s",word)==1)
        {
            int index;
            if(word[0]>='A' && word[0]<='Z')
                index=word[0]-'A';
            else if(word[0]>='a' && word[0]<='z')
                index=word[0]-'a';
            else if(isdigit(word[0]))
                index=26;
            else index=27;

            if(create_mainNode(HT,index,word,head->f_name)==FAILURE)
            {
                fclose(fptr);
                return FAILURE;
            }
            
        }
        fclose(fptr);
        is_new_file_added = 1;
        head=head->link;
    }

    if(is_new_file_added == 0)
    {
        printf("No new files found to add into database\n");
        return SUCCESS;
    }
    create_status=1;
    return SUCCESS;

}

int create_mainNode(Hash *HT,int index,char *word,char *filename)
{
    if(HT[index].link==NULL)
    {
        Main_node *Mnew=malloc(sizeof(Main_node));
        if(Mnew==NULL)   return FAILURE;
        Mnew->f_count=1;
        Mnew->word=malloc(sizeof(char)*(strlen(word)+1));
        if(Mnew->word==NULL)
        {
            free(Mnew);
            return FAILURE;
        }
        strcpy(Mnew->word,word);
        Mnew->len=strlen(word);
        Mnew->M_link=NULL;
        Mnew->S_link=NULL;
        Sub_node *Snew=malloc(sizeof(Sub_node));
        if(Snew==NULL)
        {
            free(Mnew->word);
            free(Mnew);
            return FAILURE;
        }
        Snew->f_name=malloc(sizeof(char)*(strlen(filename)+1));
        if(Snew->f_name==NULL)
        {
            free(Snew);
            free(Mnew->word);
            free(Mnew);
            return FAILURE;
        }
        strcpy(Snew->f_name,filename);
        Snew->link=NULL;
        Snew->w_count=1;
        Mnew->S_link=Snew;
        HT[index].link=Mnew;
        return SUCCESS;
    }
    Main_node *temp = HT[index].link;
    Main_node *prev=NULL;
    while(temp)
    {
        if(strcmp(temp->word,word)==0)
        {
            Sub_node *stemp=temp->S_link;
            while(stemp)
            {
                if(strcmp(stemp->f_name,filename)==0)
                {
                    stemp->w_count++;
                    return SUCCESS;
                }
                stemp=stemp->link;
            }
        Sub_node *Snew=malloc(sizeof(Sub_node));
        if(Snew==NULL)  return FAILURE;
        Snew->f_name=malloc(sizeof(char)*(strlen(filename)+1));
        if(Snew->f_name==NULL)
        {
            free(Snew);
            return FAILURE;
        }
        strcpy(Snew->f_name,filename);
        Snew->w_count=1;
        Snew->link=temp->S_link;
        temp->S_link=Snew;
        temp->f_count++;
        return SUCCESS;
        }
        prev=temp;
        temp=temp->M_link;

    }
    Main_node *Mnew=malloc(sizeof(Main_node));
    if(Mnew==NULL)  return FAILURE;
    Mnew->word=malloc(sizeof(char)*(strlen(word)+1));
    if(Mnew->word==NULL)
    {
        free(Mnew);
        return FAILURE;
    }
    strcpy(Mnew->word,word);
    Mnew->f_count=1;
    Mnew->len=strlen(word);
    Mnew->M_link=NULL;
    Sub_node *snew=malloc(sizeof(Sub_node));
    if(snew==NULL)
    {
        free(Mnew->word);
        free(Mnew);
        return FAILURE;
    }
    snew->f_name=malloc(sizeof(char)*(strlen(filename)+1));
    if(snew->f_name==NULL)
    {
        free(snew);
        free(Mnew->word);
        free(Mnew);
        return FAILURE;
    }
    strcpy(snew->f_name,filename);
    snew->w_count=1;
    snew->link=NULL;
    Mnew->S_link=snew;
    prev->M_link=Mnew;
    return SUCCESS;
}