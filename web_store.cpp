#include "Customer.h"
#include "Products.h"
#include "Order.h"
#include "Delivery.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    setlocale(LC_ALL, "Russian");
    

    std::string filename1 = "сustomers.txt";
    std::string filename2 = "products.txt";
    std::string filename3 = "orders.txt";
    std::string filename4 = "deliveries.txt";
    CustomerManager customerManager(filename1);
    ProductManager productManager(filename2);
    OrderManager orderManager(filename3, productManager);
    DeliveryManager deliveryManager(filename4);

    std::vector<Product> readProducts;
    productManager.readProducts(readProducts);
    std::vector<Order> readOrders;
    std::vector<Delivery> readDeliveries;

    bool running = true;
    bool is_authorised = false;
    while (running) {
        int main_choice;
        do {
            std::cout << "\nМеню:\n";
            std::cout << "1. Управление клиентами\n";
            std::cout << "2. Управление продуктами\n";
            std::cout << "3. Управление заказами\n";
            std::cout << "4. Управление доставкой\n";
            std::cout << "5. Выход\n";
            std::cout << "Выберите действие: ";
            std::cin >> main_choice;
            std::cin.ignore();

            switch (main_choice) {
            case 1: {
                int customer_choice;
                do {
                    std::cout << "\nМеню клиентов:\n";
                    std::cout << "1. Регистрация\n";
                    std::cout << "2. Авторизация\n";
                    std::cout << "3. Назад\n";
                    std::cout << "Выберите действие: ";
                    std::cin >> customer_choice;
                    std::cin.ignore();

                    switch (customer_choice) {
                    case 1: {
                        Customer newCustomer;
                        std::cout << "Введите имя пользователя: ";
                        std::getline(std::cin, newCustomer.username);
                        std::cout << "Введите пароль: ";
                        std::getline(std::cin, newCustomer.password);
                        // Запросите другие персональные данные

                        if (customerManager.registerCustomer(newCustomer)) {
                            std::cout << "Регистрация прошла успешно!\n";
                        }
                        break;
                    }
                    case 2: {
                        std::string username, password;
                        std::cout << "Введите имя пользователя: ";
                        std::getline(std::cin, username);
                        std::cout << "Введите пароль: ";
                        std::getline(std::cin, password);

                        if (customerManager.authorizeCustomer(username, password)) {
                            is_authorised = true;
                        }
                        break;
                    }
                    case 3:
                        std::cout << "Возврат в главное меню.\n";
                        break;
                    default:
                        std::cout << "Неверный выбор. Попробуйте снова.\n";
                    }
                } while (customer_choice != 3);
                break;
            }
            case 2: {
                if (is_authorised) {
                    int product_choice;
                    do {
                        std::cout << "\nМеню продуктов:\n";
                        std::cout << "1. Добавить продукт\n";
                        std::cout << "2. Показать все продукты\n";
                        std::cout << "3. Изменить продукт\n";
                        std::cout << "4. Удалить продукт\n";
                        std::cout << "5. Назад\n";
                        std::cout << "Выберите действие: ";
                        std::cin >> product_choice;
                        std::cin.ignore();
                        switch (product_choice) {
                        case 1:
                            addProduct(productManager, readProducts);
                            break;
                        case 2:
                            if (!readProducts.empty()) {
                                for (const auto& product : readProducts) {
                                    std::cout << "Название: " << product.name << std::endl;
                                    std::cout << "Цена: " << product.price << std::endl;
                                    std::cout << "Количество: " << product.quantity << std::endl;
                                    std::cout << "Описание: " << product.description << std::endl;
                                    std::cout << std::endl;
                                }
                            }
                            else {
                                std::cout << "Список товаров пуст." << std::endl;
                            }
                            break;
                        case 3: {
                            std::string productName;
                            std::cout << "Введите название продукта для изменения: ";
                            std::getline(std::cin, productName);

                            Product newProduct;
                            std::cout << "Введите новое название продукта: ";
                            std::getline(std::cin, newProduct.name);
                            std::cout << "Введите новую цену продукта: ";
                            std::cin >> newProduct.price;
                            std::cin.ignore();
                            std::cout << "Введите новое количество продукта: ";
                            std::cin >> newProduct.quantity;
                            std::cin.ignore();
                            std::cout << "Введите новое описание продукта: ";
                            std::getline(std::cin, newProduct.description);

                            if (productManager.updateProduct(productName, newProduct)) {
                                std::cout << "Продукт изменен!" << std::endl;
                                productManager.readProducts(readProducts);
                            }
                            else {
                                std::cout << "Продукт не найден." << std::endl;
                            }
                            break;
                        }
                        case 4: {
                            std::string productName;
                            std::cout << "Введите название продукта для удаления: ";
                            std::getline(std::cin, productName);

                            if (productManager.deleteProduct(productName)) {
                                std::cout << "Продукт удален!" << std::endl;
                                productManager.readProducts(readProducts);
                            }
                            else {
                                std::cout << "Продукт не найден." << std::endl;
                            }
                            break;
                        }
                        case 5:
                            std::cout << "Возврат в главное меню.\n";
                            break;
                        default:
                            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                        }
                    } while (product_choice != 5);
                    break;
                }
                else {
                    std::cout << "Авторизуйтесь\n";
                }
                break;
            }
            case 3: {
                if (is_authorised) {
                    int order_choice;
                    do {
                        std::cout << "\nМеню заказов:\n";
                        std::cout << "1. Добавить заказ\n";
                        std::cout << "2. Изменить статус заказа\n";
                        std::cout << "3. Получить информацию о заказе\n";
                        std::cout << "4. Назад\n";
                        std::cout << "Выберите действие: ";
                        std::cin >> order_choice;
                        std::cin.ignore();

                        switch (order_choice) {
                        case 1: {
                            Order newOrder;
                            std::cout << "Введите адрес доставки: ";
                            std::getline(std::cin, newOrder.deliveryAddress);
                            newOrder.status = "Новый"; // Устанавливаем начальный статус

                            // Добавляем товары в заказ
                            int numProducts;
                            std::cout << "Введите количество товаров в заказе: ";
                            std::cin >> numProducts;
                            std::cin.ignore();

                            for (int i = 0; i < numProducts; ++i) {
                                std::string productName;
                                int quantity;
                                std::cout << "Введите название товара: ";
                                std::getline(std::cin, productName);
                                std::cout << "Введите количество товара: ";
                                std::cin >> quantity;
                                std::cin.ignore();
                                newOrder.products.push_back(std::make_pair(productName, quantity));
                            }

                            if (orderManager.addOrder(newOrder)) {
                                std::cout << "Заказ добавлен успешно!\n";
                                orderManager.readOrders();
                            }
                            break;
                        }
                        case 2: {
                            int orderIndex;
                            std::string newStatus;
                            std::cout << "Введите индекс заказа: ";
                            std::cin >> orderIndex;
                            std::cin.ignore();
                            std::cout << "Введите новый статус: ";
                            std::getline(std::cin, newStatus);

                            if (orderManager.changeOrderStatus(orderIndex - 1, newStatus)) {
                                std::cout << "Статус заказа изменен успешно!\n";
                                orderManager.readOrders();
                            }
                            break;
                        }
                        case 3: {
                            int orderIndex;
                            std::cout << "Введите индекс заказа: ";
                            std::cin >> orderIndex;
                            std::cin.ignore();
                            orderManager.getOrderInfo(orderIndex - 1);
                            break;
                        }
                        case 4:
                            std::cout << "Возврат в главное меню.\n";
                            break;
                        default:
                            std::cout << "Неверный выбор. Попробуйте снова.\n";
                        }
                    } while (order_choice != 4);
                    break;
                }
                else {
                    std::cout << "Авторизуйтесь!!!!\n";
                }
                break;
            }
            case 4: {
                if (is_authorised) {
                    int delivery_choice;
                    do {
                            std::cout << "\nМеню доставки:\n";
                            std::cout << "1. Добавить доставку\n";
                            std::cout << "2. Показать все доставки\n";
                            std::cout << "3. Изменить доставку\n";
                            std::cout << "4. Удалить доставку\n";
                            std::cout << "5. Назад\n";
                            std::cout << "Выберите действие: ";
                            std::cin >> delivery_choice;
                            std::cin.ignore();

                            switch (delivery_choice) {
                            case 1: {
                                Delivery newDelivery;
                                std::cout << "Введите адрес доставки: ";
                                std::getline(std::cin, newDelivery.deliveryAddress);
                                std::cout << "Введите номер заказа: ";
                                std::cin >> newDelivery.orderNumber;
                                std::cin.ignore();
                                std::cout << "Введите стоимость доставки: ";
                                std::cin >> newDelivery.deliveryCost;
                                std::cin.ignore();
                                std::cout << "Выберите способ доставки:\n";
                                std::cout << "1. Standard\n";
                                std::cout << "2. Express\n";
                                std::cout << "3. Pickup\n";
                                int methodChoice;
                                std::cin >> methodChoice;
                                std::cin.ignore();
                                switch (methodChoice) {
                                case 1:
                                    newDelivery.deliveryMethod = DeliveryMethod::Standard;
                                    break;
                                case 2:
                                    newDelivery.deliveryMethod = DeliveryMethod::Express;
                                    break;
                                case 3:
                                    newDelivery.deliveryMethod = DeliveryMethod::Pickup;
                                    break;
                                default:
                                    std::cerr << "Неверный выбор.\n";
                                    break;
                                }
                                if (deliveryManager.addDelivery(newDelivery)) {
                                    std::cout << "Доставка добавлена успешно!\n";
                                } else {
                                    std::cerr << "Ошибка добавления доставки.\n";
                                }
                                break;
                            }
                            case 2: {
                                if (!readDeliveries.empty()) {
                                    for (const auto& delivery : readDeliveries) {
                                        std::cout << "Адрес: " << delivery.deliveryAddress << std::endl;
                                        std::cout << "Номер заказа: " << delivery.orderNumber << std::endl;
                                        std::cout << "Стоимость доставки: " << delivery.deliveryCost << std::endl;
                                        switch (delivery.deliveryMethod) {
                                        case DeliveryMethod::Standard:
                                            std::cout << "Способ доставки: Standard\n";
                                            break;
                                        case DeliveryMethod::Express:
                                            std::cout << "Способ доставки: Express\n";
                                            break;
                                        case DeliveryMethod::Pickup:
                                            std::cout << "Способ доставки: Pickup\n";
                                            break;
                                        }
                                        std::cout << std::endl;
                                    }
                                } else {
                                    std::cout << "Список доставок пуст.\n";
                                }
                                break;
                            }
                            case 3: {
                                int deliveryIndex;
                                std::cout << "Введите индекс доставки для изменения: ";
                                std::cin >> deliveryIndex;
                                std::cin.ignore();
                                if (deliveryIndex >= 0 && deliveryIndex < readDeliveries.size()) {
                                    Delivery& delivery = readDeliveries[deliveryIndex];
                                    std::cout << "Введите новый адрес доставки: ";
                                    std::getline(std::cin, delivery.deliveryAddress);
                                    std::cout << "Выберите способ доставки:\n";
                                    std::cout << "1. Standard\n";
                                    std::cout << "2. Express\n";
                                    std::cout << "3. Pickup\n";
                                    int methodChoice;
                                    std::cin >> methodChoice;
                                    std::cin.ignore();
                                    switch (methodChoice) {
                                    case 1:
                                        delivery.deliveryMethod = DeliveryMethod::Standard;
                                        break;
                                    case 2:
                                        delivery.deliveryMethod = DeliveryMethod::Express;
                                        break;
                                    case 3:
                                        delivery.deliveryMethod = DeliveryMethod::Pickup;
                                        break;
                                    default:
                                        std::cerr << "Неверный выбор.\n";
                                        break;
                                    }
                                    if (deliveryManager.writeDeliveries(readDeliveries)) {
                                        std::cout << "Доставка изменена успешно!\n";
                                    } else {
                                        std::cerr << "Ошибка изменения доставки.\n";
                                    }
                                } else {
                                    std::cerr << "Неверный индекс доставки.\n";
                                }
                                break;
                            }
                            case 4: {
                                int deliveryIndex;
                                std::cout << "Введите индекс доставки для удаления: ";
                                std::cin >> deliveryIndex;
                                std::cin.ignore();
                                if (deliveryIndex >= 0 && deliveryIndex < readDeliveries.size()) {
                                    readDeliveries.erase(readDeliveries.begin() + deliveryIndex);
                                    if (deliveryManager.writeDeliveries(readDeliveries)) {
                                        std::cout << "Доставка удалена успешно!\n";
                                    } else {
                                        std::cerr << "Ошибка удаления доставки.\n";
                                    }
                                } else {
                                    std::cerr << "Неверный индекс доставки.\n";
                                }
                                break;
                            }
                            case 5:
                                std::cout << "Возврат в главное меню.\n";
                                break;
                            default:
                                std::cerr << "Неверный выбор. Попробуйте снова.\n";
                            }
                        } while (delivery_choice != 5);
                } else {
                    std::cout << "Авторизуйтесь!!!!\n";
                }
                break;
                    
            }
            case 5:
                running = false;
                std::cout << "До свидания!\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } while (main_choice != 5);
    }

    return 0;
}
