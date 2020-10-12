#pragma once
#include <vector>
#include <iterator>
template<typename T, typename = void>
class merge_range;

//template <typename Iter>
//constexpr bool is_random_access_iter_v = std::is_base_of_v<std::random_access_iterator_tag, std::iterator_traits<Iter>::iterator_category>;

template<typename Iterator>
class merge_iterator;
template<typename T>

class merge_range<T> final
{
public:
	using value_type = typename std::iterator_traits<T>::value_type;
	merge_range(const std::vector<std::pair<T, T>>& vector_of_pairs_of_iterators)
	{
		pair_container = vector_of_pairs_of_iterators;
		for (size_t i = 0; i < pair_container.size(); ++i)
		{
			size_ += std::distance(pair_container[i].first, pair_container[i].second);
			container_of_begin_iterators.push_back(pair_container[i].first);
		}
	}
	merge_iterator<T> begin()
	{
		auto begin = iterator;
		if (iterator.iterator_container.size() != 0)
		{
			begin.position = 0;
			return begin;
		}
		begin++;
		return begin;
	}
	merge_iterator<T> end()
	{
		auto end = iterator;
		for (int i = end.position; i < static_cast<int>(size_); ++i) {
			end++;
		}
		return end;
	}
	size_t size() const
	{
		return size_;
	}
private:
	merge_iterator<T> iterator = merge_iterator<T>::merge_iterator(*this);
	std::vector<std::pair<T, T>>  pair_container;
	std::vector<T> container_of_begin_iterators;
	size_t size_ = 0;
	friend class merge_iterator<T>;
};

template<typename Iterator>
class merge_iterator final
{
public:
	merge_iterator(merge_range<Iterator>& new_parent)
	{
		parent = &new_parent;
		iterator_position = &new_parent.container_of_begin_iterators;
	}
	merge_iterator& operator*(const merge_iterator&)
	{
		return this;
	}
	merge_iterator operator++(int) {
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
				if ((*iterator_position)[j] == parent->pair_container[j].second) {
					break;
				}
				if ((*iterator_position)[i] == parent->pair_container[i].second) {
					continue;
				}
				if (*(*iterator_position)[i] < *(*iterator_position)[j]) {
					if (not_first_iteration) {
						if (*it > * (*iterator_position)[i]) {
							it = (*iterator_position)[i];
							elem_founded = true;
							k = i;
						}
					}
					else {
						it = (*iterator_position)[i];
						elem_founded = true;
						k = i;
					}
					not_first_iteration = true;
				}
				else {
					if (not_first_iteration) {
						if (*it > * (*iterator_position)[j]) {
							it = (*iterator_position)[j];
							elem_founded = true;
							k = j;
						}
					}
					else {
						it = (*iterator_position)[j];
						elem_founded = true;
						k = j;
					}
					not_first_iteration = true;
				}
			}
			if (elem_founded == true) {
				(*iterator_position)[k]++;
				++position;
				iterator_container.push_back(it);
				return *this;
			}
			if ((*iterator_position)[j] == parent->pair_container[j].second) {
				++j;
			}
		}
		//unreacheble code
		return *this;
	}
	merge_iterator operator--(int)
	{
		if (position - 1 > -1)
		{
			--position;
			return *this;
		}
	}
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
	const merge_range<Iterator>* parent;
	std::vector<Iterator>* iterator_position;
	std::vector<Iterator> iterator_container;
	int position = -1;
	friend class merge_range<Iterator>;
};
