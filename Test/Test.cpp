#include <iostream>
#include <array>
#include "Vector.h"

void test8_64()
{
	const std::array<signed char, 8> array{ 1, 2, 3, 4, 5, 6, 7, 8 };
	constexpr int value = -9, test = -3;

	Vector<signed char, 64> v_array(array);
	v_array += value;

	//TODO Add an array cast so that items can be printed individually and then lined up
	std::cout << "signed int8_t 64 bit test" << std::endl << v_array << std::endl << (v_array > test);
}

/*void simple128test()
{
	constexpr int array[4] = { 4, 7, -2, 9 };
	constexpr int value = 5, adjustment1 = 10, adjustment2 = 3;

	Vector<int32_t, 128> vArray(array[0], array[1], array[2], array[3]);

	vArray += Blend(vArray > value, adjustment2, adjustment1);

	std::cout << "simple 128 bit test:" << std::endl << vArray << std::endl << std::endl;
}

void simple256test()
{
	constexpr int array[8] = { 4, -2, 9, 7, 3, 2, 4, 6 };
	constexpr int value = 5, adjustment = 3;

	Vector<int, 256> vArray(array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7]);

	vArray += Blend(vArray > value, adjustment, 0);

	std::cout << "simple 256 bit test" << std::endl << vArray << std::endl << std::endl;
}*/

int main()
{
	test8_64();
	//simple128test();
	//simple256test();
}
