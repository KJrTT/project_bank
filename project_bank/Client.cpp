#include <iostream>
#include <string>
#include "Client.h"

Client::Client(std::string first_name, std::string last_name, int age, 
               std::string address, int passport_series, int passport_number)
    : first_name(first_name), last_name(last_name), age(age), 
      address(address), passport_series(passport_series), 
      passport_number(passport_number) {}

void Client::DisplayInfoClient(){
    std::cout << "Имя: \t" << first_name << "\n"
              << "Фамилия: \t" << last_name << "\n"
              << "Адрес: \t" << address << std::endl;
}


std::string Client::GetFirstName(){
    return first_name;
}

std::string Client::GetLastName(){
    return last_name;
}

