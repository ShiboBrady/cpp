#include "bash.h"

void del_space(char *str)
{
    char *p, *q;
    p = q = str;
    int count;
    while(*p == 32){/*如果开头就是空格*/
        p ++;
        count ++;/*纪录空格的个数*/
    }
    while(*p != 0){/*从后向前依次移动空格个数个位置*/
        *(p - count) = *p;
        p ++;
    }
    *(p - count) = 0;/*别忘了最后面的‘/0’*/
    p = q;/*让p回到原来的位置*/

    while(*p != 0){
        count = 0;
        if(*p == 32 && *(p + 1) == 32){/*当出现了连续空格*/
            p ++;
            q = p;/*记下多余空格的第一个位置*/
            while(*p == 32){
                p ++;
                count ++;/*统计多余空格的个数*/
            }
            if(*p == 0){/*如果某个字符后面到结尾全部是空格*/
                *(p - count - 1) = 0;
                break;
            }
            while(*p != 0){/*从后往前移动多余空格个数个位置*/
                *(p - count) = *p;
                p ++;
            }
            *(p - count) = 0;
            p = q;
        }
        else{
            p ++;
        }
    }
}

void cmd_parse(char *cmd_line, char ***cmd)
{
    char word[20];
    int pos = 0, i = 0;
    while(bzero(word, 100), sscanf(cmd_line + pos, "%s", word) == 1){
        if(i == 0){
            *cmd = (char **)calloc(1, sizeof(char *));
        }
        else{
            *cmd = (char **)realloc(*cmd, sizeof(char *));
        }
        (*cmd)[i] = (char *)calloc(1, (strlen(word) + 1) * sizeof(char));
        strcpy((*cmd)[i], word);
        pos += strlen(word) + 1;
    }
}
