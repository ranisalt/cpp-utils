#ifndef UTILS_TUPLEHASH_H
#define UTILS_TUPLEHASH_H

#include <tuple>

namespace std {

template<typename T>
inline void hash_combine(size_t& seed, const T& value)
{
	seed ^= hash<T>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename Tuple, size_t Index = tuple_size<Tuple>::value - 1>
struct TupleHash {
	static size_t hash(size_t& seed, const Tuple& tuple)
	{
		TupleHash<Tuple, Index - 1>::hash(seed, tuple);
		hash_combine(seed, get<Index>(tuple));
	}
};

template<typename Tuple>
struct TupleHash<Tuple, 0> {
	static size_t hash(size_t& seed, const Tuple& tuple)
	{
		hash_combine(seed, get<0>(tuple));
	}
};

template<typename... Types>
struct hash<tuple<Types...>> {
	using type = tuple<Types...>;

	size_t operator()(const type& tuple) const
	{
		size_t seed = 0;
		TupleHash<type>::hash(seed, tuple);
        return seed;
	}
};

}

#endif /* UTILS_TUPLEHASH_H */
