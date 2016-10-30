#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <direct.h>

#include "main.h"

#define MAX_LINE 1024

int split_file(void)
{
    FILE *fp_read;
    size_t BUFSIZE = 1024;
    
    char read_buf[MAX_LINE];
    char *fp_read_name = "Test.txt";
    //char *fp_write_name = "Output.txt"
    char read_string[MAX_LINE];
    char cmp1[1] = ":"; //for comparison with the sentence
    char cmp2[1] = ","; //for comparison with the sentence
    
    int count_array[MAX_LINE];
    int loop_count = 0;
    int txt_line_count = 1;

    fp_read = fopen(fp_read_name, "r");
    if (fp_read == NULL) //normal return 0, error return NULL, and the message save at errno
    {
        printf("Open the file error: %s\n", fp_read_name);
        exit(1);
    }
    setvbuf(fp_read, NULL, _IOFBF, BUFSIZE);
    
    while (fgets(read_string, MAX_LINE, fp_read) != NULL)
    {
        //printf("%s", read_string);
        if (strlen(read_string) > 28)
        {
            if (read_string[2] == cmp1[0])
            {
                if (read_string[5] == cmp1[0])
                {
                    if (read_string[8] == cmp2[0])
                    {
                        count_array[loop_count] = txt_line_count - 1; //mark the sentence start address
                        loop_count += 1;
                        //printf("%s", read_string);
                    }
                }
            }
        }
        
        txt_line_count += 1;
    }
    fclose(fp_read);
    
    count_array[loop_count] = 99999;
    
    /* open the file again to split it */
    FILE *fp_read_0, *fp_write;
    
    char write_name_demo[100];
    char *fp_write_name_demo = write_name_demo;
    
    fp_read_0 = fopen(fp_read_name, "r");
    
    if (fp_read_0 == NULL)
    {
        printf("Open the file again error: %s\n", fp_read_name);
        exit(1);
    }
    setvbuf(fp_read_0, NULL, _IOFBF, BUFSIZE);
    
    int split_loop_count = 0;
    int fgets_loop_count = 1;
    int split_address_one, split_address_two; //to save the sentence start address and end address
    int array_length = sizeof(count_array);
    
    if (!access("temp", 0)) // check the file 'temp' existed
    {
        if (_mkdir("temp") == 0) // try to mkdir the file
        {
            printf("There is no file name 'temp' and the program can't make it, please check you permissions");
        }
    }
    
    while (fgets(read_string, MAX_LINE, fp_read_0) != NULL)
    {
        
        split_address_one = count_array[split_loop_count];
        split_address_two = count_array[split_loop_count + 1];
        /* make the save file name */
        sprintf(write_name_demo, "temp/split_temp_%d", split_loop_count);
        
        fp_write = fopen(fp_write_name_demo, "a+");
        if (fp_write == NULL)
        {
            printf("fp_write error");
        }
        /* there is write the sentence in the file */
        fprintf(fp_write, "%s", read_string);
        
        fclose(fp_write);
        fgets_loop_count += 1;
        if (fgets_loop_count >= split_address_two)
        {
            split_loop_count += 1;
        }
    }
    fclose(fp_read_0);
    return split_loop_count - 1;
}
