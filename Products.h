#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Product {
    std::string name;
    double price;
    int quantity;
    std::string description;
};

class ProductManager {
public:

    ProductManager(const std::string& filename);

    bool writeProducts(const std::vector<Product>& products);
    
    bool readProducts(std::vector<Product>& products);
    
    Product findProductByName(const std::string& name);

    bool updateProduct(const std::string& name, const Product& newProduct);
    
    bool deleteProduct(const std::string& name);

private:
    std::string filename;
};

void addProduct(ProductManager& manager, std::vector<Product>& readProducts);
