#include "heder.h"   // Header file containing declarations and macros

int validate(int argc, char *argv[],Node **head)
{
    int count=0;   // Variable to count valid files

    // Traverse command line arguments
    for(int i=1;i<argc;i++)
    {
        FILE *fp;

        // Check whether file extension is .txt
        if(strstr(argv[i],".txt")==NULL)
            continue;

        // Open file in read mode
        fp=fopen(argv[i],"r");

        // Check if file opened successfully
        if(fp==NULL)
            continue;

        int ch;

        // Check whether file is empty
        if((ch=fgetc(fp))==EOF)
        {
            fclose(fp);   // Close empty file
            continue;
        }

        // Insert valid file into linked list
        if(create_file_list(head,argv[i])==FAILURE)
        {
            printf("%s file inserting to list failed\n",argv[i]);
        }
        else
            count++;   // Increment valid file count

        // Close file
        fclose(fp);
    }

    // No valid files found
    if(count==0)
        return FAILURE;

    // Some files are invalid
    if(count!=(argc-1))
        return P_SUCCESS;

    // All files are valid
    return SUCCESS;
}

int create_file_list(Node **head, char *filename)
{
    // Insert filename at end of linked list
    if(insert_last(head, filename) == FAILURE)
    {
        printf("INSERT operation failed\n");
        return FAILURE;
    }

    // Return success if insertion completed
    return SUCCESS;
}