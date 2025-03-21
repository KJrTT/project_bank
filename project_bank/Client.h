#pragma once
#include <iostream>
#include <string>

using namespace std;

class Client {
	string first_name;
	string last_name;
	int age;
	string address;
	int passport_series;
	int passport_number;
public:
	Client(std::string first_name, std::string last_name, int age, std::string address, int passport_series, int passport_number);

	void DisplayInfoClient();
	string GetFirstName();
	string GetLastName();
};


