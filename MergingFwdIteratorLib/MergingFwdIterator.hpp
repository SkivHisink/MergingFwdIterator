#pragma once
#include <vector>
#include <iterator>
template<typename T, typename = void>
class merge_range;

//template <typename Iter>
//constexpr bool is_random_access_iter_v = std::is_base_of_v<std::random_access_iterator_tag, std::iterator_traits<Iter>::iterator_category>;

template<typename Iterator>
class merge_iterator;

template<typename Iterator_type>
class merge_range<Iterator_type> final
{
public:
	using value_type = typename std::iterator_traits<Iterator_type>::value_type;
	merge_range(const std::vector<std::pair<Iterator_type, Iterator_type>>& vector_of_pairs_of_iterators)
	{
		pair_container = vector_of_pairs_of_iterators;
		for (size_t i = 0; i < pair_container.size(); ++i)
		{
			container_of_begin_iterators.push_back(pair_container[i].first);
		}
		iterator.iterator_position = container_of_begin_iterators;
	}
	merge_iterator<Iterator_type> begin()
	{
		auto begin = iterator;
		if (iterator.iterator_container.size() != 0)
		{
			return end();
		}
		++begin;
		return begin;
	}
	merge_iterator<Iterator_type> end()
	{
		return *merge_iterator<Iterator_type>::end;
	}
private:
	merge_iterator<Iterator_type> iterator = merge_iterator<Iterator_type>::merge_iterator(*this);
	std::vector<std::pair<Iterator_type, Iterator_type>>  pair_container;
	std::vector<Iterator_type> container_of_begin_iterators;
	friend class merge_iterator<Iterator_type>;
};

template<typename Iterator>
class merge_iterator final
{
public:
	merge_iterator(merge_range<Iterator>& new_parent)
	{
		parent = &new_parent;
	}
	merge_iterator& operator*(const merge_iterator&)
	{
		return this;
	}
	merge_iterator operator++() {
		Iterator it;
		if (position + 1 < static_cast<int>(iterator_container.size()))
		{
			++position;
			return *this;
		}
		for (size_t j = 0; j != parent->pair_container.size();)
		{
			auto k = 0;
			auto not_first_iteration = false;
			auto elem_founded = false;
			for (size_t i = 1; i < parent->pair_container.size(); ++i) {
				if (iterator_position[j] == parent->pair_container[j].second) {
					break;
				}
				if (iterator_position[i] == parent->pair_container[i].second) {
					continue;
				}
				if (*(iterator_position)[i] < *(iterator_position)[j]) {
					if (not_first_iteration) {
						if (*it > * (iterator_position)[i]) {
							it = (iterator_position)[i];
							elem_founded = true;
							k = i;
						}
					}
					else {
						it = (iterator_position)[i];
						elem_founded = true;
						k = i;
					}
					not_first_iteration = true;
				}
				else {
					if (not_first_iteration) {
						if (*it > * (iterator_position)[j]) {
							it = iterator_position[j];
							elem_founded = true;
							k = j;
						}
					}
					else {
						it = iterator_position[j];
						elem_founded = true;
						k = j;
					}
					not_first_iteration = true;
				}
			}
			if (elem_founded == true) {
				++iterator_position[k];
				++position;
				iterator_container.push_back(it);
				return *this;
			}
			if ((iterator_position)[j] == parent->pair_container[j].second) {
				++j;
			}
		}
		//unreacheble code
		return *this;
	}
	merge_iterator operator--()
	{
		if (position - 1 > -1)
		{
			--position;
			return *this;
		}
	}
	/*bool operator==(const merge_iterator& compared)
	{
		return this == compared;
	}
	bool operator!=(const merge_iterator& compared)
	{
		return !(this == compared);
	}*/
	int operator -(const merge_iterator& subtrahend)
	{
		return subtrahend.position - this->position;
	}
	auto get(size_t _pos)
	{
		if (_pos <= position) {
			return iterator_container[_pos];
		}
	}
	auto get()
	{
		return iterator_container[position];
	}
private:
	inline static const merge_iterator* end = nullptr;
	 merge_range<Iterator>* parent;
	std::vector<Iterator> iterator_position;
	std::vector<Iterator> iterator_container;
	int position = -1;
	friend class merge_range<Iterator>;
};
