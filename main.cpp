#include <iostream>
// #include <string>
// #include <deque>
# include <sys/time.h>

// #if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	// namespace ft = std;
// #else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
// #endif

#include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
#define BUFFER_SIZE 130
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

// #define COUNT (MAX_RAM / (int)sizeof(Buffer))
#define COUNT 130

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template<typename T>
class MutantStack2 : public std::stack<T>
{
public:
	MutantStack2() {}
	MutantStack2(const MutantStack2<T>& src) { *this = src; }
	MutantStack2<T>& operator=(const MutantStack2<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack2() {}

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	// if (argc != 2)
	// {
	// 	std::cerr << "Usage: ./test seed" << std::endl;
	// 	std::cerr << "Provide a seed please" << std::endl;
	// 	std::cerr << "Count value:" << COUNT << std::endl;
	// 	return 1;
	// }
	// const int seed = atoi(argv[1]);
	// const int seed = 130;
	// srand(seed);

	ft::vector<std::string>	vector_str;

	ft::vector<int>			vector_int;
	std::vector<int>		vec_int;

	ft::vector<Buffer>		vector_buffer;
	// ft::stack<int> stack_int;
	// ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	std::map<int, int> map_int;
	// ft::map<int, int> map_int;

	ft::map<int, int> my_map;
	std::map<int, int> std_map;

// Vector part

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}

	int	max_value;

	max_value = 25;
	std::cout << std::endl << " ~~~ Vector values ~~~ " << std::endl;
	std::cout << "my vector" << std::endl;
	std::cout << "size\tcapacity" << std::endl;
	for (int i = 0; i < max_value; i++)
	{
		vector_int.push_back(i);
		std::cout << vector_int.size() << "\t" << vector_int.capacity() << std::endl;
	}
	std::cout << "std vector" << std::endl;
	std::cout << "size\tcapacity" << std::endl;
	for (int i = 0; i < max_value; i++)
	{
		vec_int.push_back(i);
		std::cout << vec_int.size() << "\t" << vec_int.capacity() << std::endl;
	}

	struct timeval	tv;
	struct timeval	tv1;

	gettimeofday(&tv, NULL);
	std::cout << std::endl << "Time 1: " <<
	((tv.tv_sec * 1000000) + tv.tv_usec) << " micro sec" << std::endl << std::endl;

	std::cout << "My vector: " << std::endl;
	for (int i = 0; i < max_value; i++)
		std::cout << vector_int[i] << " ";

	gettimeofday(&tv1, NULL);
	std::cout << std::endl << std::endl << "Time 2: " <<
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv1.tv_sec * 1000000) + tv1.tv_usec) - \
	((tv.tv_sec * 1000000) + tv.tv_usec) << std::endl;

	std::cout << std::endl << "Standart vector: " << std::endl;
	for (int i = 0; i < max_value; i++)
		std::cout << vec_int[i] << " ";

	gettimeofday(&tv, NULL);
	std::cout << std::endl << std::endl << "Time 3: " <<
	((tv.tv_sec * 1000000) + tv.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv.tv_sec * 1000000) + tv.tv_usec) - \
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << std::endl;

	std::cout << std::endl << std::endl << "My vector: " << std::endl;
	std::cout << ".operator[]() element:\t" << vector_int.operator[](1) << " " << std::endl;
	std::cout << ".at() element:\t\t"	<< vector_int.at(1) << " " << std::endl;
	std::cout << ".front() element:\t"	<< vector_int.front() << " " << std::endl;
	std::cout << ".back() element:\t"	<< vector_int.back() << " " << std::endl;
	std::cout << "is .empty()?\t\t"		<< vector_int.empty() << " " << std::endl;
	std::cout << ".size():\t\t"			<< vector_int.size() << " " << std::endl;
	std::cout << ".max_size():\t\t"		<< vector_int.max_size() << " " << std::endl;
	std::cout << ".capacity():\t\t"		<< vector_int.capacity() << " " << std::endl;
	std::cout << ".reserve():\t\t"		<< "'42'" << std::endl;
										vector_int.reserve(42);
	std::cout << ".capacity():\t\t"		<< vector_int.capacity() << " " << std::endl;
										ft::vector<int>::iterator it = vector_int.begin();
	std::cout << ".insert():\t\t" 		<< "'42'" << std::endl;
										it = vector_int.insert(it, 42);
		it++;
		it++;
	std::cout << ".erase():\t\t"		<< *it << std::endl;
										vector_int.erase(it);
	std::cout << ".push_back():\t\t'42'" << std::endl; 
										vector_int.push_back(42);
	std::cout << ".back() element:\t"	<< vector_int.back() << " " << std::endl;
	std::cout << ".resize():\t\t20" << std::endl;
										vector_int.resize(20, 99);
	std::cout << ".size():\t\t"			<< vector_int.size() << " " << std::endl;
	std::cout << "all values:\t\t";
	for (int i = 0; i < (int)vector_int.size(); i++)
		std::cout << vector_int[i] << " ";
	std::cout << std::endl << ".pop_back() element\t\t" << std::endl;
										vector_int.pop_back();
	std::cout << ".size():\t\t"			<< vector_int.size() << " " << std::endl;
	std::cout << "all values:\t\t";
	for (int i = 0; i < (int)vector_int.size(); i++)
		std::cout << vector_int[i] << " ";
	std::cout << std::endl << ".clear() elements\t\t" << std::endl;
										vector_int.clear();
	std::cout << ".size():\t\t"			<< vector_int.size() << " " << std::endl;

	gettimeofday(&tv1, NULL);
	std::cout << std::endl << std::endl << "Time 4: " <<
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv1.tv_sec * 1000000) + tv1.tv_usec) - \
	((tv.tv_sec * 1000000) + tv.tv_usec) << std::endl;

	std::cout << std::endl << std::endl << "Standart vector: " << std::endl;
	std::cout << ".operator[]() element:\t" << vec_int.operator[](1) << " " << std::endl;
	std::cout << ".at() element:\t\t"	<< vec_int.at(1) << " " << std::endl;
	std::cout << ".front() element:\t"	<< vec_int.front() << " " << std::endl;
	std::cout << ".back() element:\t"	<< vec_int.back() << " " << std::endl;
	std::cout << "is .empty()?\t\t"		<< vec_int.empty() << " " << std::endl;
	std::cout << ".size():\t\t"			<< vec_int.size() << " " << std::endl;
	std::cout << ".max_size():\t\t"		<< vec_int.max_size() << " " << std::endl;
	std::cout << ".capacity():\t\t"		<< vec_int.capacity() << " " << std::endl;
	std::cout << ".reserve():\t\t"		<< "'42'" << std::endl;
										vec_int.reserve(42);
	std::cout << ".capacity():\t\t"		<< vec_int.capacity() << " " << std::endl;
										std::vector<int>::iterator it2 = vec_int.begin();
	std::cout << ".insert():\t\t"		<< "'42'" << std::endl;
										it2 = vec_int.insert(it2, 42);
		it2++;
		it2++;
	std::cout << ".erase():\t\t"		<< *it2 << std::endl;
										vec_int.erase(it2);
	std::cout << ".push_back():\t\t'42'" << std::endl; 
										vec_int.push_back(42);
	std::cout << ".back() element:\t"	<< vec_int.back() << " " << std::endl;
	std::cout << ".resize():\t\t20" << std::endl;
										vec_int.resize(20, 99);
	std::cout << ".size():\t\t"			<< vec_int.size() << " " << std::endl;
	std::cout << "all values:\t\t";
	for (int i = 0; i < (int)vec_int.size(); i++)
		std::cout << vec_int[i] << " ";
	std::cout << std::endl << ".pop_back() element\t\t" << std::endl;
										vec_int.pop_back();
	std::cout << ".size():\t\t"			<< vec_int.size() << " " << std::endl;
	std::cout << "all values:\t\t";
	for (int i = 0; i < (int)vec_int.size(); i++)
		std::cout << vec_int[i] << " ";
	std::cout << std::endl << ".clear() elements\t\t" << std::endl;
										vec_int.clear();
	std::cout << ".size():\t\t"			<< vec_int.size() << " " << std::endl;

	gettimeofday(&tv, NULL);
	std::cout << std::endl << std::endl << "Time 5: " <<
	((tv.tv_sec * 1000000) + tv.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv.tv_sec * 1000000) + tv.tv_usec) - \
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << std::endl;

// Map part

	std::cout << std::endl << std::endl << "~~~ Map ~~~ " << std::endl;
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(std::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}

	for (int i = 0; i < COUNT; ++i)
	{
		my_map.insert(ft::make_pair(i, i));
		std_map.insert(std::make_pair(i, i));
	}

	gettimeofday(&tv1, NULL);
	std::cout << std::endl << "Time 6: " <<
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv1.tv_sec * 1000000) + tv1.tv_usec) - \
	((tv.tv_sec * 1000000) + tv.tv_usec) << std::endl;

	std::cout << std::endl << " ~~~ My map ~~~ " << std::endl;
	for (int i = 0; i < (int)my_map.size(); i++)
		std::cout << my_map[i] << " ";
	std::cout << std::endl << std::endl;
	std::cout << ".at(2) element:\t\t"			<< my_map.at(2) << std::endl;
	std::cout << ".operator[](1) element:\t"	<< my_map.operator[](1) << std::endl;
	std::cout << "is .empty()?\t\t"				<< my_map.empty() << std::endl;
	std::cout << ".size()\t\t\t"				<< my_map.size() << std::endl;
	std::cout << ".max_size()\t\t"				<< my_map.max_size() << std::endl;
	std::cout << ".erase()\t\t"					<< my_map.erase(1) << std::endl;
	for (int i = 0; i < (int)my_map.size(); i++)
		std::cout << my_map[i] << " ";
	std::cout << std::endl;
	std::cout << ".count(0)\t\t"				<< my_map.count(0) << std::endl;
	ft::map<int, int>::iterator it3 = my_map.find(23);
	std::cout << ".find(23)\t\t"				<< it3->second << std::endl;
		it3 = my_map.lower_bound(4);
	std::cout << ".lower_bound(4)\t\t" << it3->second << std::endl;
		it3 = my_map.upper_bound(20);
	std::cout << ".upper_bound(20)\t" << it3->second << std::endl;
	std::cout << ".clear()\t\t"					<< "(all elements)" << std::endl;
					my_map.clear();
	std::cout << ".size()\t\t\t"				<< my_map.size() << std::endl;
	std::cout << std::endl;

	gettimeofday(&tv, NULL);
	std::cout << std::endl << "Time 7: " <<
	((tv.tv_sec * 1000000) + tv.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv.tv_sec * 1000000) + tv.tv_usec) - \
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << std::endl;

	std::cout << std::endl << " ~~~ Std map ~~~ " << std::endl;
	for (int i = 0; i < (int)std_map.size(); i++)
		std::cout << std_map[i] << " ";
	std::cout << std::endl << std::endl;
	std::cout << ".at(2) element:\t\t"			<< std_map.at(2) << std::endl;
	std::cout << ".operator[](1) element:\t"	<< std_map.operator[](1) << std::endl;
	std::cout << "is .empty()?\t\t"				<< std_map.empty() << std::endl;
	std::cout << ".size()\t\t\t"				<< std_map.size() << std::endl;
	std::cout << ".max_size()\t\t"				<< std_map.max_size() << std::endl;
	std::cout << ".erase()\t\t"					<< std_map.erase(1) << std::endl;
	for (int i = 0; i < (int)std_map.size(); i++)
		std::cout << std_map[i] << " ";
	std::cout << std::endl;
	std::cout << ".count(0)\t\t"				<< std_map.count(0) << std::endl;
		std::map<int, int>::iterator it4 = std_map.find(23);
	std::cout << ".find(23)\t\t"				<< it4->second << std::endl;
		it4 = std_map.lower_bound(4);
	std::cout << ".lower_bound(4)\t\t" << it4->second << std::endl;
		it4 = std_map.upper_bound(20);
	std::cout << ".upper_bound(20)\t" << it4->second << std::endl;
	std::cout << ".clear()\t\t"					<< "(all elements)" << std::endl;
					std_map.clear();
	std::cout << ".size()\t\t\t"				<< std_map.size() << std::endl;
	std::cout << std::endl;	

// Stack part

	gettimeofday(&tv1, NULL);
	std::cout << std::endl << "Time 8: " <<
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv1.tv_sec * 1000000) + tv1.tv_usec) - \
	((tv.tv_sec * 1000000) + tv.tv_usec) << std::endl;

	std::cout << std::endl << "~~~ my Stack ~~~ " << std::endl;
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	std::cout << "Size:\t\t\t"			<< iterable_stack.size() << std::endl;
	std::cout << "Is it empty?\t\t"		<< iterable_stack.empty() << std::endl;
	std::cout << "Top element:\t\t"		<< iterable_stack.top() << std::endl;
	std::cout << "Delete top element\t"	<< "(yes)" << std::endl;
										iterable_stack.pop();
	std::cout << "New top element:\t"	<< iterable_stack.top() << std::endl;
	std::cout << "Total stack:\t"		<< std::endl;
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		std::cout << *it;
	std::cout << std::endl << std::endl;

	gettimeofday(&tv, NULL);
	std::cout << std::endl << "Time 9: " <<
	((tv.tv_sec * 1000000) + tv.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv.tv_sec * 1000000) + tv.tv_usec) - \
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << std::endl;

	std::cout << std::endl << "~~~ std Stack ~~~ " << std::endl;
	MutantStack2<char> iterable_stack_std;
	for (char letter_std = 'a'; letter_std <= 'z'; letter_std++)
		iterable_stack_std.push(letter_std);
	for (MutantStack2<char>::iterator it_std = iterable_stack_std.begin(); it_std != iterable_stack_std.end(); it_std++)
	{
		std::cout << *it_std;
	}
	std::cout << std::endl;
	std::cout << "Size:\t\t\t"			<< iterable_stack_std.size() << std::endl;
	std::cout << "Is it empty?\t\t"		<< iterable_stack_std.empty() << std::endl;
	std::cout << "Top element:\t\t"		<< iterable_stack_std.top() << std::endl;
	std::cout << "Delete top element\t"	<< "(yes)" << std::endl;
										iterable_stack_std.pop();
	std::cout << "New top element:\t"	<< iterable_stack_std.top() << std::endl;
	std::cout << "Total stack:\t"		<< std::endl;
	for (MutantStack2<char>::iterator it_std = iterable_stack_std.begin(); it_std != iterable_stack_std.end(); it_std++)
		std::cout << *it_std;
	std::cout << std::endl << std::endl;

	gettimeofday(&tv1, NULL);
	std::cout << std::endl << "Time 10: " <<
	((tv1.tv_sec * 1000000) + tv1.tv_usec) << " micro sec" << std::endl;
	std::cout << "diff: " << ((tv1.tv_sec * 1000000) + tv1.tv_usec) - \
	((tv.tv_sec * 1000000) + tv.tv_usec) << std::endl;

	return (0);
}
