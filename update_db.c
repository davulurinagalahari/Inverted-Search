#include "heder.h"   // Header file containing structure declarations and macros

int update_database(Hash *arr)
{
    // Check if database is already created or updated
    if(create_status==1 || update_status==1)
    {
        printf("database is already created using create/update database, so update database failed.\n");
        return FAILURE;
    }

    char filename[100];

    // Read filename from user
    printf("Enter the filename:");
    scanf("%99s",filename);

    // Check whether file extension is .txt
    if(strstr(filename,".txt")==NULL) 
    {
        return FAILURE;
    }

    FILE *fp;

    // Open file in read mode
    fp=fopen(filename,"r");

    // Check file open failure
    if(fp==NULL)
    {
        return FAILURE;
    }

    char word[1000];

    // Read first word from file
    if(fscanf(fp,"%999s",word) != 1)
    {
        fclose(fp);
        return FAILURE;
    }

    // Validate magic string
    if(strcmp(word,"**")!=0)
    {
        fclose(fp);
        return FAILURE;
    }

    // Read database entries from file
    while(fscanf(fp,"%s",word)!=EOF)
    {
        // Remove newline character if present
        word[strcspn(word,"\n")]='\0';

        int len = strlen(word);

        // Remove '#' at end of string
        if(len > 0 && word[len - 1] == '#')
            word[len - 1] = '\0';

        // Extract index value
        char *token=strtok(word+1,";");

        if(token == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        int index=atoi(token);

        // Extract word
        token=strtok(NULL,";");

        if(token == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        char wordd[100];
        strcpy(wordd,token);

        // Extract file count
        token=strtok(NULL,";");

        if(token == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        int f_count=atoi(token);

        // Allocate memory for main node
        Main_node *mnew=malloc(sizeof(Main_node));

        if(mnew == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        // Allocate memory for word
        mnew->word = malloc(strlen(wordd) + 1);

        if(mnew->word == NULL)
        {
            free(mnew);
            fclose(fp);
            return FAILURE;
        }

        // Copy word into main node
        strcpy(mnew->word,wordd);

        // Initialize main node data
        mnew->f_count=f_count;
        mnew->len=strlen(wordd);
        mnew->S_link=NULL;
        mnew->M_link=NULL;

        Sub_node *prev=NULL;

        // Read sub node details
        while((token=strtok(NULL,";")) != NULL)
        {
            // Stop if '#' encountered
            if(strcmp(token,"#") == 0)
                break;

            char fname[100];

            // Copy file name
            strcpy(fname,token);

            // Extract word count
            token=strtok(NULL,";");

            if(token == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            int w_count=atoi(token);

            // Allocate memory for sub node
            Sub_node *snew=malloc(sizeof(Sub_node));

            if(snew == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            // Allocate memory for file name
            snew->f_name = malloc(strlen(fname) + 1);

            if(snew->f_name == NULL)
            {
                free(snew);
                fclose(fp);
                return FAILURE;
            }

            // Copy file name
            strcpy(snew->f_name,fname);

            // Initialize sub node data
            snew->w_count=w_count;
            snew->link=NULL;

            // Link sub node to main node
            if(mnew->S_link==NULL)
                mnew->S_link=snew;
            else
                prev->link=snew;

            // Update previous pointer
            prev=snew;
        }

        // Insert main node into hash table
        mnew->M_link=arr[index].link;
        arr[index].link=mnew;
    }

    // Close file
    fclose(fp);

    // Update database status
    update_status=1;

    // Return success
    return SUCCESS;
}