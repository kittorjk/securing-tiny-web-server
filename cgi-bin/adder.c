/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "csapp.h"

int isNumber(char *chr);

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0, result=0, eval1=0, eval2=0;

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
        p = strchr(buf, '&');
        *p = '\0';
        strcpy(arg1, buf);
        strcpy(arg2, p+1);
        eval1 = isNumber(arg1);
        eval2 = isNumber(arg2);
        n1 = atoi(arg1);
        n2 = atoi(arg2);
        result = n1 + n2;
    }

    /* Make the response body */
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);

    /* Check conditions to print result or error */
    if (eval1 == 0 || eval2 == 0) {
        sprintf(content, "%sOne or both of the values provided: %s + %s are not allowed!\r\n<p>", 
            content, arg1, arg2);
        sprintf(content, "%sPlease use integers only!\r\n", content);
    } else if ((n1 < 0 && n2 < 0 && result < 0) || (n1 > 0 && n2 > 0 && result > 0) || n1 == 0 || n2 == 0) {
        sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", 
            content, n1, n2, result);
        sprintf(content, "%sEvaluations are: %d + %d\r\n<p>", 
            content, eval1, eval2);
        sprintf(content, "%sThanks for visiting!\r\n", content);
    } else {
        sprintf(content, "%sOne or both of the values provided: %d + %d exceed the maximum value permitted!\r\n<p>", 
            content, n1, n2);
        sprintf(content, "%sPlease try with other values!\r\n", content);
    }
  
    /* Generate the HTTP response */
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}

int isNumber(char *chr) {
    int ret = 1;
    for (int i = 0; i < strlen(chr); i++) {
        if (!isdigit(chr[i])) 
            ret = 0;
    }
  
    return ret;
} 
/* $end adder */
