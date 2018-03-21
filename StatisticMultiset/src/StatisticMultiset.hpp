#pragma once
#include <set>
#include <list>
#include <vector>
#include <string>
#include <map>

template<class T>
class StatisticMultiset {
public:
	StatisticMultiset<T>();
	StatisticMultiset<T>(const std::vector<T>& vector);
	StatisticMultiset<T>(const std::list<T>& lis);
	StatisticMultiset<T>(const std::multiset<T>& mset);
	StatisticMultiset<T>(const std::set<T>& dset);
	StatisticMultiset<T>(const std::string& filename);
	
	void AddNum(const T& num);
	void AddNum(const std::multiset<T>& numbers);
	void AddNum(const std::list<T>& numbers);
	void AddNum(const std::set<T>& numbers);
	void AddNum(const std::vector<T>& numbers);
	void AddNum(const StatisticMultiset& statSet);
	void AddNumsFromFile(const std::string& filename);
	void AddNumsFromStream(const std::istream& stream);

	T GetMax() const;
	T GetMin() const;
	float GetAvg() const;
	int GetCountUnder(float number) const;
	int GetCountAbove(float number) const;

private:
	void CalcValueOfAvg() const;
	void InsertCacheUnder(float number, int count) const;
	void InsertCacheAbove(float number, int count) const;
	std::istream MakeStream(std::string& filename) const;
	mutable std::map<float, int> countAboveDataCache;
	mutable std::map<float, int> countUnderDataCache;
	std::multiset<T> data;
	mutable float avgValue;
	
};

template <typename T>
StatisticMultiset<T>::StatisticMultiset() {
	avgValue = 0;
}

template <typename T>
StatisticMultiset<T>::StatisticMultiset(const std::string& filename) {
	AddNumsFromFile(filename)
}

template <typename T>
StatisticMultiset<T>::StatisticMultiset(const std::list<T>& lis) {
	AddNum(lis);
}

template <typename T>
StatisticMultiset<T>::StatisticMultiset(const std::vector<T>& vec) {
	AddNum(vec);
}

template <typename T>
StatisticMultiset<T>::StatisticMultiset(const std::multiset<T>& mset) {
	AddNum(mset);
}

template <typename T>
StatisticMultiset<T>::StatisticMultiset(const std::set<T>& dset) {
	AddNum(dset);
}

template <typename T>
void StatisticMultiset<T>::AddNum(const T& num) {
	data.insert(num);
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
void StatisticMultiset<T>::AddNum(const std::list<T>& numbers) {
	data.insert(numbers.begin(), numbers.end());
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
void StatisticMultiset<T>::AddNum(const std::vector<T>& numbers) {
	data.insert(numbers.begin(), numbers.end());
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
void StatisticMultiset<T>::AddNum(const std::multiset<T>& numbers) {
	data.insert(numbers.begin(), numbers.end());
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
void StatisticMultiset<T>::AddNum(const std::set<T>& numbers) {
	data.insert(numbers.begin(), numbers.end());
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
void StatisticMultiset<T>::AddNum(const StatisticMultiset<T>& numbers) {
	data.insert(numbers.data.begin(), numbers.data.end());
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
void StatisticMultiset<T>::AddNumsFromFile(const std::string& filename) {
	AddNumsFromStream(MakeStream(filename));
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
std::istream StatisticMultiset<T>::MakeStream(std::string& filename) const {
	std::ifstream stream(filename);
	return stream;
}

template <typename T>
void StatisticMultiset<T>::AddNumsFromStream(const std::istream& stream) {
	T value;
	while (stream >> value) {
		AddNum(value);
	}
	countAboveDataCache.clear();
	countUnderDataCache.clear();
}

template <typename T>
T StatisticMultiset<T>::GetMin() const {
	return *data.begin();
}

template <typename T>
T StatisticMultiset<T>::GetMax() const {
	return *data.rbegin();
}

template <typename T>
int StatisticMultiset<T>::GetCountUnder(float number) const {
	if (!countUnderDataCache.count(number)) {
		int count = static_cast<int>(std::distance(data.cbegin(), data.lower_bound(number)));
		InsertCacheUnder(number, count);
		return count;
	}
	return countUnderDataCache[number];
}

template <typename T>
int StatisticMultiset<T>::GetCountAbove(float number) const {
	if (!countAboveDataCache.count(number)) {
		int count = static_cast<int>(std::distance(data.upper_bound(number), data.end()));
		InsertCacheAbove(number, count);
		return count;
	}
	return countAboveDataCache[number];
}



template <typename T>
void StatisticMultiset<T>::CalcValueOfAvg() const {
	avgValue = 0;
	if (!data.empty()) {
		for (const auto &it : data)
			avgValue += it;
		avgValue /= data.size();
	}
}

template <typename T>
float StatisticMultiset<T>::GetAvg() const {
	CalcValueOfAvg();
	return avgValue;
}

template <typename T>
void StatisticMultiset<T>::InsertCacheAbove(float number, int count) const {
	countAboveDataCache[number] = count;
}

template <typename T>
void StatisticMultiset<T>::InsertCacheUnder(float number, int count) const {
	countUnderDataCache[number] = count;
}



