#include <iostream>
#include <string>
#include <clocale>
#include <conio.h>

using namespace std;

// Интерфейс для субъекта
class SecureDataSubject 
{
public:
    virtual string getData() = 0;
};

// Реальный объект с секретными данными
class SecureData : public SecureDataSubject 
{
public:
    string getData() override 
    {
        return "Секретные данные";
    }
};

// Заместитель для доступа к секретным данным
class SecureDataProxy : public SecureDataSubject 
{
private:
    SecureDataSubject* realData;
    string username;
    string password;

public:
    SecureDataProxy(const string& username, const string& password) :
        realData(nullptr), username(username), password(password) {}

    string getData() override 
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

// Заместитель для супер-пользователя
class SuperUserProxy : public SecureDataSubject 
{
private:
    SecureDataSubject* realData;
    string username;
    string password;
    string accessKey;

public:
    SuperUserProxy(const string& username, const string& password, const string& accessKey) :
        realData(nullptr), username(username), password(password), accessKey(accessKey) {}

    string getData() override 
    {
        if (authenticate(username, password, accessKey)) 
        {
            if (realData == nullptr) 
            {
                realData = new SecureData();
            }
            return realData->getData() + " (Иван Иванов)"; // Добавлен владелец данных
        }
        else {
            return "Доступ запрещен.";
        }
    }

private:
    bool authenticate(const string& username, const string& password, const string& accessKey) 
    {
        if (username == "superuser" && password == "superpassword" && accessKey == "secretkey") 
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
    string AccessKey;

    while (true) 
    {
        clearScreen();
        cout << "\t\t  *** Секретные данные ***\n";
        cout << "\t\t______________________________\n";
        cout << "\t\t| 1. Вход                    |\n";
        cout << "\t\t| 2. Вход супер-пользователя |\n";
        cout << "\t\t| 3. Выход                   |\n";
        cout << "\t\t------------------------------\n";
        cout << "\t\t| Выберите действие: ";

        int choice;
        cin >> choice;

        if (choice == 1) 
        {
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
        else if (choice == 2) 
        {
            clearScreen();
            cout << "\t\t\t      *** Вход супер-пользователя ***\n";
            cout << "\t\t\t___________________________________________\n";
            cout << "\t\t\t|User:     | ";
            cin >> User;
            cout << "\t\t\t-------------------------------------------\n";
            cout << "\t\t\t|Password: | ";
            cin >> Password;
            cout << "\t\t\t-------------------------------------------\n";
            cout << "\t\t\t|Access Key:| ";
            cin >> AccessKey;
            cout << "\t\t\t-------------------------------------------\n";

            SuperUserProxy superUserProxy(User, Password, AccessKey);
            cout << "\t\t\t" << superUserProxy.getData() << endl;
            cout << "\t\t\tНажмите любую клавишу, чтобы вернуться в меню...";
            _getch();
        }
        else if (choice == 3) 
        {
            cout << "\t\t\tДо свидания!\n";
            break;
        }
        else 
        {
            cout << "\t\t\tНеверный выбор. Попробуйте снова.\n";
            _getch();
        }
    }

    return 0;
}
