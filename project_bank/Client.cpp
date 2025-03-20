#include <iostream>
#include <string>
#include "Client.h"
using namespace std;



Client::Client(string first_name, string last_name, int age, string address, int passport_series, int passport_number) : first_name(first_name), last_name(last_name), age(age), address(address), passport_series(passport_series), passport_number(passport_number) {};

void Client::DisplayInfoClient() {
	cout << "Имя: \t" << first_name << "\n" << "Фамилия: \t" << last_name << "\n" << "Адрес: \t" << address;
}