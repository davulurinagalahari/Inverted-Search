#include "heder.h"   // Header file containing structure declarations and macros
int search_database(Hash *arr,char *word)
{
    // Read word from user
    printf("Enter word to search: ");
    scanf("%49s", word);
    int index;
    // Calculate index for uppercase letters
    if(word[0]>='A' && word[0]<='Z')
        index=word[0]-'A';
    // Calculate index for lowercase letters
    else if(word[0]>='a' && word[0]<='z')
        index=word[0]-'a';
    // Assign index for digits
    else if(isdigit(word[0]))
        index=26;
    // Assign index for special characters
    else
        index=27;
    // Point to main node at calculated index
    Main_node *mtemp=arr[index].link;
    // Check if index is empty
    if (mtemp == NULL)
    {
        printf("No elements found in this index\n");
        return -1;
    }
    // Traverse main node list
    while(mtemp)
    {
        // Display searching word
        printf("\n🔍 Searching for: %s\n", word);

        // Compare word with database word
        if(strcmp(mtemp->word,word)==0)
        {
            // Display file count
            printf("file count=%d\n",mtemp->f_count);

            printf("Present in files:\n");

            // Point to sub node
            Sub_node *stemp=mtemp->S_link;

            // Traverse sub node list
            while(stemp)
            {
                // Display file name and word count
                printf("File name: %s ,Word count=%d\n",stemp->f_name,stemp->w_count);

                // Move to next sub node
                stemp=stemp->link;
            }

            // Word found successfully
            return SUCCESS;
        }

        // Move to next main node
        mtemp=mtemp->M_link;
    }
    // Word not found in database
    printf("Word NOT found in database\n");
    return FAILURE;
}