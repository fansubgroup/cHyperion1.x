#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "main.h"

int main(void)
{
    char translation_txt[1000];
    char translation_result[1000];
    
    file_count = split_file(); //we first split the origin file
    
    for (int i = 0; i <= file_count, i ++)
    {
        *translation_txt = get_goal();
        *translation_result = translation(*translation_txt);
        write_result(*translation_result);
    }
}
