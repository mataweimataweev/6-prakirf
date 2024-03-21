#include <iostream>
#include <Windows.h>
#include <string> 
#include <sstream> 

using namespace std;


class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;
public:
    BankAccount(int accNumber, double initBalance) : accountNumber(accNumber), balance(initBalance), interestRate(0.0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
           cout << "Пополнение прошло успешно. Текущий баланс: " << balance << std::endl;
        }
        else {
            cout << "Недопустимая сумма для внесения депозита!" << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Вывод средств завершен.Текущий баланс : " << balance << std::endl;
        }
        else {
            cout << "Недопустимая сумма для вывода или недостаточно средств!" << std::endl;
        }
    }

    double getBalance() {
        return balance;
    }

    double getInterest() {
        return balance * interestRate * (1 / 12.0);
    }

    void setInterestRate(double newRate) {
        interestRate = newRate;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount <= 0 || amount > from.balance) {
        cout << "Неверная сумма для перевода или недостаточно средств!" << std::endl;
        return false;
    }

    from.balance -= amount;
    to.balance += amount;
    cout << "Перевод выполнен успешно. Текущий баланс отправителя: " << from.balance << " | Текущий баланс получателя: " << to.balance << std::endl;
    return true;
}

int main() {
    setlocale(LC_ALL, "Rus");
    BankAccount acc1(12345, 1000.0);
    BankAccount acc2(67890, 500.0);

    char choice;
    string input; // Используем строку для считывания ввода пользователя
    double amount;

    do {
        cout << "\nВыберите действие:\n1. Депозит\n2. Вывод\n3. Перевод денег\n4. Проверьте баланс\n5. Выход\n";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "Введите сумму для внесения депозита: ";
            cin.ignore(); // Очищаем буфер ввода перед использованием getline
            getline(cin, input);
            try {
                amount = stod(input); // Преобразуем строку в число
                acc1.deposit(amount);
            }
            catch (const invalid_argument& e) {
                cout << "Ошибка: неверный формат ввода!\n";
            }
            break;
        case '2':
            cout << "Введите сумму для вывода: ";
            cin.ignore(); // Очищаем буфер ввода перед использованием getline
            getline(cin, input);
            try {
                amount = stod(input); // Преобразуем строку в число
                acc1.withdraw(amount);
            }
            catch (const invalid_argument& e) {
                cout << "Ошибка: неверный формат ввода!\n";
            }
            break;
        case '3':
            cout << "Введите сумму для перевода: ";
            cin.ignore(); // Очищаем буфер ввода перед использованием getline
            getline(cin, input);
            try {
                amount = stod(input); // Преобразуем строку в число
                transfer(acc1, acc2, amount);
            }
            catch (const invalid_argument& e) {
                cout << "Ошибка: неверный формат ввода!\n";
            }
            break;
        case '4':
            cout << "Текущий баланс: " << acc1.getBalance() << std::endl;
            break;
        case '5':
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, выберите еще раз.\n";
        }
    } while (choice != '5');

    return 0;
}