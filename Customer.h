#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Customer {
    std::string username;
    std::string password;
};

class CustomerManager {
public:
    CustomerManager(const std::string& filename);

    bool registerCustomer(const Customer& newCustomer);

    bool authorizeCustomer(const std::string& username, const std::string& password);
    
private:
    std::vector<Customer> readCustomers();

    bool writeCustomers(const std::vector<Customer>& customers);

    std::string filename;
};
