#include "bigint.hpp"
int main()
{
	bigint A;
	cout << "input A" << endl;
	cin >> A;

	bigint B;
	cout << "input B" << endl;
	cin >> B;

        cout << A << endl;
        cout << B << endl;

        if ( A > B )
                cout<<"A > B"<<endl;
        if ( A < B )
                cout<<"A < B"<<endl;
        if ( A == B )
                cout<<"A == B"<<endl;


	bigint C;
	C = A + B;
        cout << "A + B = " << C << endl;

	C = A - B;
        cout << "A - B = " << C << endl;

	C = A * B;
        cout << "A * B = " << C << endl;

	C = A / B;
        cout << "A / B = " << C << endl;
	return 0;
}
