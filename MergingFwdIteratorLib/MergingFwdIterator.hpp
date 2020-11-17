#pragma once
#include <vector>
#include <iterator>
#include "OutOfRangeException.h"

template<typename T, typename = void>
class Merge_range;

template<typename Iterator>
class Merge_iterator;

template<typename Iterator_type>
class Merge_range<Iterator_type> final
{
public:
	using value_type = typename std::iterator_traits<Iterator_type>::value_type;
	explicit Merge_range(const std::vector<std::pair<Iterator_type, Iterator_type>>& vector_of_pairs_of_iterators) : pair_container(vector_of_pairs_of_iterators)
	{
		for (size_t i = 0; i < pair_container.size(); ++i)
		{
			iterator.iterator_position.push_back(pair_container[i].first);
		}
	}

	Merge_iterator<Iterator_type> begin()
	{
		if (iterator.iterator_container.size() != 0)
		{
			iterator.position = 0;
			return iterator;
		}
		return ++iterator;
	}

	Merge_iterator<Iterator_type> end() const
	{
		return end_iterator_;
	}

private:
	std::vector<std::pair<Iterator_type, Iterator_type>>  pair_container;
	Merge_iterator<Iterator_type> iterator = Merge_iterator<Iterator_type>::Merge_iterator(this);
	friend class Merge_iterator<Iterator_type>;
	const Merge_iterator<Iterator_type> end_iterator_ = Merge_iterator<Iterator_type>::Merge_iterator(this);
};


template<typename Iterator>
class Merge_iterator final
{
public:
	explicit Merge_iterator(Merge_range<Iterator>* new_parent) : parent(*new_parent) {}

	Merge_iterator operator++() {
		Iterator desired_iterator;
		if (position + 1 < static_cast<int>(iterator_container.size()) && position != -1)
		{
			++position;
			return *this;
		}
		for (size_t j = 0; j != parent.pair_container.size();)
		{
			size_t pos_counter = 0;
			auto not_first_iteration = false;
			auto iterator_founded = false;
			auto& [begin_j_container_iterator, end_j_container_iterator] = parent.pair_container[j];

			for (size_t i = 1; i < parent.pair_container.size(); ++i) {
				auto& [begin_i_container_iterator, end_i_container_iterator] = parent.pair_container[i];
				if (iterator_position[j] == end_j_container_iterator) {
					break;
				}
				if (iterator_position[i] == end_i_container_iterator) {
					continue;
				}
				if (value_compare((iterator_position)[j], (iterator_position)[i])) {
					assing_if_found(desired_iterator, pos_counter,
						not_first_iteration, iterator_founded, i);
				}
				else {
					assing_if_found(desired_iterator, pos_counter,
						not_first_iteration, iterator_founded, j);
				}
			}
			if (iterator_founded == true) {
				++iterator_position[pos_counter];
				++position;
				iterator_container.push_back(desired_iterator);
				return *this;
			}
			if ((iterator_position)[j] == parent.pair_container[j].second) {
				++j;
			}
		}
		position = -1;
		return *this;
	}

	Merge_iterator operator++(int)
	{
		Merge_iterator temp = *this;
		++* this;
		return temp;
	}

	Merge_iterator operator--()
	{
		if (position > 0)
		{
			--position;
		}
		if (position == -1 && iterator_container.size() > 0)
		{
			position = static_cast<int>(iterator_container.size()) - 1;
		}
		return *this;
	}

	Merge_iterator operator--(int)
	{
		Merge_iterator temp = *this;
		--* this;
		return temp;
	}

	Merge_iterator& operator=(const Merge_iterator iterator)
	{
		if (&this->parent == &iterator.parent)
		{
			this->position = iterator.position;
			this->iterator_position = iterator.iterator_position;
			this->iterator_container = iterator.iterator_container;
		}
		return *this;
	}
	bool operator==(const Merge_iterator& compared)
	{
		return &this->parent == &compared.parent && this->position == compared.position;
	}

	bool operator!=(const Merge_iterator& compared)
	{
		return &this->parent == &compared.parent && this->position != compared.position;
	}

	auto get(size_t _pos) const
	{
		if (_pos < iterator_container.size() && _pos >= 0) {
			return iterator_container[_pos];
		}
		throw OutOfRangeException();
	}

	auto get() const
	{
		if (position >= 0 && position < iterator_container.size()) {
			return iterator_container[position];
		}
		throw OutOfRangeException();
	}

private:
	void assing_if_found(Iterator& desired_iterator, size_t& pair_numb_pos, bool& not_first_iteration, bool& elem_founded, size_t pos_in_iter_pos)
	{
		if (not_first_iteration) {
			if (*desired_iterator > * (iterator_position)[pos_in_iter_pos]) {
				desired_iterator = iterator_position[pos_in_iter_pos];
				elem_founded = true;
				pair_numb_pos = pos_in_iter_pos;
			}
		}
		else {
			desired_iterator = iterator_position[pos_in_iter_pos];
			elem_founded = true;
			pair_numb_pos = pos_in_iter_pos;
		}
		not_first_iteration = true;
	}
	bool value_compare(Iterator first, Iterator second) const
	{
		return *first > * second;
	}
	Merge_range<Iterator>& parent;
	std::vector<Iterator> iterator_position;
	std::vector<Iterator> iterator_container;
	int position = -1;
	friend class Merge_range<Iterator>;
};