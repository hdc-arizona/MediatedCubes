#include <iostream>
#include <string>
#include <iterator>
#include <chrono>

#include "Address.h"
#include "DimAddress.h"
#include "MediatedCube.h"
#include "Mercator.h"
#include "MemoryUtil.h"

/*
 * Cat the contents of the brightkite data into this (skip the header please).
 */

using namespace std;

vector<string> split(string s, char c) {
	vector<string> pieces;
	size_t start = 0;
	size_t end = 0;
	while(end <= s.size()) {
		if(end == s.size() || s[end] == c) {
			pieces.push_back(s.substr(start, end - start));
			start = end = end + 1;
		} else {
			end += 1;
		}	
	}
	return pieces;
}

string to_b(uint32_t x) {
	string s;
	while(x > 0) {
		s = to_string(x % 2) + s;	
		x /= 2;
	}
	return s;
}

void mem_info() {
	memory_util::MemInfo m = memory_util::MemInfo::get();
	stringstream ss;
	ss << "Memory (MB): " << m.res_MB();
	return ss.str();
}

int main() {

	MediatedCube m;
	Address all({ DimAddress(""), DimAddress(""), DimAddress("") });

	cout << mem_info() << endl;


	auto start = chrono::high_resolution_clock::now();


	string line;
	size_t count = 0;
	while(getline(cin, line)) {
		auto pieces = split(line, ',');
		string lat = to_b(util::lat2tiley(stof(pieces[2]), 25));
		string lon = to_b(util::lon2tilex(stof(pieces[3]), 25));
		string month = to_b(stoi(split(pieces[1], '-')[1]));

		m.add(Address({ DimAddress(lat), DimAddress(lon), DimAddress(month) }), 1);

		if((count + 1) % 100 == 0) {
			auto summary = m.size_summary();
			cout << "Count = " << count + 1 
				<< ", Cube reports table sizes "
				<< "(" << get<0>(summary) << ", " << get<1>(summary) << ")"
				<< ", " << mem_info() << endl;
		}
		count++;
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = (end - start).count();
	cout << "Time: " << duration / 1000000000 
		<< "." << (duration / 1000000) % 1000 << endl;

	cout << mem_info() << endl;

	return 0;
}
