#include "Customer.h"

CustomerManager::CustomerManager(const std::string& filename) : filename(filename) {}

bool CustomerManager::registerCustomer(const Customer& newCustomer) {
    std::vector<Customer> customers = readCustomers();
    if (std::find_if(customers.begin(), customers.end(),
        [&newCustomer](const Customer& c) { return c.username == newCustomer.username; }) != customers.end()) {
        std::cerr << "Пользователь с таким именем уже существует.\n";
        return false;
    }
    customers.push_back(newCustomer);
    return writeCustomers(customers);
}

bool CustomerManager::authorizeCustomer(const std::string& username, const std::string& password) {
    std::vector<Customer> customers = readCustomers();
    for (const auto& customer : customers) {
        if (customer.username == username && customer.password == password) {
            std::cout << "Авторизация успешна!\n";
            return true;
        }
    }
    std::cerr << "Неверный логин или пароль.\n";
    return false;
}


std::vector<Customer> CustomerManager::readCustomers() {
    std::vector<Customer> customers;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return customers;
    }

    Customer customer;
    while (std::getline(file, customer.username) && std::getline(file, customer.password)) {
        customers.push_back(customer);
    }
    file.close();
    return customers;
}

bool CustomerManager::writeCustomers(const std::vector<Customer>& customers) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }
    for (const auto& customer : customers) {
        file << customer.username << std::endl;
        file << customer.password << std::endl;
    }
    file.close();
    return true;
}
