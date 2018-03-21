#include "StatisticMultiset.hpp"
#include <iostream>
#include <vector>

int main() {
	StatisticMultiset<int> mset, mmset;
	mset.AddNum(5);
	mset.AddNum(3);
	std::vector<int> test = { 1, 2, 3, 4 };
	mmset.AddNum(test);
	mset.AddNum(mmset);
	std::cout << mset.GetAvg() << " " << mset.GetCountAbove(2) << " " << mset.GetCountUnder(1);
	mset.AddNum(6);
	std::cout << std::endl << mset.GetAvg() << " " << mset.GetCountAbove(2) << " " << mset.GetCountUnder(1);
	std::getchar();

}