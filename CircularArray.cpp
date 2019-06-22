// Example program
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <array>

using namespace std;

inline size_t modulo(const long long index, size_t size) {
	auto r = index % size;

	return size_t(r < 0 ? r + size : r);
}

template<class T, std::size_t N>
class circular_array : public array<T, N> {
public:
	T& operator[] (const long long index)
	{
		size_t new_index = modulo(index,   array<T, N>::size());

		return array<T,N>::at(new_index);
	}
};

// Powers of 2
//  0 = 1
//  1 = 2
//  2 = 4
//  3 = 8
//  4 = 16
//  5 = 32
//  6 = 64
//  7 = 128
//  8 = 256 
//  9 = 512
//  10 = 1, 024
//  11 = 2, 048
//  12 = 4, 096
//  13 = 8, 192
//  14 = 16, 384
//  15 = 32, 768
//  16 = 65, 536
//
//  32 = 4, 294, 967, 296
//
//  64 = 18, 446, 744, 073, 709, 500, 000

// You assigned the 
inline size_t modulo2(const long long index, unsigned short Exponent) {
	auto exp = ((long long) 1 << Exponent);
	auto r = index & (exp -1);

	return size_t(r);
}

template<class T, unsigned short Exponent>
class circular_array_exponent : public array<T, 1<< Exponent> {
public:
	T& operator[] (const long long index)
	{
		size_t new_index = modulo2(index, Exponent);

		return array<T, 1<< Exponent>::at(new_index);
	}
};

int main()
{
	cout << "============= modulo test ===========" << endl;

	for (int i = -5; i < 5; i++)
		cout << "modulo(" << i << ",8)=" << modulo(i,8) << endl;

	cout << "============= modulo test ===========" << endl;

	for (int i = -5; i < 5; i++)
		cout << "modulo2(" << i << ",3)=" << modulo2(i, 3) << endl;

	cout << "============= circular_array ===========" << endl;

	circular_array<int,8> a;
	
	for (int i = -5; i < 5; i++)
		a[i] = i;

	for (int i = -5; i < 5; i++)
		cout << "a[" << i << "]=" << a[i] << endl;

	cout << "============= circular_array2 ===========" << endl;

	circular_array_exponent<int, 3> a2; // The exponent is 3. 2^3=8!

	for (int i = -5; i < 5; i++)
		a2[i] = i;

	for (int i = -5; i < 5; i++)
		cout << "a[" << i << "]=" << a2[i] << endl;


	cout << "============= circular_array2 with enough space ===========" << endl;

	circular_array_exponent<int, 4> a3; // The exponent is 4. 2^4=16!

	for (int i = -5; i < 5; i++)
		a3[i] = i;

	for (int i = -5; i < 5; i++)
		cout << "a[" << i << "]=" << a3[i] << endl;
}

