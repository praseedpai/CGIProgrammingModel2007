// A simple CGI program
// This Program is used to demonstrate the GET vs POST
// to the browser

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void EmitHTTPHeader()
{
     printf("HTTP/1.0 200 OK\n");
     printf("Content-type: text/html\n\n\n");

}

void main( int argc , char **argv )
{
        char *lpstrMethod = getenv("REQUEST_METHOD");

	



        EmitHTTPHeader();

        if ( strnicmp(lpstrMethod,"GET",3) == 0 )
        {
		printf("<form method=\"post\" action=\"http://localhost/cgi/fourth.exe\">");
		printf("<input type=\"hidden\" name=\"value1\" value=\"test1\">");
		printf("<input type=\"hidden\" name=\"value2\" value=\"test2\">");
		printf("<input type=\"hidden\" name=\"value3\" value=\"test3\">");
		printf("<input type=\"submit\">");
		printf("</form>\n");


        }
        else if ( strnicmp(lpstrMethod,"POST",4) == 0 )
	{
		 char* lpszContentLength = getenv("CONTENT_LENGTH");
		 char* lpszBuffer;
		 int nContentLength = atoi(lpszContentLength);
		 lpszBuffer =(char *) malloc(atoi(lpszContentLength)+1);  // allocate a buffer
          	 memset(lpszBuffer, 0, atoi(lpszContentLength)+1);  // zero it out
        	 fread(lpszBuffer,1,atoi(lpszContentLength),stdin);  // get data
        	cout << "Content-type: text/html" << endl << endl;
                cout << "<html>" << endl;
                cout << "<body>" << endl;
		cout << "<p>" << endl;
		cout << "Hello! You sent " << lpszContentLength << " bytes of data which read: <br>" << endl;
		cout << lpszBuffer << endl;
		cout << "" << endl;
		cout << "" << endl;
                cout << "";

                free(lpszBuffer);






	}
        
       
	return ;

}