#include "../src/LRUCache.h"
#include <gtest/gtest.h>

TEST(LRUCache, TestConstructors)
{
	LRUCache<int, std::string> cache(2);
	cache.Put(1, "hello");
	cache.Put(2, "there!");

	LRUCache cache2(cache);
	EXPECT_EQ(*cache2.Get(1), "hello");
	EXPECT_EQ(*cache2.Get(2), "there!");
	cache2.Put(3, "my dear");
	cache2.Put(4, "user");

	EXPECT_EQ(*cache2.Get(3), "my dear");
	EXPECT_EQ(*cache2.Get(4), "user");

	LRUCache cache3 = std::move(cache);
	EXPECT_EQ(*cache3.Get(1), "hello");
	EXPECT_EQ(*cache3.Get(2), "there!");

	LRUCache cache4 = cache2;
	EXPECT_EQ(*cache4.Get(3), "my dear");
	EXPECT_EQ(*cache4.Get(4), "user");

	LRUCache<int, std::string> cacheWithInvalidCapacity(-1);
}

TEST(LRUCache, TestOperations)
{
	LRUCache<int, std::string> cache(2);
	cache.Put(1, "hello");
	cache.Put(2, "there!");

	const auto item1 = cache.Get(1);
	const auto item2 = cache.Get(2);
	EXPECT_EQ(*item1, "hello");
	EXPECT_EQ(*item2, "there!");
	EXPECT_EQ(cache.Get(5), nullptr);

	cache.Put(3, "my dear");
	EXPECT_EQ(cache.Get(1), nullptr);

	const auto item3 = cache.GetValueOrDefault(7, []() {
		return "default value";
	});
	EXPECT_EQ(*item3, "default value");
	EXPECT_EQ(*cache.GetValueOrDefault(3, []() {
		return "default value";
	}),
		"my dear");
}