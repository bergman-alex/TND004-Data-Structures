// Exerc1.cpp : stable partition
//Iterative and divide-and-conquer

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>

using namespace std;

/****************************************
* Declarations                          *
*****************************************/

using Test = bool(*)(int);

//generic class to write an item to a stream
template<typename T>
class Formatter
{
public:

	Formatter(std::ostream& os, int width, int per_line)
		: os_(os), per_line_(per_line), width_(width)
	{}

	void operator()(const T& t)
	{
		os_ << std::setw(width_) << t;
		if (++outputted_ % per_line_ == 0)
			os_ << "\n";
	}

private:
	std::ostream&  os_;		//output stream
	const int per_line_;	//number of columns per line
	const int width_;		//column width
	int   outputted_{ 0 };	//counter of number of items written to os_
};

namespace TND004
{
	//Divide-and-conquer algorithm
	void stable_partition(std::vector<int>& V, Test p);

	//Iterative algorithm
	void stable_partition_iterative(std::vector<int>& V, Test p);
}


void execute(std::vector<int>& V);

bool even(int i);


/****************************************
* Main: to test                         *
*****************************************/

int main()
{
	/*****************************************************
	* TEST PHASE 1                                       *
	******************************************************/
	std::cout << "TEST PHASE 1\n\n";

	std::vector<int> seq1{ 1, 2 };

	std::cout << "Sequence: ";
	std::copy(std::begin(seq1), std::end(seq1), std::ostream_iterator<int>(std::cout, " "));

	execute(seq1);

	/*****************************************************
	* TEST PHASE 2                                       *
	******************************************************/
	std::cout << "\n\nTEST PHASE 2\n\n";

	std::vector<int> seq2{ 2 };

	std::cout << "Sequence: ";
	std::copy(std::begin(seq2), std::end(seq2), std::ostream_iterator<int>(std::cout, " "));

	execute(seq2);

	/*****************************************************
	* TEST PHASE 3                                       *
	******************************************************/
	std::cout << "\n\nTEST PHASE 3\n\n";

	std::vector<int> seq3{ 3 };

	std::cout << "Sequence: ";
	std::copy(std::begin(seq3), std::end(seq3), std::ostream_iterator<int>(std::cout, " "));

	execute(seq3);

	/*****************************************************
	* TEST PHASE 4                                       *
	******************************************************/
	std::cout << "\n\nTEST PHASE 4\n\n";

	std::vector<int> seq4{ 3, 3 };

	std::cout << "Sequence: ";
	std::copy(std::begin(seq4), std::end(seq4), std::ostream_iterator<int>(std::cout, " "));

	execute(seq4);

	/*****************************************************
	* TEST PHASE 5                                       *
	******************************************************/
	std::cout << "\n\nTEST PHASE 5\n\n";

	std::vector<int> seq5{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::cout << "Sequence: ";
	std::copy(std::begin(seq5), std::end(seq5), std::ostream_iterator<int>(std::cout, " "));

	execute(seq5);

	/*****************************************************
	* TEST PHASE 6                                       *
	******************************************************/
	std::cout << "\n\nTEST PHASE 6: test with long sequence loaded from a file\n\n";

	std::ifstream file("test_data.txt");

	if (!file)
	{
		std::cout << "Could not open test data file!!\n";
		return 0;
	}

	std::istream_iterator<int> in_itr(file);
	std::istream_iterator<int> in_itr_end;

	//read the data in the file into seq5
	std::vector<int> seq6{ in_itr,  in_itr_end };

	std::cout << "Number of items in the sequence: " << seq6.size() << "\n";

	std::vector<int> seq7{ seq6 };

	std::cout << "\n After stable partition ...\n";

	TND004::stable_partition_iterative(seq6, even);

	TND004::stable_partition(seq7, even); //recursive

	if ( std::equal(std::begin(seq6), std::end(seq6), std::begin(seq7)) )
	{
		//Display
		std::for_each(std::begin(seq7), std::end(seq7), Formatter<int>(std::cout, 8, 5));
	}
	else
	{
		std::cout << "Error: Iterative and divide-and-conquer algorithms give different results!!\n";
	}

	std::cout << "\n";

	return 0;
}

/****************************************
* Functions definitions                 *
*****************************************/

bool even(int i)
{
	return i % 2 == 0;
}

//Iterative algorithm
void TND004::stable_partition_iterative(std::vector<int>& V, Test p)
{
	//ADD IMPLEMENTATION

    std::cout << "Note implemented, yet!!\n";
}


//Auxiliary function that performs the stable partition using a divide-and-conquer strategy
namespace TND004
{
	//Divide-and-conquer algorithm: stable-partition the sub-sequence in V starting at first and ending at last-1
	//If there are items with property p then return an iterator to the end of the block containing the items with property p
	//If there are no items with property p then return first
	std::vector<int>::iterator stable_partition(std::vector<int>& V, std::vector<int>::iterator first, std::vector<int>::iterator last, Test p)
	{
		//ADD IMPLEMENTATION

        std::cout << "Note implemented, yet!!\n";

        return std::begin(V); //this is dummy code that should be removed
	}
}

void TND004::stable_partition(std::vector<int>& V, Test p)
{
	TND004::stable_partition(V, std::begin(V), std::end(V), p); //call auxiliary function
}


//Used for testing
void execute(std::vector<int>& V)
{
	std::vector<int> _copy{ V };

	std::cout << "\nIterative stable partition: ";
	TND004::stable_partition_iterative(V, even);

	//Display
	std::copy(std::begin(V), std::end(V), std::ostream_iterator<int>(std::cout, " "));

	std::cout << "\nDivide-and-conquer stable partition: ";
	TND004::stable_partition(_copy, even);

	//Display
	std::copy(std::begin(_copy), std::end(_copy), std::ostream_iterator<int>(std::cout, " "));
}
