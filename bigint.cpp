#include "bigint.hpp"

void del_zero ( vector<unsigned char> & v )
{
        int i = 0;
        if ( v[i] == '-' ) {
                i++ ;
        }
        while ( v[i] == 0 ) {
                v.erase(v.begin() + i );
        }
}

void sys256 ( string & a , vector<unsigned char> & res )
{
        if ( a.size() > 3 || stoi(a) >= 256 ) {
		string r;
		string r1;
		int i = 3;
		int k = 0;
		char tmp1;
		int qn;
		int tmp = 0;
		r1.assign(a, 0, 3);
		k = stoi(r1);
		if( k < 256 ) {
			r1.assign(a, 0, 4);
			k = stoi(r1);
			i = 4;
		}
		qn = k / 256;
		tmp1 = qn + '0';
		r = r + tmp1;
		k =  k % 256;
		while ( i < a.size() ) {
			if ( k < 256 ) {
				tmp = a[i] - '0';
				k *= 10;
				k = k + tmp;
				i++;
				if ( k < 256 && i < a.size()) {
					tmp = a[i] - '0';
					k *= 10;
					k = k + tmp;
					r = r + '0';
					i++;
				}
			}
			qn = k / 256;
			tmp1 = qn + '0';
			r = r + tmp1;
			k =  k % 256;
		}
		res.push_back(k);
		sys256 ( r , res );
	}
        else {
                int k = stoi(a);
                res.push_back(k);
        }
}

void to_bigint ( string & a , vector<unsigned char> & res )
{
	bool sign_ = false;
	if ( a[0] == '-' ) {
		sign_ = true;
                cout << "minusov tiv" << endl;
		a.erase(a.begin());
	}
	sys256(a,res);
	reverse(res.begin(), res.end());
	if ( sign_ == true ) {
		res.insert(res.begin() , 0 );
	}

}

bigint::bigint()
{
	dig.clear();
}

bigint::bigint( string & s )
{
	to_bigint( s , dig );
        //sys256(s,dig);
        //reverse(dig.begin(),dig.end());
}

bigint::bigint( vector<unsigned char> & v )
{
	dig = v;
}

void minus_vec( vector<unsigned char> & v1 , vector<unsigned char> & v2 , vector<unsigned char> & res )
{
        int c = 0;
        int k ;
        for ( int i = v1.size() - 1 , j = v2.size() - 1;  ; i-- , j-- ) {
                if ( i >= 0 && j >= 0) {
                        if ( (int)(v1[i]) >= (int)(v2[j]) ) {
                                        k = (int)(v1[i]) - (int)(v2[j]) - c ;
                                        c = 0;
                        }
                        else {
                                k = (int)(v1[i]) - (int)(v2[j]) - c + 256 ;
                                c = 1;
                        }
                }
                if ( i >= 0 && j < 0 ) {
                        k = (int)(v1[i]) - c ;
                        c = 0;
                }
                if ( i < 0 && j < 0 ) {
                        break;
                }
                res.push_back(k);
        }
        reverse(res.begin(), res.end());
        del_zero(res);
}
void mult_vec( vector<unsigned char> & v1 , vector<unsigned char> & v2 , vector<unsigned char> & res )
{
        for ( int i = 0 ; i < v1.size() + v2.size() ; i++ ) {
                res.push_back(0);
        }
        int carry;
        for ( int i = v2.size() - 1 ; i >= 0 ; --i ) {
                for ( int j = v1.size() - 1 ; j >= 0 ; j-- ) {
                        int k = (int)(res[ i + j + 1 ]) + (int)(v1[j])*(int)(v2[i]);
                        res[ i + j + 1 ] = k % 256 ;
                        carry = k / 256;
                        res[ i + j ] += carry;
                }
        }
        del_zero(res);
}
bool is_zero(vector<unsigned char> & v )
{
        if ( v.size() == 0 && v[0] == 0 ) {
                return true;
        }
        else {
                return false;
        }
}

void unar_minus_vec( vector<unsigned char> & res )
{
        if ( res[0] == 0 ) {
                res.erase(res.begin());
        }
        else {
                res.insert( res.begin() , 0 );
        }
}

void plus_vec( vector<unsigned char> & v1 , vector<unsigned char> & v2 , vector<unsigned char> & res )
{
        int c = 0;
        int k ;
        for ( int i = v1.size() - 1 , j = v2.size() - 1; i >= 0 , j >= 0  ; i-- , j-- ) {
                if ( i >= 0 && j >= 0) {
                        k = (int)(v1[i]) + (int)(v2[j]) + c ;
                        if ( k >= 256 ) {
                                k = k - 256;
                                c = 1;
                        }
                        else {
                                c = 0;
                        }
                }
                if ( i >= 0 && j < 0 ) {
                        k = (int)(v1[i]) + c ;
                        if ( k >= 256 ) {
                                k = k - 256;
                                c = 1;
                        }
                        else {
                                c = 0;
                        }
                }
                res.push_back(k);
        }
        reverse(res.begin(), res.end());
}

bigint operator+( bigint & ths , bigint & oth ) //gumarum
{
        vector<unsigned char> r;
        if ( is_zero( ths.dig ) ) {
                return oth;
        }
        else if ( is_zero(oth.dig) ) {
                return ths;
        }
        else if ( ths.dig[0] == 0 && oth.dig[0] != 0 ) {
                vector<unsigned char> a = ths.dig;
                vector<unsigned char> b = oth.dig;
                unar_minus_vec(a);
                minus_vec( b , a , r );
                return bigint(r);
        }
        else if ( ths.dig[0] != 0 && oth.dig[0] == 0 ) {
                vector<unsigned char> a = ths.dig;
                vector<unsigned char> b = oth.dig;
                b.erase(b.begin());
                minus_vec( a , b , r );
                return bigint(r);
        }
        else if ( ths.dig[0] == 0 && oth.dig[0] == 0 ) {
                vector<unsigned char> a = ths.dig;
                vector<unsigned char> b = oth.dig;
                a.erase(a.begin());
                b.erase(b.begin());
                plus_vec( a , b , r );
                unar_minus_vec(r);
                return bigint(r);
        }
        else if ( ths.dig[0] != 0 && oth.dig[0] != 0 ) {
                plus_vec( ths.dig, oth.dig, r );
                return  bigint(r);
        }

}

bigint operator-( bigint & ths , bigint & oth )//hanum
{
        vector<unsigned char> r;
        if ( ths == oth ) {
                string s = "0";
                return bigint(s);
        }
        else if ( is_zero(ths.dig) ) {
                r = oth.dig ;
                unar_minus_vec(r);
                return bigint(r);
        }
        else if ( is_zero(oth.dig)) {
                r = ths.dig;
                return bigint(r);
        }
        else if ( ths.dig[0] == 0 && oth.dig[0] != 0 ) {
                vector<unsigned char> a = ths.dig;
                vector<unsigned char> b = oth.dig;
                a.erase(a.begin());
                plus_vec( a , b , r );
                unar_minus_vec(r);
                return bigint(r);
        }
        else if ( ths.dig[0] != 0 && oth.dig[0] == 0 ) {
                vector<unsigned char> a = ths.dig;
                vector<unsigned char> b = oth.dig;
                b.erase(b.begin());
                plus_vec( a , b , r );
                return bigint(r);
        }
        else if ( ths.dig[0] == 0 && oth.dig[0] == 0 ) {
                vector<unsigned char> a = ths.dig;
                vector<unsigned char> b = oth.dig;
                a.erase(a.begin());
                b.erase(b.begin());
                if ( ths > oth ) {
                        minus_vec( b , a , r );
                        return bigint(r);
                }
                else {
                        minus_vec( a , b , r );
                        unar_minus_vec(r);
                        return bigint(r);
                }
        }
        else if ( ths.dig[0] != 0 && oth.dig[0] != 0 && ths < oth ) {
                bigint cc = oth - ths;
                minus_vec( oth.dig , ths.dig , r );
                unar_minus_vec(r);
                return bigint(r);
        }
        else if ( ths.dig[0] != 0 && oth.dig[0] != 0 && ths > oth ) {
                minus_vec( ths.dig , oth.dig , r );
                return bigint(r);
        }
}

bigint operator*( bigint & ths , bigint& oth )
{
        vector<unsigned char> r;
        if ( is_zero(ths.dig) || is_zero(oth.dig) ) {
                string s = "0";
                return bigint(s);
        }
        else if ( ths.dig.size() == 1 && ths.dig[0] == 1 ) {
                return bigint(oth.dig);
        }
        else if ( oth.dig.size() == 1 && oth.dig[0] == 1 ) {
                return bigint(ths.dig);
        }
        vector<unsigned char> a = ths.dig;
        vector<unsigned char> b = oth.dig;
        bool sign_;// true if -
        if ( a[0] == 0 && b[0] != 0 ){
                a.erase(a.begin());
                sign_ = true;
        }
        else if ( a[0] != 0 && b[0] == 0 ) {
                b.erase(b.begin());
                sign_ = true;
        }
        else if ( a[0] == 0 && b[0] == 0 ) {
                a.erase(a.begin());
                b.erase(b.begin());
                sign_ = false;
        }
        mult_vec( a , b , r );
        if( sign_ ) {
                unar_minus_vec(r);
        }
        return bigint(r);
}
bigint operator/( bigint & ths , bigint& oth )//bajanum
{
        if ( ths < oth ) {
                string s = "0";
                return bigint(s);
        }
        if ( ths == oth ) {
                string s = "1";
                return bigint(s);
        }
        if ( oth.dig.size() == 1 && oth.dig[0] == 1 ) {
                return bigint(ths.dig);
        }
        vector<unsigned char> r;
        bigint a = ths;
        bigint b = oth;
        bool sign_;// true if -
        if ( a.dig[0] == 0 && b.dig[0] != 0 ){
                a.dig.erase(a.dig.begin());
                sign_ = true;
        }
        if ( a.dig[0] != 0 && b.dig[0] == 0 ) {
                b.dig.erase(b.dig.begin());
                sign_ = true;
        }
        if ( a.dig[0] == 0 && b.dig[0] == 0 ) {
                a.dig.erase(a.dig.begin());
                b.dig.erase(b.dig.begin());
                sign_ = false;
        }
        while ( b.dig.size() < a.dig.size() ) {
                b.dig.push_back(0);
        }
                for(;;) {
                        int count = 0;
                        while ( a >= b ) {
                                a = a - b ;
                                ++count;
                        }
                        r.push_back(count);
                        if ( b.dig.size() <= oth.dig.size() ) {
                                break;
                        }
                        b.dig.pop_back();
                }
        del_zero(r);
        if ( sign_ ) {
                r.insert( r.begin(), 0 );
        }
        return bigint(r);
}

bigint operator%( bigint & ths , bigint & oth )
{
        bigint r;
        r = ths / oth;
        r = ths - r;
        return bigint(r);
}
bigint operator-( bigint & oth )
{
        bigint r;
        r = oth;
        unar_minus_vec(r.dig);
        return bigint(r.dig);
}
void operator+=( bigint & ths , bigint & oth )
{
        ths = ths + oth;
}

void operator-=( bigint & ths , bigint & oth )
{
        ths = ths - oth;
}

void operator*=( bigint & ths , bigint& oth )
{
        ths = ths * oth;
}

void operator/=( bigint & ths , bigint & oth )
{
        ths = ths / oth;
}
void operator%=( bigint & ths , bigint & oth )
{
        ths = ths % oth;
}

bool operator<( bigint & ths , bigint & oth )
{
        if ( ths.dig[0] == 0 && oth.dig[0] == 0 ) {
                bigint a = ths;
                bigint b = oth;
                a.dig.erase(a.dig.begin());
                b.dig.erase(b.dig.begin());
                return a > b ;
        }
        if ( ths.dig[0] == 0 && oth.dig[0] != 0 ) {
                return true;
        }
        if ( ths.dig[0] != 0 && oth.dig[0] == 0 ) {
                return false;
        }
        if ( ths.dig.size() < oth.dig.size() ) {
                return true;
        }
        if ( ths.dig.size() > oth.dig.size() ) {
                return false;
        }
        if ( ths.dig.size() == oth.dig.size() ) {
                int i = 0;
                for ( i = 0 ; i < ths.dig.size(); i++ ) {
                        if( (int)(ths.dig[i]) > (int)(oth.dig[i]) ) {
                                return false;
                        }
                        if( (int)(ths.dig[i]) < (int)(oth.dig[i]) ) {
                                return true;
                        }
                }
        }
}

bool operator>( bigint & ths , bigint & oth )
{
        if ( ths.dig[0] == 0 && oth.dig[0] == 0 ) {
                bigint a = ths;
                bigint b = oth;
                a.dig.erase(a.dig.begin());
                b.dig.erase(b.dig.begin());
                return a < b ;
        }
        if ( ths.dig[0] == 0 && oth.dig[0] != 0 ) {
                return false;
        }
        if ( ths.dig[0] != 0 && oth.dig[0] == 0 ) {
                return true;
        }
        if ( ths.dig.size() > oth.dig.size() ) {
                return true;
        }
        if ( ths.dig.size() < oth.dig.size() ) {
                return false;
        }
        if ( ths.dig.size() == oth.dig.size() ) {
                int i = 0;
                for ( i = 0 ; i < ths.dig.size(); i++ ) {
                        if( (int)(ths.dig[i]) < (int)(oth.dig[i]) ) {
                                return false;
                        }
                        if ( (int)(ths.dig[i]) > (int)(oth.dig[i]) ) {
                                return true;
                        }
                }
        }
}

bool operator==( bigint & ths , bigint & oth )
{
        if ( ths.dig.size() != oth.dig.size() ) {
                return false;
        }
        else {
                for ( int i = 0 ; i < ths.dig.size() ; i++ ) {
                        if ( (int)(ths.dig[i]) != (int)(oth.dig[i]) ) {
                                return false;
                        }
                }
                return true;
        }
}

bool operator>=( bigint & ths , bigint & oth )
{
        if ( ths > oth || ths == oth ) {
                return true;
        }
        else {
                return false;
        }
}

bool operator<=( bigint & ths , bigint& oth )
{
        if ( ths < oth || ths == oth ) {
                return true;
        }
        else {
                return false;
        }
}

bool operator!=( bigint & ths , bigint & oth )
{
        if ( ths == oth ) {
                return false;
        }
        else {
                return true;
        }
}

ostream & operator<<( ostream & out , bigint & b )
{
        int c;
        for( int i = 0; i < b.dig.size(); i++ ) {
                c = b.dig[i];
                out << c << " ";
        }
        return out ;
}

istream & operator>> ( istream & in , bigint & b )
{
}
 /*       string str;
        cin >> str;
*/
bigint & operator++( bigint & ths )
{
        string s = "1";
        bigint a(s);
        ths = ths + a;
        return ths;
}
bigint operator++( bigint & ths , int )
{
        bigint tmp = ths;
        ++ths;
        return tmp;
}
bigint & operator--( bigint & ths )
{
        string s = "1";
        bigint a(s);
        ths = ths - a;
        return ths;
}
bigint operator--( bigint & ths , int )
{
        bigint tmp = ths;
        --ths;
        return tmp;
}

