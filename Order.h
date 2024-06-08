#pragma once
#include "Products.h"

enum class DeliveryMethod {
    Standard,
    Express,
    Pickup
};

struct Order {
    std::vector<std::pair<std::string, int>> products;
    std::string deliveryAddress;
    std::string status;
};

class OrderManager {
public:
    OrderManager(const std::string& filename, ProductManager& productManager);

    bool addOrder(const Order& newOrder);

    bool changeOrderStatus(int orderIndex, const std::string& newStatus);

    void getOrderInfo(int orderIndex);
    
    std::vector<Order> readOrders();
    
    bool writeOrders(const std::vector<Order>& orders);
    
    DeliveryMethod chooseDeliveryMethod(int choice);
    
    double calculateDeliveryCost(DeliveryMethod method);
    
    double calculateOrderCost(int orderIndex, DeliveryMethod deliveryMethod);
    
private:
    std::string filename;
    ProductManager& productManager;
};
