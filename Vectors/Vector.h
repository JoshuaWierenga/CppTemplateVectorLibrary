//TODO Merge string info arrays into a single structure
//TODO Automate generation of typeVectorConstructorArguments
#ifndef VECTOR_H
#define VECTOR_H
#include <array>
#include <cstdint>
#include <intrin.h>
#include <type_traits>

template <typename T, uint_fast16_t X>
class Vector
{
	friend struct VectorHelpers;

	__m64 vector_64_{};
	//__m128i vector_128_{};
	//__m256i vector_256_{};

	//TODO Generate automatically?
	Vector(__m64 vector) : vector_64_(vector)
	{
	}
	
	/*Vector(__m128i vector) : vector_128_(vector)
	{
	}

	Vector(__m256i vector) : vector_256_(vector)
	{
	}*/

public:
	// Constructors
	Vector(T value);

	explicit Vector(std::array<T, X / (8 * sizeof(T))> values);

	template<class ...T2, std::enable_if_t<sizeof...(T2) == X / (8 * sizeof(T)) && std::conjunction_v<std::is_same<T, T2>...>, int> = 0>
	explicit Vector(T2... args) : Vector(std::array<T, sizeof...(T2)>{std::forward<T2>(args)...})
	{
	}

	// Assignment Operators
	Vector<T, X>& operator+=(const Vector<T, X>& rhs);

	// Comparision Operators
	Vector<T, X> operator>(const Vector<T, X>& vector2) const;
};

//TODO Move into struct?
#pragma region Vector<int8_t, 64>
// Constructors
template <> Vector<int8_t, 64>::Vector(int8_t value);
template <> Vector<int8_t, 64>::Vector(std::array<int8_t, 8> values);

std::ostream& operator<<(std::ostream& stream, const Vector<int8_t, 64>& vector);

//Vector<int8_t, 64> Blend(Vector<int8_t, 64> comparision, Vector<int8_t, 64> falseValue, Vector<int8_t, 64> trueValue);

// Assignment Operators
template <> Vector<int8_t, 64>& Vector<int8_t, 64>::operator+=(const Vector<int8_t, 64>& rhs);

// Comparision Operators
template <> Vector<int8_t, 64> Vector<int8_t, 64>::operator>(const Vector<int8_t, 64>& vector2) const;
#pragma endregion

#endif //VECTOR_H