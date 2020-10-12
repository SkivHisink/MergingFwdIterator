#include "pch.h"

#include <deque>
#include <list>


#include "mergingFwdIterator.hpp"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(Vector_container_test, int_test)
{
	std::vector<std::vector<int>> container_of_int_vectors;
	int number_of_vectors = rand() % 100;
	for (int i = 0; i < number_of_vectors; ++i)
	{
		std::vector<int> temp;
		int number_of_elements_in_container = rand() % 100;
		for (int j = 0; j < number_of_elements_in_container; ++j)
		{
			temp.push_back(rand() % 1000);
		}
		container_of_int_vectors.push_back(temp);
		std::sort(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
	}using it_pair = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>;
	std::vector<it_pair> iter_vec;
	for (int i = 0; i < container_of_int_vectors.size(); ++i)
	{
		iter_vec.emplace_back(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
	}
	merge_range<std::vector<int>::iterator> merge_iter(iter_vec);
	auto tmp = merge_iter.begin();
	for (auto i = 0; i < merge_iter.size() - 1; ++i)
	{
		auto tmp2 = tmp;
		tmp2++;
		EXPECT_FALSE(*tmp.get() > * tmp2.get());
		tmp = tmp2;
	}
}
TEST(Vector_container_test, double_test)
{
	std::vector<std::vector<double>> container_of_double_vectors;
	int number_of_vectors = rand() % 100;
	for (int i = 0; i < number_of_vectors; ++i)
	{
		std::vector<double> temp;
		int number_of_elements_in_container = rand() % 100;
		for (int j = 0; j < number_of_elements_in_container; ++j)
		{
			temp.push_back(static_cast<double>(rand() % 1000));
		}
		container_of_double_vectors.push_back(temp);
		std::sort(container_of_double_vectors[i].begin(), container_of_double_vectors[i].end());
	}using it_pair = std::pair<std::vector<double>::iterator, std::vector<double>::iterator>;
	std::vector<it_pair> iter_vec;
	for (int i = 0; i < container_of_double_vectors.size(); ++i)
	{
		iter_vec.emplace_back(container_of_double_vectors[i].begin(), container_of_double_vectors[i].end());
	}
	merge_range<std::vector<double>::iterator> merge_iter(iter_vec);
	auto tmp = merge_iter.begin();
	for (auto i = 0; i < merge_iter.size() - 1; ++i)
	{
		auto tmp2 = tmp;
		tmp2++;
		EXPECT_FALSE(*tmp.get() > * tmp2.get());
		tmp = tmp2;
	}
}
TEST(Deque_container_test, int_test)
{
	std::vector<std::deque<int>> container_of_double_deque;
	int number_of_vectors = rand() % 100;
	for (int i = 0; i < number_of_vectors; ++i)
	{
		std::deque<int> temp;
		int number_of_elements_in_container = rand() % 100;
		for (int j = 0; j < number_of_elements_in_container; ++j)
		{
			temp.push_back(static_cast<double>(rand() % 1000));
		}
		container_of_double_deque.push_back(temp);
		std::sort(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
	}using it_pair = std::pair<std::deque<int>::iterator, std::deque<int>::iterator>;
	std::vector<it_pair> iter_vec;
	for (int i = 0; i < container_of_double_deque.size(); ++i)
	{
		iter_vec.emplace_back(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
	}
	merge_range<std::deque<int>::iterator> merge_iter(iter_vec);
	auto tmp = merge_iter.begin();
	for (auto i = 0; i < merge_iter.size() - 1; ++i)
	{
		auto tmp2 = tmp;
		tmp2++;
		EXPECT_FALSE(*tmp.get() > * tmp2.get());
		tmp = tmp2;
	}
}
TEST(Deque_container_test, double_test)
{
	std::vector<std::deque<double>> container_of_double_deque;
	int number_of_vectors = rand() % 100;
	for (int i = 0; i < number_of_vectors; ++i)
	{
		std::deque<double> temp;
		int number_of_elements_in_container = rand() % 100;
		for (int j = 0; j < number_of_elements_in_container; ++j)
		{
			temp.push_back(static_cast<double>(rand() % 1000));
		}
		container_of_double_deque.push_back(temp);
		std::sort(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
	}using it_pair = std::pair<std::deque<double>::iterator, std::deque<double>::iterator>;
	std::vector<it_pair> iter_vec;
	for (int i = 0; i < container_of_double_deque.size(); ++i)
	{
		iter_vec.emplace_back(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
	}
	merge_range<std::deque<double>::iterator> merge_iter(iter_vec);
	auto tmp = merge_iter.begin();
	for (auto i = 0; i < merge_iter.size() - 1; ++i)
	{
		auto tmp2 = tmp;
		tmp2++;
		EXPECT_FALSE(*tmp.get() > * tmp2.get());
		tmp = tmp2;
	}
}
TEST(List_container_test, double_test)
{
	std::vector<std::list<double>> container_of_double_list;
	int number_of_vectors = rand() % 100;
	for (int i = 0; i < number_of_vectors; ++i)
	{
		std::list<double> temp;
		int number_of_elements_in_container = rand() % 100;
		for (int j = 0; j < number_of_elements_in_container; ++j)
		{
			temp.push_back(static_cast<double>(rand() % 1000));
		}
		container_of_double_list.push_back(temp);
		//std::sort(container_of_double_list[i].begin(), container_of_double_list[i].end());
		container_of_double_list[i].sort();
	}using it_pair = std::pair<std::list<double>::iterator, std::list<double>::iterator>;
	std::vector<it_pair> iter_vec;
	for (int i = 0; i < container_of_double_list.size(); ++i)
	{
		iter_vec.emplace_back(container_of_double_list[i].begin(), container_of_double_list[i].end());
	}
	merge_range<std::list<double>::iterator> merge_iter(iter_vec);
	auto tmp = merge_iter.begin();
	for (auto i = 0; i < merge_iter.size() - 1; ++i)
	{
		auto tmp2 = tmp;
		tmp2++;
		EXPECT_FALSE(*tmp.get() > * tmp2.get());
		tmp = tmp2;
	}
}
TEST(List_container_test, int_test)
{
	std::vector<std::list<int>> container_of_int_list;
	int number_of_vectors = rand() % 100;
	for (int i = 0; i < number_of_vectors; ++i)
	{
		std::list<int> temp;
		int number_of_elements_in_container = rand() % 100;
		for (int j = 0; j < number_of_elements_in_container; ++j)
		{
			temp.push_back(static_cast<double>(rand() % 1000));
		}
		container_of_int_list.push_back(temp);
		//std::sort(container_of_double_list[i].begin(), container_of_double_list[i].end());
		container_of_int_list[i].sort();
	}using it_pair = std::pair<std::list<int>::iterator, std::list<int>::iterator>;
	std::vector<it_pair> iter_vec;
	for (int i = 0; i < container_of_int_list.size(); ++i)
	{
		iter_vec.emplace_back(container_of_int_list[i].begin(), container_of_int_list[i].end());
	}
	merge_range<std::list<int>::iterator> merge_iter(iter_vec);
	auto tmp = merge_iter.begin();
	for (auto i = 0; i < merge_iter.size() - 1; ++i)
	{
		auto tmp2 = tmp;
		tmp2++;
		EXPECT_FALSE(*tmp.get() > * tmp2.get());
		tmp = tmp2;
	}
}
