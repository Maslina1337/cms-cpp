#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template<typename type>
void coutVector(vector<type>* arr, string title = "", bool isVectorOfVectors = false) {
	cout << title << endl;
	for (int i = 0; i < arr->size(); i++) {
		cout << i << ". \t";

		if (isVectorOfVectors) {
			for (auto e : (*arr)[i]) cout << e << " \t";
		}
		else {
			cout << arr[i] << endl;
		}
	}
};
