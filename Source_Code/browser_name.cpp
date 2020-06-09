// A simple CGI program
// This will retrieve the Browser name and spit it
// to the browser

#include <stdio.h>
#include <stdlib.h>
void EmitHTTPHeader()
{
    // printf("HTTP/1.0 200 OK\n");
     printf("Content-type: text/html\n\n\n");

}

void main( int argc , char **argv )
{
        char *lpstrBrowser = getenv("HTTP_USER_AGENT");

        EmitHTTPHeader();
       	printf("<HTML><BODY>\n");
	printf("<TITLE>");
	printf("CGI sample program");
	printf("</TITLE>");
        printf("<H1>%s</H1>\n",lpstrBrowser);
	printf("</BODY></HTML>\n");
	return ;

}