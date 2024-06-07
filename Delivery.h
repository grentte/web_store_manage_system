#pragma once
#include <string>
#include "Products.h"
#include "Order.h"

enum class DeliveryMethod {
    Standard,
    Express,
    Pickup
};


struct Delivery {
    std::string deliveryAddress;
    int orderNumber;
    double deliveryCost;
    DeliveryMethod deliveryMethod;
};


class DeliveryManager {
public:
    DeliveryManager(const std::string& filename) : filename(filename) {}
    
    
    double countCost(int orderNumber, const Order& order) {
        std::vector<Product> products;
        ProductManager productManager;
        productManager.readProducts(products);

        double totalCost = 0;
        for (const auto& product : order.products) {
            Product foundProduct = productManager.findProductByName(product.first);
            if (foundProduct.name != "") {
                totalCost += foundProduct.price * product.second;
            }
            else {
                std::cerr << "Товар '" << product.first << "' не найден в каталоге.\n";
                return -1;
            }
        }
        return totalCost;
    }


    bool addDelivery(const Delivery& newDelivery) {
        std::vector<Delivery> deliveries = readDeliveries();
        deliveries.push_back(newDelivery);
        return writeDeliveries(deliveries);
    }

    std::vector<Delivery> readDeliveries() {
        std::vector<Delivery> deliveries;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла: " << filename << std::endl;
            return deliveries;
        }

        Delivery delivery;
        std::string line;
        while (std::getline(file, line)) {
            delivery.deliveryAddress = line;
            std::getline(file, line);
            delivery.orderNumber = std::stoi(line);
            std::getline(file, line);
            delivery.deliveryCost = std::stod(line);
            std::getline(file, line);
            int methodInt = std::stoi(line);
            delivery.deliveryMethod = static_cast<DeliveryMethod>(methodInt);

            deliveries.push_back(delivery);
        }

        file.close();
        return deliveries;
    }

    bool writeDeliveries(const std::vector<Delivery>& deliveries) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла: " << filename << std::endl;
            return false;
        }
        for (const auto& delivery : deliveries) {
            file << delivery.deliveryAddress << std::endl;
            file << delivery.orderNumber << std::endl;
            file << delivery.deliveryCost << std::endl;
            file << static_cast<int>(delivery.deliveryMethod) << std::endl;
        }
        file.close();
        return true;
    }

private:
    std::string filename;
};
