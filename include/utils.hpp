#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <functional>

using sf::Vector2f;
using std::hash;

struct Vector2fHash {
	inline size_t operator()(const Vector2f& pos) const {
		int x = hash<float>()(pos.x);
		int y = hash<float>()(pos.y) << 1;
		return x ^ y;
	}
};

#endif 
