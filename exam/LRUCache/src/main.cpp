#include "LRUCache.h"
#include <functional>
#include <iostream>

int main()
{
	LRUCache<int, std::string> cache(2); // Емкость 2

	// Put
	cache.Put(1, "one");
	cache.Put(2, "two");

	// Get
	std::string* value = cache.Get(1);
	if (value)
		std::cout << *value << "\n"; // "one"
	value = cache.Get(3); // nullptr

	// GetValueOrDefault
	value = cache.GetValueOrDefault(3, []() { return "three"; });
	if (value)
		std::cout << *value << "\n"; // "three"

	value = cache.Get(2); // Удален, так как LRU
	if (!value)
		std::cout << "Key 2 not found\n";
}