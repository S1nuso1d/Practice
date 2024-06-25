#include <iostream>
#include <string> 
#include <clocale>
#include <conio.h>

using namespace std;

class SecureData
{
public:
    string getData()
    {
        return "Секретные данные";
    }
};

class SecureDataProxy
{
private:
    SecureData* realData;
    string username;
    string password;

public:
    SecureDataProxy(const string& username, const string& password) :
        realData(nullptr), username(username), password(password) {}

    string getData()
    {
        if (authenticate(username, password))
        {
            if (realData == nullptr)
            {
                realData = new SecureData();
            }
            return realData->getData();
        }
        else
        {
            return "Доступ запрещен.";
        }
    }

private:
    bool authenticate(const string& username, const string& password)
    {
        if (username == "user" && password == "password")
        {
            return true;
        }
        return false;
    }
};

void clearScreen() 
{
    system("cls");
}

int main()
{
    setlocale(LC_ALL, "Ru");

    string User;
    string Password;

    while (true) 
    {
        clearScreen();
        cout << "\t\t  *** Секретные данные ***\n";
        cout << "\t\t___________________________\n";
        cout << "\t\t| 1. Вход                 |\n";
        cout << "\t\t| 2. Выход                |\n";
        cout << "\t\t---------------------------\n";
        cout << "\t\t| Выберите действие: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            cout << "\t\t\t      *** Вход ***\n";
            cout << "\t\t\t_______________________\n";
            cout << "\t\t\t|User:     | ";
            cin >> User;
            cout << "\t\t\t-----------------------\n";
            cout << "\t\t\t|Password: | ";
            cin >> Password;
            cout << "\t\t\t-----------------------\n";

            SecureDataProxy authorizedProxy(User, Password);
            cout << "\t\t\t" << authorizedProxy.getData() << endl;
            cout << "\t\t\tНажмите любую клавишу, чтобы вернуться в меню...";
            _getch();
        }
        else if (choice == 2) {
            cout << "\t\t\tДо свидания!\n";
            break;
        }
        else {
            cout << "\t\t\tНеверный выбор. Попробуйте снова.\n";
            _getch();
        }
    }

    return 0;
}