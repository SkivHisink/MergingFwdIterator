#pragma once
#include <iostream>
#include <vector>
#include <iterator>
template<typename T, typename = void>
class Merge_range;

//template <typename Iter>
//constexpr bool is_random_access_iter_v = std::is_base_of_v<std::random_access_iterator_tag, std::iterator_traits<Iter>::iterator_category>;

template<typename Iterator>
class Merge_iterator;

template<typename Iterator_type>
class Merge_range<Iterator_type> final
{
public:
	using value_type = typename std::iterator_traits<Iterator_type>::value_type;
	Merge_range(const std::vector<std::pair<Iterator_type, Iterator_type>>& vector_of_pairs_of_iterators)
	{
		pair_container = vector_of_pairs_of_iterators;
		for (size_t i = 0; i < pair_container.size(); ++i)
		{
			container_of_begin_iterators.push_back(pair_container[i].first);
		}
		iterator.iterator_position = container_of_begin_iterators;
	}
	Merge_iterator<Iterator_type> begin()
	{
		auto begin = iterator;
		if (iterator.iterator_container.size() != 0)
		{
			return end();
		}
		++begin;
		return begin;
	}
	Merge_iterator<Iterator_type> end()
	{
		return end_iterator_;
	}
private:
	Merge_iterator<Iterator_type> iterator = Merge_iterator<Iterator_type>::Merge_iterator(*this);
	std::vector<std::pair<Iterator_type, Iterator_type>>  pair_container;
	std::vector<Iterator_type> container_of_begin_iterators;
	friend class Merge_iterator<Iterator_type>;
	const Merge_iterator<Iterator_type> end_iterator_ = Merge_iterator<Iterator_type>::Merge_iterator(*this, true);
};
class OutOfRangeException final :std::exception
{
	const char* m_error = "Out of range position was sent in function";
public:
	OutOfRangeException() {}
	const char* what() noexcept { return m_error; }
};
template<typename Iterator>
class Merge_iterator final
{
public:

	Merge_iterator(Merge_range<Iterator>& new_parent)
	{
		parent = &new_parent;
	}
	Merge_iterator& operator*(const Merge_iterator&)
	{
		return this;
	}
	bool value_compare(Iterator first, Iterator second)
	{
		return *first > * second;
	}

	Merge_iterator operator++() {
		Iterator it;
		if (position + 1 < static_cast<int>(iterator_container.size()) && position != -2)
		{
			++position;
			return *this;
		}
		for (size_t j = 0; j != parent->pair_container.size();)
		{
			size_t k = 0;
			auto not_first_iteration = false;
			auto elem_founded = false;
			for (size_t i = 1; i < parent->pair_container.size(); ++i) {
				if (iterator_position[j] == parent->pair_container[j].second) {
					break;
				}
				if (iterator_position[i] == parent->pair_container[i].second) {
					continue;
				}
				if (value_compare((iterator_position)[j], (iterator_position)[i])) {
					assing_if_found(it, k, not_first_iteration, elem_founded, i);
				}
				else {
					assing_if_found(it, k, not_first_iteration, elem_founded, j);
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
		position = -2;
		return *this;
	}

	Merge_iterator operator--()
	{
		if (position - 1 > -1)
		{
			--position;
		}
		if (position == -2 && iterator_container.size() > 0)
		{
			position = static_cast<int>(iterator_container.size()) - 1;
		}
		return *this;
	}

	bool operator==(const Merge_iterator& compared)
	{
		return this->parent == compared.parent && this->position == compared.position;
	}

	bool operator!=(const Merge_iterator& compared)
	{
		return this->parent == compared.parent && this->position != compared.position;
	}

	auto get(size_t _pos)
	{
		if (_pos <= iterator_container.size() && _pos >= 0) {
			return iterator_container[_pos];
		}
		throw OutOfRangeException();
	}

	auto get()
	{
		if (position >= 0) {
			return iterator_container[position];
		}
		throw OutOfRangeException();
	}

private:
	void assing_if_found(Iterator& it, size_t& k, bool& not_first_iteration, bool& elem_founded, size_t i)
	{
		if (not_first_iteration) {
			if (*it > * (iterator_position)[i]) {
				it = (iterator_position)[i];
				elem_founded = true;
				k = i;
			}
		}
		else {
			it = iterator_position[i];
			elem_founded = true;
			k = i;
		}
		not_first_iteration = true;
	}
	Merge_iterator(Merge_range<Iterator>& new_parent, bool end_flag)
	{
		parent = &new_parent;
		position = -2;
	}
	Merge_range<Iterator>* parent;
	std::vector<Iterator> iterator_position;
	std::vector<Iterator> iterator_container;
	int position = -1;
	friend class Merge_range<Iterator>;
	friend std::ostream& operator<<(std::ostream& stream, const Merge_iterator& iter);
};