#include "bigint.hpp"
int main()
{
	string a;
	cout << "input a"<<endl;
	cin >> a;
	bigint A(a);

	string b;
	cout << "input b"<<endl;
	cin >> b;
	bigint B(b);
	A.print();
	B.print();
        if ( A > B )
                cout<<"A > B"<<endl;
        if ( A < B )
                cout<<"A < B"<<endl;
        if ( A == B )
                cout<<"A == B"<<endl;

	bigint C;
	C = A + B;
        cout << "A + B = ";
	C.print();

	C = A - B;
        cout << "A - B = ";
	C.print();

	C = A * B;
        cout << "A * B = ";
	C.print();

	C = A / B;
        cout << "A / B = ";
	C.print();
	return 0;
}
