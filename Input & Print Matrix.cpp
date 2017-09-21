#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a[10][10],m,n;
	cout<<"Enter Number of Rows(<11)\n";
	cin>>n;

	cout<<"Enter Number of Columns(<11)\n";
	cin>>m;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<"Enter "<<i+1<<" "<<j+1<<" Element: ";
			cin>>a[i][j];
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<a[i][j]<<",";
		}
		cout<<"\n";
	}

	getch();
	return 0;
}