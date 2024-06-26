#include "Order.h"

OrderManager::OrderManager(const std::string& filename, ProductManager& productManager)
    : filename(filename), productManager(productManager) {}

bool OrderManager::addOrder(const Order& newOrder) {
    std::vector<Product> products;
    productManager.readProducts(products);

    for (const auto& orderProduct : newOrder.products) {
        Product foundProduct = productManager.findProductByName(orderProduct.first);
        if (foundProduct.quantity < orderProduct.second) {
            std::cerr << "Недостаточно товара '" << foundProduct.name << "' на складе. Требуется " << orderProduct.second << ", а есть только " << foundProduct.quantity << "." << std::endl;
            return false;
        }
    }

    std::vector<Order> orders = readOrders();
    orders.push_back(newOrder);

    for (const auto& orderProduct : newOrder.products) {
        Product foundProduct = productManager.findProductByName(orderProduct.first);
        foundProduct.quantity -= orderProduct.second;
        productManager.updateProduct(foundProduct.name, foundProduct);
    }

    return writeOrders(orders);
}

bool OrderManager::changeOrderStatus(int orderIndex, const std::string& newStatus) {
    std::vector<Order> orders = readOrders();
    if (orderIndex >= 0 && orderIndex < orders.size()) {
        orders[orderIndex].status = newStatus;
        return writeOrders(orders);
    }
    else {
        std::cerr << "Неверный индекс заказа.\n";
        return false;
    }
}

void OrderManager::getOrderInfo(int orderIndex) {
    std::vector<Order> orders = readOrders();
    if (orderIndex >= 0 && orderIndex < orders.size()) {
        std::cout << "Информация о заказе:\n";
        std::cout << "Адрес доставки: " << orders[orderIndex].deliveryAddress << std::endl;
        std::cout << "Статус: " << orders[orderIndex].status << std::endl;
        std::cout << "Товары:\n";
        for (const auto& product : orders[orderIndex].products) {

            std::string productName = product.first;

            Product foundProduct = productManager.findProductByName(productName);
            if (foundProduct.name != "") {
                std::cout << "- " << foundProduct.name << " (Цена: " << foundProduct.price << ", Количество: " << product.second << ")\n";
            }
            else {
                std::cerr << "Товар '" << product.first << "' не найден в каталоге.\n";
            }
        }
    }
    else {
        std::cerr << "Неверный индекс заказа.\n";
    }
}

std::vector<Order> OrderManager::readOrders() {
    std::vector<Order> orders;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return orders;
    }

    Order order;
    std::string line;
    while (std::getline(file, line)) {
        order.deliveryAddress = line;
        std::getline(file, line);
        order.status = line;

        while (std::getline(file, line) && !line.empty()) {
            std::size_t pos = line.find(' ');
            if (pos != std::string::npos) {
                std::string productName = line.substr(0, pos);
                std::string quantityStr = line.substr(pos + 1);
                order.products.push_back(std::make_pair(productName, std::stoi(quantityStr)));
            }
        }

        orders.push_back(order);
        order.products.clear();
    }

    file.close();
    return orders;
}

bool OrderManager::writeOrders(const std::vector<Order>& orders) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }
    for (const auto& order : orders) {
        file << order.deliveryAddress << std::endl;
        file << order.status << std::endl;
        for (const auto& product : order.products) {
            file << product.first << " " << product.second << std::endl;
        }
        file << std::endl;
    }
    file.close();
    return true;
}


DeliveryMethod OrderManager::chooseDeliveryMethod(int choice) {
    switch (choice) {
        case 1 :
            return DeliveryMethod::Standard;
        case 2:
            return DeliveryMethod::Express;
        case 3:
            return DeliveryMethod::Pickup;
        default:
            return DeliveryMethod::Standard;
    }
}




double OrderManager::calculateDeliveryCost(DeliveryMethod method) {
    double basePrice = 200.0;
    switch (method) {
        case DeliveryMethod::Standard:
            return basePrice;
        case DeliveryMethod::Express:
            return basePrice * 1.5;
        case DeliveryMethod::Pickup:
            return 0;
        default:
            return -1;
    }
}

double OrderManager::calculateOrderCost(int orderIndex, DeliveryMethod deliveryMethod) {
    std::vector<Order> orders = readOrders();
    if (orderIndex >= 0 && orderIndex < orders.size()) {
        Order& order = orders[orderIndex];
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
        
        double deliveryCost = calculateDeliveryCost(deliveryMethod);
        if (deliveryCost != -1) {
            return totalCost + deliveryCost;
        }
        else {
            return -1;
        }
    }
    else {
        std::cerr << "Неверный индекс заказа.\n";
        return -1;
    }
}

