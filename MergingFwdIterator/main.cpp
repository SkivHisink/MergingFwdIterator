#include <iostream>
#include <list>
#include <vector>
#include "mergingFwdIterator.hpp"

int main()
{
	/*Если на вход поступили пары итераторов,
	соответствующие трём диапазонам 1, 2, 7, 3, 5, 8, и 6, 10, 12,
		то последовательный доступ к итератору
		должен выдать последовательность 1, 2, 3, 5, 6, 7, 8, 10, 12.*/
	std::vector<int> first_container = { 1, 2, 7 };
	std::vector<int> second_container = { 3, 5,  8 };
	std::vector<int> third_container = { 6, 10, 12 };
	using it_pair = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>;
	std::vector<it_pair> vector_of_iterators;
	vector_of_iterators.emplace_back(first_container.begin(), first_container.end());
	vector_of_iterators.emplace_back(second_container.begin(), second_container.end());
	vector_of_iterators.emplace_back(third_container.begin(), third_container.end());
	Merge_range<std::vector<int>::iterator> merge_iter(vector_of_iterators);
	auto tmp = merge_iter.begin();
	int prev_numb = 0;
	for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp)
	{
		std::cout << *tmp.get() << " ";
		if (prev_numb < *tmp.get())
		{
			std::cout << std::endl << "Something went wrong. Previous number was bigger than next." << std::endl;
		}
		prev_numb = *tmp.get();
	}
}