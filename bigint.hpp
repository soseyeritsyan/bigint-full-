#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
class bigint
{
	private:

	vector<unsigned char> dig;

	friend void del_zero ( vector<unsigned char> & v );
	friend void sys256 ( string & a , vector<unsigned char> & res );
	friend void to_bigint ( string & a , vector<unsigned char> & res );

	friend void plus_vec( vector<unsigned char> & v1 , vector<unsigned char> & v2 , vector<unsigned char> & res );
	friend void minus_vec( vector<unsigned char> & v1 , vector<unsigned char> & v2 , vector<unsigned char> & res );
	friend void mult_vec( vector<unsigned char> & v1 , vector<unsigned char> & v2 , vector<unsigned char> & res );

	friend bool is_zero(vector<unsigned char> & v );
        friend void unar_minus_vec( vector<unsigned char> & res );


	public:

	bigint();
	bigint( string & s );
	bigint( vector<unsigned char> & v);
	void print()
	{
		for ( int i = 0; i < dig.size() ; i++ ) {
			printf("%d",dig[i]);
                        cout<<" ";
		}
		cout<<endl;
	}
//	~bigint();
	friend bigint operator+( bigint & ths , bigint & oth );
	friend bigint operator-( bigint & ths , bigint & oth );
	friend bigint operator*( bigint & ths , bigint & oth );
	friend bigint operator/( bigint & ths , bigint & oth );
	friend bigint operator%( bigint & ths , bigint & oth );

	friend bool operator<( bigint & ths , bigint & oth );
	friend bool operator>( bigint & ths , bigint & oth );
	friend bool operator==( bigint & ths , bigint & oth );
	friend bool operator>=( bigint & ths , bigint & oth );
	friend bool operator<=( bigint & ths , bigint& oth );
	friend bool operator!=( bigint & ths , bigint & oth );

	friend bigint operator-( bigint & oth );// const;

	friend void operator+=( bigint & ths , bigint& oth );//
	friend void operator-=( bigint & ths , bigint& oth );
	friend void operator*=( bigint & ths , bigint& oth );
	friend void operator/=( bigint & ths , bigint& oth );
	friend void operator%=( bigint & ths , bigint& oth );

        friend ostream & operator<<(ostream & out, bigint & b);
	friend istream & operator>> ( istream & in , bigint & b );
        friend bigint & operator++( bigint & ths );
        friend bigint operator++( bigint & ths , int );
        friend bigint & operator--( bigint & ths );
        friend bigint operator--( bigint & ths , int );
};
