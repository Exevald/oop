#include "VectorProcessor.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<float> InitializeVectorFromStream(std::istream& inputStream)
{
	float vectorItem;
	std::vector<float> vector;
	while (inputStream >> vectorItem)
	{
		vector.push_back(vectorItem);
	}
	if (!inputStream.eof())
	{
		throw std::runtime_error("Failed to read text from file");
	}
	return vector;
}

void DivideItemsOnHalfMaxElement(std::vector<float>& vector)
{
	if (vector.empty())
	{
		return;
	}
	float halfOfMaxElement = *std::max_element(vector.begin(), vector.end()) / 2;
	std::transform(vector.begin(), vector.end(), vector.begin(), [halfOfMaxElement](float vectorItem) {
		return vectorItem / halfOfMaxElement;
	});
}

void WriteVector(const std::vector<float>& vector)
{
	for (const float& vectorItem : vector)
	{
		std::cout << std::fixed << std::setprecision(3) << vectorItem << " ";
	}
}