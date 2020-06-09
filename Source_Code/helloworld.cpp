// A simple CGI program
// This will emit the string Hello World to the Browser Window

#include <stdio.h>

void main( int argc , char **argv )
{
       
        printf("HTTP/1.0 200 OK\n");
        printf("Content-type: text/html\n\n\n");
	printf("<HTML><BODY>\n");
	printf("<TITLE>");
	printf("CGI sample program");
	printf("</TITLE>");
        printf("<H1>HELLO WORLD</H1>\n");
	printf("</BODY></HTML>\n");
	return ;

}