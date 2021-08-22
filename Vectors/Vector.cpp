//TODO Merge string info arrays into a single structure
//TODO Automate generation of typeVectorConstructorArguments
//TODO add _mm_empty for mmx operation call
#include <sstream>
#include <string>
#include "Vector.h"

struct VectorHelpers
{
	//Vector ToString Functions
	//TODO Check if these can be merged, doubt it though given use of vector_{64, 128, 256}_, only works if GetInternal{64, 128, 256} can be merged as well
	template <typename T>
	static std::string ToString64i(const Vector<T, 64> vector)
	{
		std::stringstream sstr;
		T values[8 / sizeof(T)];
		std::memcpy(values, &vector.vector_64_, sizeof(values));

		for (T v : values)
		{
			sstr << static_cast<int>(v) << " ";
		}

		return sstr.str();
	}
	
	template <typename T>
	static std::string ToString128i(const Vector<T, 128> vector)
	{
		std::stringstream sstr;
		T values[16 / sizeof(T)];
		std::memcpy(values, &vector.vector_128_, sizeof(values));

		for (T v : values)
		{
			sstr << v << " ";
		}

		return sstr.str();
	}

	template <typename T>
	static std::string ToString256i(const Vector<T, 256> vector) 
	{
		std::stringstream sstr;
		T values[32 / sizeof(T)];
		std::memcpy(values, &vector.vector_256_, sizeof(values));

		for (T v : values)
		{
			sstr << v << " ";
		}

		return sstr.str();
	}

	//TODO Generate automatically?
	template <typename T>
	static __m128i GetInternal128i(const Vector<T, 128> vector)
	{
		return vector.vector_128_;
	}

	template <typename T>
	static __m256i GetInternal256i(const Vector<T, 256> vector)
	{
		return vector.vector_256_;
	}

	template <typename T>
	static Vector<T, 128> GetVector128i(const __m128i vector)
	{
		return vector;
	}

	template <typename T>
	static Vector<T, 256> GetVector256i(const __m256i vector)
	{
		return vector;
	}
};

#pragma region Vector<int8_t, 64>
// Constructors
template <>
Vector<int8_t, 64>::Vector(const int8_t value) : vector_64_(_mm_set1_pi8(value))
{
}

template <>
Vector<int8_t, 64>::Vector(const std::array<int8_t, 8> values) : vector_64_(_mm_setr_pi8(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7]))
{
}

//TODO Fix for floating point types
std::ostream& operator<<(std::ostream& stream, const Vector<int8_t, 64>& vector)
{
	return stream << VectorHelpers::ToString64i(vector);
}

// Assignment Operators
template <>
Vector<int8_t, 64>& Vector<int8_t, 64>::operator+=(const Vector<int8_t, 64>& rhs)
{
	this->vector_64_ = _mm_add_pi8(this->vector_64_, rhs.vector_64_);
	_mm_empty();
	return *this;
}

// Comparision Operators
template <>
Vector<int8_t, 64> Vector<int8_t, 64>::operator>(const Vector<int8_t, 64>& vector2) const
{
	const auto result = _mm_cmpgt_pi8(this->vector_64_, vector2.vector_64_);
	_mm_empty();
	return result;
}
#pragma endregion

