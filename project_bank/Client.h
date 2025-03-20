#pragma once
#include <iostream>

using namespace std;


class Client {
	string first_name;
	string last_name;
	int age;
	string address;
	int passport_series;
	int passport_number;
public:
	Client(string first_name, string last_name, int age, string address, int passport_series, int passport_number);

	void DisplayInfoClient();


};


