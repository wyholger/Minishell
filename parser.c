#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


char *ft_double_quotes(char *str, int i)
{
    int k;
    char tmp;

    k = 0;
    




}





void parser(char *str, char **env)
{
// "", '', \, $, ;, |

int i;

i = 0;
// возможно пробел увести в отдельную функцию 
// куда будем передавать строку и структуру.
while (str[i] != ' ' || str[i] != '\0')
{
    if (str[i] == "\"")
        ft_double_quotes(str, i);
    if (str[i] == "\'")
        ft_quotes(str, i);
    if (str[i] == "\\")
        ft_backslash(str, i);
    if (str[i] == "$")
        ft_dollar(str, i, env);
    if (str[i] == ";")
        ft_semocolon(str, i);
    if (str[i] == "|")
        ft_pipe(str, i);
    i++;
    // еще функции для < << > >>
}
}


int main(int argc, char **argv, char **env)
{

    // нужно создать структуру
    char *str;





}