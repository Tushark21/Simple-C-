#include <iostream>

using namespace std;

int main(){
	
	char ch;
	FILE *f;

	f=fopen("iofile","w");
	printf("Enter data");

	while( (ch = getchar()) != EOF) {
    	putc(ch,f);
 	}

fclose(f);

return 0;
}