/*  Project : Inverted search 
 *  Name: D.NAGA LAHARI
 *  Date : 07-05-2026
 *  Description:An inverted search project implementing inverted index for fast document searching.
 */
#include "heder.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int update_status = 0;
int create_status = 0;
int main(int argc,char* argv[])
{
    Node *head = NULL;
    if(argc <= 1)
    {
        printf("No input files provided\n");
        return 1;
    }
    int res;
    if((res = validate(argc, argv, &head)) == FAILURE)
    {
        printf("validation failed\n");
        return 1;
    }
    else if(res == P_SUCCESS)
    {
        printf("Some files validation failed\n");
    }
    printf("file node--> ");
    print_list(head);
    int choice;
    int size = 28;
    Hash arr[28];   
    for(int i = 0; i < size; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }
    do
    {
        printf("1.Create database\n2.Display database\n3.search database\n4.Save database\n5.Update database\n6.Exit\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            if(head == NULL)
            {
                printf("No files available to create database\n");
                break;
            }
            if(create_database(arr,head)==SUCCESS)
                printf("Database created successfully\n");
            else
                printf("Database creation failed\n");
            break;
        case 2:
            if(create_status == 0)
            {
                printf("Database not created yet\n");
                break;
            }
            display_database(arr,size);
            break;
        case 3:
        {
            char word[100];
            printf("Enter the word:");
            scanf("%s",word);
            if(search_database(arr,word)==FAILURE)
                printf("Word not found\n");
            break;
        }
        case 4:
            if(save_database(arr)==FAILURE)
                printf("Saving database FAILED\n");
            break;
        case 5:
            if(update_database(arr)==FAILURE)
                printf("Update database FAILED\n");
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    } while(choice != 6);
    return 0;
}
int print_list(Node *head)
{
    if(head==NULL)
        return FAILURE;
    while(head)
    {
        printf("%s ",head->f_name);
        head=head->link;
    }
    printf("\n");
    return SUCCESS;
}
int insert_last(Node **head,char *word)
{
    Node *new=malloc(sizeof(Node));
    if(new==NULL)
        return FAILURE;
    int len=strlen(word);
    new->f_name=malloc(sizeof(char)*(len+1));
    if(new->f_name==NULL)
    {
        free(new);
        return FAILURE;
    }
    strcpy(new->f_name,word);
    new->link=NULL;
    if(*head==NULL)
    {
        *head=new;
        return SUCCESS;
    }
    Node *temp=*head;
    while(temp->link)
    {
        temp=temp->link;
    }
    temp->link=new;

    return SUCCESS;
}