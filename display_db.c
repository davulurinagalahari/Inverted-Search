
#include "heder.h"   
int display_database(Hash *arr,int size)
{
    // Check if array is NULL or size is 0
    if(size==0 || arr==NULL)
        return FAILURE;

    // Print table header
    printf("--------------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-20s %-10s\n","Index","Word","F_count","F_name","W_count");
    printf("--------------------------------------------------------------------------------\n");
    // Traverse hash table
    for(int i=0;i<size;i++)
    {
        // Skip empty index positions
        if(arr[i].link==NULL)
            continue;

        // Point to main node
        Main_node *mtemp=arr[i].link;

        // Traverse main node list
        while(mtemp)
        {
            // Print index, word and file count
            printf("%-10d %-15s %-10d ",arr[i].index,mtemp->word,mtemp->f_count);

            // Point to sub node
            Sub_node *stemp=mtemp->S_link;

            // Traverse sub node list
            while(stemp)
            {
                // Print file name and word count
                printf("%-20s %-10d",stemp->f_name,stemp->w_count);

                // Move to next sub node
                stemp=stemp->link;

                // Formatting for next sub node display
                if(stemp)
                    printf("\n%-10s %-15s %-10s ","","","");
            }

            // Move to next main node
            mtemp=mtemp->M_link;

            // Print newline after each main node
            printf("\n");
        }
    }
    // Print table footer
    printf("--------------------------------------------------------------------------------\n");
    // Return success status
    return SUCCESS;
}