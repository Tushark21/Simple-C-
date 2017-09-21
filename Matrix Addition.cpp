#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a[10][10],b[10][10],res[10][10],m,n;

	cout<<"Enter Number of Rows(<11) of Matrices\n";
	cin>>n;

	cout<<"Enter Number of Columns(<11) of First Matrices\n";
	cin>>m;

	//Input First Matrix
	cout<<"Enter Elements of First Matrix\n";

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<"Enter "<<i+1<<" "<<j+1<<" Element: ";
			cin>>a[i][j];
		}
	}


	//Input Second Matrix
	cout<<"Enter Elements of Second Matrix\n";
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<"Enter "<<i+1<<" "<<j+1<<" Element: ";
			cin>>b[i][j];
		}
	}

	//Adding the Matrices and Printing Resultant Matrix
	cout<<"Resultant Matrix:\n";
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			res[i][j]=a[i][j]+b[i][j];
			cout<<res[i][j]<<",";
		}
		cout<<"\n";
	}	

	getch();
	return 0;
}