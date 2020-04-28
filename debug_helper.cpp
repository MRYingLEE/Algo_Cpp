//=============================================================
//          Begin of Debug section
//=============================================================


#define DEBUG



#ifdef DEBUG
#include <typeinfo>       // operator typeid
// C++ program to demonstrate working of 
// constants in climits. 
#include <climits> 
#include <iostream> 
  
using namespace std; 
 
void print_type_info(){
   
   cout<<endl;
   
   cout<<"SIZE of  <Machine Dependent>: "<<endl;
   cout<<endl;
   
   cout << "Size of char : " << sizeof(char) << endl;
   cout << "Size of int : " << sizeof(int) << endl;
   cout << "Size of short int : " << sizeof(short int) << endl;
   
   cout << "Size of long int : " << sizeof(long int) << endl;
   cout << "Size of long long : " << sizeof(long long) << endl;
   cout << "Size of float : " << sizeof(float) << endl;
   cout << "Size of double : " << sizeof(double) << endl;
   cout << "Size of wchar_t : " << sizeof(wchar_t) << endl;
   
   cout<<endl;
   
   cout<<"Limits <Machine Dependent>: "<<endl;
   cout<<endl;
    
    cout << "CHAR_MIN : " << CHAR_MIN << endl; 
    cout << "CHAR_MAX : " << CHAR_MAX << endl; 
    cout << "SHRT_MIN : " << SHRT_MIN << endl; 
    cout << "SHRT_MAX : " << SHRT_MAX << endl; 
    cout << "USHRT_MAX : " << USHRT_MAX << endl; 
    cout << "INT_MIN : " << INT_MIN << endl; 
    cout << "INT_MAX : " << INT_MAX << endl; 
    cout << "UINT_MAX : " << UINT_MAX << endl; 
    cout << "LONG_MIN : " << LONG_MIN << endl; 
    cout << "LONG_MAX : " << LONG_MAX << endl; 
    cout << "ULONG_MAX : " << ULONG_MAX << endl; 
    cout << "LLONG_MIN : " << LLONG_MIN << endl; 
    cout << "LLONG_MAX : " << LLONG_MAX << endl; 
    cout << "ULLONG_MAX : " << ULLONG_MAX << endl; 
  
}
#endif

#ifdef DEBUG
#define env_info() { print_type_info(); }
#else
#define env_info() 
#endif


#ifdef DEBUG
#define Debug(x) {std::cout <<"Line("<< __LINE__<<")--"<<#x <<"["<< typeid(x).name() << "] = " << x << endl;}
#define D(x)  {std::cout <<"Line("<< __LINE__<<")--"<<#x <<"["<< typeid(x).name() << "] = " << x << endl;}
#define d(x)  {std::cout <<"Line("<< __LINE__<<")--"<<#x <<"["<< typeid(x).name() << "] = " << x << endl;}
#else
#define Debug(x) 
#define D(x) 
#define d(x) 
#endif

#ifdef DEBUG
// C++ program to print vector objects 
// by overloading "<<" operator 
#include <iostream> 
#include <vector> 
#include <set> 
#include <map> 
#include <unordered_set> 
#include <unordered_map>
#include <array> 

using namespace std;

// C++ template to print vector container elements 
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "[";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]"<<endl;
	return os;
}

// C++ template to print array container elements 
template <typename T,  std::size_t N >
ostream& operator<<(ostream& os, const array<T,N>& v)
{
	os << "[";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]"<<endl;
	return os;
}


// C++ program to print set elements 
// by overloading "<<" operator 

// C++ template to print set container elements 
template <typename T>
ostream& operator<<(ostream& os, const set<T>& v)
{
	os << "[";
	for (auto it : v) {
		os << it;
		if (it != *v.rbegin())
			os << ", ";
	}
	os << "]" << endl;
	return os;
}

// C++ template to print unordered_map container elements 
template <typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& v)
{
	os << "[";
	for (auto it : v) {
		os << it;
		if (it != *v.rbegin())
			os << ", ";
	}
	os << "]" << endl;
	return os;
}


// C++ program to print map elements 
// by overloading "<<" operator 

// C++ template to print map container elements 
template <typename T, typename S>
ostream& operator<<(ostream& os, const map<T, S>& v)
{
	os << "{";
	for (auto it : v) {
		os << it.first << " : "
			<< it.second;

		if (it != *v.rbegin())
			os << ", ";
	}
	os << "}" << endl;
	return os;
}

// C++ program to print unordered_map elements 
// by overloading "<<" operator 

// C++ template to print unordered_map container elements 
template <typename T, typename S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	os << "{";
	for (auto it : v) {
		os << it.first << " : "
			<< it.second;

		if (it != *v.rbegin())
			os << ", ";
	}
	os << "}" << endl;
	return os;
}

// C++ program to print pair<> class 
// by overloading "<<" operator 

// C++ template to print pair<> 
// class by using template 
template <typename T, typename S>
ostream& operator<<(ostream& os, const pair<T, S>& v)
{
	os << "(";
	os << v.first << ", "
		<< v.second << ")" << endl;
	return os;
}


#endif

//=============================================================
//          End of Debug section
//=============================================================


// Driver code 
int vectortest()
{
	vector<int> vec{ 4, 2, 17, 11, 15 };

	// Printing the elements directly 
	//cout << vec;
	d(vec);
	return 0;
}

// Driver code 
int settest()
{
	set<int> st{ 4, 2, 17, 11, 15 };
	//cout << st;
	d(st);
	return 0;
}

// Driver code 
int maptest()
{
	map<char, int> mp;
	mp['b'] = 3;
	mp['d'] = 5;
	mp['a'] = 2;

	//cout << mp;
	d(mp);

	return 0;
}

// Driver code 
int pairtest()
{
	pair<int, int> pi{ 45, 7 };
	//cout << pi;
	d(pi);
	return 0;
}


int main() {
	vectortest();
	settest();
	maptest();
	pairtest();
	
	env_info();

	return 0;
}


