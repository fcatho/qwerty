#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <cassert>


template<typename Key, typename Value>
struct HashItem
{
	Key key;
	Value value;
};


template<typename Key>
struct Hasher
{
	const std::size_t operator()(const Key & key, const std::size_t limit)
	{
		std::size_t hash = std::hash<Key>{}(key);
		return hash % limit;
	}
};


template<typename Key, typename Value>
class HashMap
{
public:
	typedef std::list<HashItem<Key, Value>> HashBucket;

	HashMap(const std::size_t size)
		: size_(size)
	{
		array_.resize(size_);
	}

	void insert(const Key & key, const Value & value)
	{
		auto index = Hasher<Key>{}(key, size_);
		array_[index].emplace_back(HashItem<Key, Value>{key, value});
	}

	//void remove(const Key & key);
	const Value * find(const Key & key)
	{
		auto index = Hasher<Key>{}(key, size_);
		auto & bucket = array_[index];
		auto found = std::find_if(bucket.begin(), bucket.end(), [&key](const auto & item) { return item.key == key; });
		if (found != bucket.end())
		{
			return &(found->value);
		}
		return nullptr;
	}

	const Value * operator[](const Key & key)
	{
		return find(key);
	}

private:
	std::size_t size_;
	std::vector<HashBucket> array_;
};


int main()
{
	HashMap<int, std::string> hash_map(100);
	hash_map.insert(10, "foo");
	hash_map.insert(20, "bar");
	hash_map.insert(30, "quz");

	//auto * found = hash_map.find(10);
	auto * found = hash_map[10];
	assert(found);
	assert(*found == "foo");

	return 0;
}
