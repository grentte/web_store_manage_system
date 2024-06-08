#include "Products.h"

ProductManager::ProductManager(const std::string& filename) : filename(filename) {}

bool ProductManager::writeProducts(const std::vector<Product>& products) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }
    for (const auto& product : products) {
        file << product.name << std::endl;
        file << product.price << std::endl;
        file << product.quantity << std::endl;
        file << product.description << std::endl;
    }
    file.close();
    return true;
}

bool ProductManager::readProducts(std::vector<Product>& products) {
    products.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }
    std::string line;
    Product product;
    while (std::getline(file, line)) {
        product.name = line;
        std::getline(file, line);
        product.price = std::stod(line);
        std::getline(file, line);
        product.quantity = std::stoi(line);
        std::getline(file, line);
        product.description = line;
        products.push_back(product);
    }
    file.close();
    return true;
}

Product ProductManager::findProductByName(const std::string& name) {
    std::vector<Product> products;
    if (!readProducts(products)) {
        return Product{};
    }
    for (auto& product : products) {
        if (product.name == name) {
            return product;
        }
    }
    return Product{};
}

bool ProductManager::updateProduct(const std::string& name, const Product& newProduct) {
    std::vector<Product> products;
    if (!readProducts(products)) {
        return false;
    }
    for (auto& product : products) {
        if (product.name == name) {
            product = newProduct;
            return writeProducts(products);
        }
    }
    return false;
}

bool ProductManager::deleteProduct(const std::string& name) {
    std::vector<Product> products;
    if (!readProducts(products)) {
        return false;
    }
    auto it = std::remove_if(products.begin(), products.end(), [&name](const Product& product) { return product.name == name; });
    products.erase(it, products.end());
    return writeProducts(products);
}


void addProduct(ProductManager& manager, std::vector<Product>& readProducts) {
Product product;
std::cout << "Введите название продукта: ";
std::getline(std::cin, product.name);

Product foundProduct = manager.findProductByName(product.name);
if (foundProduct.name != "") {
    std::cout << "Введите количество продукта для добавления: ";
    int quantity;
    std::cin >> quantity;
    foundProduct.quantity += quantity;
    manager.updateProduct(product.name, foundProduct);
    std::cout << "Количество товара '" << product.name << "' успешно обновлено!" << std::endl;
}
else {
    std::cout << "Введите цену продукта: ";
    std::cin >> product.price;
    std::cin.ignore();
    std::cout << "Введите количество продукта: ";
    std::cin >> product.quantity;
    std::cin.ignore();
    std::cout << "Введите описание продукта: ";
    std::getline(std::cin, product.description);

    std::vector<Product> products;
    manager.readProducts(products);
    products.push_back(product);
    manager.writeProducts(products);
    manager.readProducts(readProducts);
    std::cout << "Продукт добавлен!" << std::endl;
}
}

