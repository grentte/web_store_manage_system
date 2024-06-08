#include "Customer.h"
#include "Products.h"
#include "Order.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::string filename1 = "сustomers.txt";
    std::string filename2 = "products.txt";
    std::string filename3 = "orders.txt";
    CustomerManager customerManager(filename1);
    ProductManager productManager(filename2);
    OrderManager orderManager(filename3, productManager);

    std::vector<Product> readProducts;
    productManager.readProducts(readProducts);
    std::vector<Order> readOrders;

    bool running = true;
    bool is_authorised = false;
    while (running) {
        int main_choice;
        do {
            std::cout << "\nМеню:\n";
            std::cout << "1. Авторизация/регистрация\n";
            std::cout << "2. Товары\n";
            std::cout << "3. Заказы\n";
            std::cout << "4. Выход\n";
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
                        std::cout << "\nМеню товаров:\n";
                        std::cout << "1. Добавить товар\n";
                        std::cout << "2. Показать все товары\n";
                        std::cout << "3. Изменить товар\n";
                        std::cout << "4. Удалить товар\n";
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
                            std::cout << "Введите название товара для изменения: ";
                            std::getline(std::cin, productName);

                            Product newProduct;
                            std::cout << "Введите новое название товара: ";
                            std::getline(std::cin, newProduct.name);
                            std::cout << "Введите новую цену товара: ";
                            std::cin >> newProduct.price;
                            std::cin.ignore();
                            std::cout << "Введите новое количество товара: ";
                            std::cin >> newProduct.quantity;
                            std::cin.ignore();
                            std::cout << "Введите новое описание товара: ";
                            std::getline(std::cin, newProduct.description);

                            if (productManager.updateProduct(productName, newProduct)) {
                                std::cout << "товар изменен!" << std::endl;
                                productManager.readProducts(readProducts);
                            }
                            else {
                                std::cout << "товар не найден." << std::endl;
                            }
                            break;
                        }
                        case 4: {
                            std::string productName;
                            std::cout << "Введите название товара для удаления: ";
                            std::getline(std::cin, productName);

                            if (productManager.deleteProduct(productName)) {
                                std::cout << "товар удален!" << std::endl;
                                productManager.readProducts(readProducts);
                            }
                            else {
                                std::cout << "товар не найден." << std::endl;
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
                        std::cout << "4. Расчитать стоимость заказа\n";
                        std::cout << "5. Назад\n";
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
                        case 4: {
                            int orderIndex;
                            std::cout << "Введите индекс заказа: ";
                            std::cin >> orderIndex;
                            std::cin.ignore();
                            int deliveryChoice;
                            std::cout << "\nВыберите способ доставки: \n";
                            std::cout << "1. Стандартный\n";
                            std::cout << "2. Экспресс\n";
                            std::cout << "3. Самовывоз\n";
                            std::cin >> deliveryChoice;
                            
                            std::cout << orderManager.calculateOrderCost(orderIndex-1, orderManager.chooseDeliveryMethod(deliveryChoice)) << " руб." <<  std::endl;
                            break;
                        }
                        case 5:
                            std::cout << "Возврат в главное меню.\n";
                            break;
                        default:
                            std::cout << "Неверный выбор. Попробуйте снова.\n";
                        }
                    } while (order_choice != 5);
                    break;
                }
                else {
                    std::cout << "Авторизуйтесь!!!!\n";
                }
                break;
            }
            case 4:
                running = false;
                std::cout << "До свидания!\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } while (main_choice != 4);
    }

    return 0;
}
