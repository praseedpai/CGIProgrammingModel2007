// A simple CGI program
// This will retrieve some enivironment variables and spit it
// to the browser ... Demonstrates the use of Cookies as well
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//
//  
//
//
using namespace std;


//
//
//   Emit the Header and cookie data
//
//
void EmitHTTPHeader(char *cookievalue)
{
 
     int i = 0;

     if ( cookievalue != 0 && *cookievalue != 0 ) 
         i = atoi(cookievalue)+1;
        
     printf("HTTP/1.0 200 OK\n");
     printf("Set-Cookie: COUNTER=%d;\n",i);
     printf("Content-type: text/html\n\n\n");
    

}

//
//
// Retrieve the value corresponding to the key
//
//
//

char *GetCookieValueForKey( const char *keyvalue )
{
   char * ret_val = getenv("HTTP_COOKIE");

   if ( ret_val == 0)
          return 0;


   char *strptr = strstr(ret_val,keyvalue);

   if (strptr == 0 ) 
        return 0;

   while ( *strptr != 0 && *strptr != '=' )
                strptr++;

   if ( strptr == 0 )
          return 0;

   strptr++;

   ret_val = (char *) malloc(255);

	if ( ret_val == 0 ) return 0;

   char *sret = ret_val;       

   while ( *strptr != 0 && *strptr != ';' )
              *ret_val++ = *strptr++;   

   if ( *strptr == ';' )
	*ret_val = 0;

   return sret;


}

//
//
//
//  user entry point 
//
//
void main( int argc , char **argv )
{
        char *lpstrMethod = getenv("REQUEST_METHOD");

	
        if ( lpstrMethod == 0 )
 		return; 

          
        EmitHTTPHeader(GetCookieValueForKey("COUNTER"));


        if ( strnicmp(lpstrMethod,"GET",3) == 0 )
        {
		printf("<form method=\"post\" action=\"http://localhost/cgi/cookie.exe\">");
		printf("<input type=\"hidden\" name=\"value1\" value=\"test1\">");
		printf("<input type=\"hidden\" name=\"value2\" value=\"test2\">");
		printf("<input type=\"hidden\" name=\"value3\" value=\"test3\">");
		printf("<input type=\"submit\">");
		printf("</form>\n");


        }
        else if ( strnicmp(lpstrMethod,"POST",4) == 0 )
	{
                 char *tmpCookie ="HELLO"; 
                 if (getenv("HTTP_COOKIE") != NULL) 
                         tmpCookie = getenv("HTTP_COOKIE"); 
                   
                
       
                
		 char* lpszContentLength = getenv("CONTENT_LENGTH");
		 char* lpszBuffer;
		 int nContentLength = atoi(lpszContentLength);
		 lpszBuffer =(char *) malloc(atoi(lpszContentLength)+1);  // allocate a buffer
          	 memset(lpszBuffer, 0, atoi(lpszContentLength)+1);  // zero it out
        	 fread(lpszBuffer,1,atoi(lpszContentLength),stdin);  // get data
        	
                cout << "<html>" << endl;
                cout << "<body>" << endl;
		cout << "<p>" << endl;
		cout << "Hello! You sent " << lpszContentLength << " bytes of data which read: <br>" << endl;
		cout << lpszBuffer << "  " <<endl;
                cout << "------------------" << endl;  
             
                char *last_env = GetCookieValueForKey("COUNTER");

                if ( last_env != 0 )  
                    cout <<  last_env  << endl; 
                          
              	cout << "" << endl;
		cout << "" << endl;
                cout << "";

                free(lpszBuffer);






	}
        
       
	return ;

}