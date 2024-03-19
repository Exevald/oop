#include "VectorProcessor.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	try
	{
		std::vector<float> vector = InitializeVectorFromStream(std::cin);
		std::ranges::sort(vector);
		DivideItemsOnHalfMaxElement(vector);
		WriteVector(vector);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}