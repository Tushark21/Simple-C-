#include <iostream>

using namespace std;

int main(){
	
	char ch;
	FILE *f;

	f=fopen("iofile.txt","w");
	printf("Enter data\n");

	while( (ch = getchar()) != EOF) {
    	putc(ch,f);
 	}

fclose(f);

return 0;
}