// A simple CGI program
// This will retrieve Brwoser name as well as incoming request's IP
// and dump it into  the browser

#include <stdio.h>
#include <stdlib.h>
void EmitHTTPHeader()
{
     printf("HTTP/1.0 200 OK\n");
     printf("Content-type: text/html\n\n\n");

}

void main( int argc , char **argv )
{
        char *lpstrBrowser = getenv("HTTP_USER_AGENT");
   	char* lpszRemoteHost = getenv("REMOTE_HOST");


        EmitHTTPHeader();
       	printf("<HTML><BODY>\n");
	printf("<TITLE>");
	printf("CGI sample program");
	printf("</TITLE>");
        printf("<H1>%s</H1>\n",lpstrBrowser);
                printf("<H1>%s</H1>\n",lpszRemoteHost );
	printf("</BODY></HTML>\n");
	return ;

}