#include "stdafx.h"
#include "Header.h"

// Функция для удаления пробелов в начале строки  
string trimLeadingSpaces(const string& str) {
    size_t start = str.find_first_not_of(' '); // Находим первый символ, не являющийся пробелом  
    if (start == string::npos) {
        // Если строка состоит только из пробелов, возвращаем пустую строку  
        return "";
    }
    return str.substr(start); // Возвращаем подстроку без начальных пробелов  
}

// Функция для удаления пробелов в конце строки  
string trimTrailingSpaces(const string& str) {
    size_t end = str.find_last_not_of(' '); // Находим последний символ, не являющийся пробелом  
    if (end == string::npos) {
        // Если строка состоит только из пробелов, возвращаем пустую строку  
        return "";
    }
    return str.substr(0, end + 1); // Возвращаем подстроку без конечных пробелов  
}

// Функция проверки введённых имени, фамилии, отчества
bool checkString(const string& inputString) {
    trimLeadingSpaces(inputString);
    trimTrailingSpaces(inputString);
    if (inputString == "") {
        cout << "Пустая строка\n";
        return 0;
    }

    bool onlyAlphaAndDash = true;
    bool isFirstUpper = false;
    bool isLastDash = false;

    // Проверяем, состоит ли строка только из букв и дефисов  
    for (char c : inputString) {
        if (!isalpha(c) and c != '-') {
            onlyAlphaAndDash = false;
            break;
        }
    }

    // Проверяем, является ли первый символ строки буквой в верхнем регистре  
    if (isalpha(inputString[0]) and isupper(inputString[0])) {
        isFirstUpper = true;
    }

    // Проверяем, является ли последний символ строки дефисом  
    if (inputString.back() == '-') {
        isLastDash = true;
    }

    // Выводим результаты проверок  
    if (onlyAlphaAndDash == false){
        cout << "Строка содержит другие символы помимо латинских букв и дефисов" << endl << endl;
    }

    if (isFirstUpper == false){
        cout << "Первый символ строки не является латинской буквой в верхнем регистре" << endl << endl;
    }

    if (isLastDash == true) {
        cout << "Последний символ строки является дефисом" << endl << endl;
    }
    
    //Возвращаем результат функции
    if (onlyAlphaAndDash and isFirstUpper and !isLastDash) {
        return 1;
    }
    else
        return 0;
}

// Функция проверки введённого email
bool emailCheck(const string& inputString, const string& inputName) {

    //Удаление лишних пробелов и проверка на пустую строку.
    trimLeadingSpaces(inputString);
    trimTrailingSpaces(inputString);
    if (inputString == "") {
        cout << "Пустая строка\n";
        return 0;
    }

    bool onlyAlphaAndDigit = true;
    bool isAtSigned = false;
    bool isNameIn = true;

    //Проверяем, состоит ли строка только из букв, цифр, собаки и точки
    for (char c : inputString) {
        if (!isalpha(c) and !isdigit(c) and c != '@' and c != '.') {
            onlyAlphaAndDigit = false;
            break;
        }
    }

    //Проверяем на наличие собаки '@' в строке
    for (char c : inputString) {
        if (c == '@') {
            isAtSigned = true;
            break;
        }
    }

    //Проверяем есть ли в email имя пользователя
    if (inputString.find(inputName) == string::npos) {
        isNameIn = false;
    }

    //Выводим результаты проверок
    if (onlyAlphaAndDigit == false) {
        cout << "Строка содержит другие символы помимо букв, цифр и собаки" << endl << endl;
    }

    if (isAtSigned == false) {
        cout << "Строка не содержит символа собаки" << endl << endl;
    }
    
    if (isNameIn == false) {
        cout << "Email не содержит имя пользователя" << endl << endl;
    }

    //Возвращаем результат функции
    if (onlyAlphaAndDigit and isAtSigned and isNameIn) {
        return 1;
    }
    else
        return 0;
}

// Проверка на високосный год
bool isLeapYear(int year) {
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0);
}

// Проверка введённой даты рождения
bool isValidDate(const string& dateStr) {
    int day, month, year;

    // Разделение строки на компоненты
    char delimiter;
    istringstream dateStream(dateStr);
    if (!(dateStream >> day >> delimiter >> month >> delimiter >> year)) {
        return false;
    }

    // Проверка формата
    if (delimiter != '/') {
        return false;
    }

    // Проверка диапазонов
    if (year < 1 or month < 1 or month > 12 or day < 1 or day > 31) {
        return false;
    }

    // Проверка количества дней в месяце
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // Февраль в високосный год
    }
    if (day > daysInMonth[month - 1]) {
        return false;
    }

    // Проверка на будущее время
    time_t t = time(nullptr);
    tm* currentTime = localtime(&t);

    int currentYear = 1900 + currentTime->tm_year;
    int currentMonth = 1 + currentTime->tm_mon;
    int currentDay = currentTime->tm_mday;

    if (year > currentYear or
        (year == currentYear and month > currentMonth) or
        (year == currentYear and month == currentMonth and day >= currentDay)) {
        return false;
    }

    return true;
}

// Проверка введённого номера телефона
bool isValidPhoneNumber(const string& phoneNumber) {
    // Проверка длины строки
    if (phoneNumber.length() != 12) {
        return false;
    }

    // Проверка на знак "+" в начале строки
    if (phoneNumber[0] != '+') {
        return false;
    }

    // Проверка, что остальные символы являются цифрами
    for (size_t i = 1; i < phoneNumber.length(); ++i) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }

    return true;
}

// Редактирование контакта
void updateContact(map<string, Contact>& phoneBook, const string& key) {
    
    auto it = phoneBook.find(key);
    if (it == phoneBook.end()) {
        cout << "Контакт с таким ключом не найден.\n";
    }
    else {
        Contact& contact = it->second;
        bool flag = 1;
        while (flag) {
            string input;
            cout << "Введите новое имя (оставьте пустым, чтобы не изменять): ";
            getline(cin, input);
            getline(cin, input);
            if (!input.empty()) {
                contact.firstName = input;
            }
            else if (checkString(contact.firstName) == false) {
                break;
            }

            cout << "Введите новую фамилию (оставьте пустым, чтобы не изменять): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.lastName = input;
            }
            else if (checkString(contact.lastName) == false) {
                break;
            }

            cout << "Введите новое отчество (оставьте пустым, чтобы не изменять): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.middleName = input;
            }
            else if (checkString(contact.middleName) == false) {
                break;
            }

            cout << "Введите новый адрес (оставьте пустым, чтобы не изменять): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.address = input;
            }

            cout << "Введите новую дату рождения (оставьте пустым, чтобы не изменять): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.dateOfBirth = input;
            }
            else if (!isValidDate(contact.dateOfBirth)) {
                cout << "Неправильно введена дата рождения.\n----------------------\n";
                break;
            }

            cout << "Введите новый email (оставьте пустым, чтобы не изменять): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.email = input;
            }
            else if (emailCheck(contact.email, contact.firstName) == false) {
                break;
            }

            cout << "Хотите обновить номера телефонов? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                contact.phoneNumbers.clear();
                while (true) {
                    string label, number;
                    cout << "Введите тип телефона ( 'Home','Work','Cell'; чтобы закончить добавлять номера введите 'q'): ";
                    getline(cin, label);
                    if (label == "q") break;
                    if (label.empty()) continue;
                    else if (label != "Home" and label != "Work" and label != "Cell") {
                        cout << "Такого типа нет.\n----------------------\n";
                        continue;
                    }

                    cout << "Введите номер телефона: ";
                    getline(cin, number);
                    if (!isValidPhoneNumber(number)) {
                        cout << "Неправильно введён номер телефона.\n----------------------\n";
                        continue;
                    }
                    contact.phoneNumbers[label] = number;
                }
            }
            flag = 0;
        }
        

        // Очистка файла
        ofstream ofs;
        ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
        ofs.close();

        // Открываем файл
        fstream file("contacts.txt", ios::in | ios::out | ios::app);

        // При ошибке открытия
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла." << endl;
        }
        // Сохраняем данные в файл  
        for (const auto& element : phoneBook) {
            file << element.first << endl;
            file << element.second.firstName << endl;
            file << element.second.lastName << endl;
            file << element.second.middleName << endl;
            file << element.second.address << endl;
            file << element.second.dateOfBirth << endl;
            file << element.second.email << endl;
            for (const auto& element1 : element.second.phoneNumbers) {
                file << element1.first + " номер: " + element1.second << endl;
            }
            file << "-=-=-=-=-=-=-=-=-=-=-=-" << endl;
        }
        file.close();

        cout << "Контакт обновлён.\n";
    }
}

// Сортировка контактов
void sortAndDisplayContacts(map<string, Contact>& phoneBook) {
    cout << "Выберите поле для сортировки:\n";
    cout << "1) Фамилия\n2) Имя\n3) Отчество\n4) Email\n";
    int fieldChoice;
    cin >> fieldChoice;

    vector<Contact> contacts;
    for (const auto& element : phoneBook) {
        contacts.push_back(element.second);
    }

    // Выполняем сортировку в зависимости от выбора
    sort(contacts.begin(), contacts.end(), [fieldChoice](const Contact& a, const Contact& b) {
        switch (fieldChoice) {
        case 1: return a.lastName < b.lastName;
        case 2: return a.firstName < b.firstName;
        case 3: return a.middleName < b.middleName;
        case 4: return a.email < b.email;
        default: return true;
        }
        });

    // Выводим отсортированные контакты
    for (auto& contact : contacts) {
        contact.printContact();
    }
}

// Функция для поиска контактов
void searchContacts(map<string, Contact>& phoneBook) {
    cout << "Выберите поле для поиска:\n";
    cout << "1) Фамилия\n2) Имя\n3) Отчество\n4) Email\n5) Номер телефона\n";
    int fieldChoice;
    cin >> fieldChoice;

    cout << "Введите значение для поиска: ";
    string searchValue;
    cin.ignore();
    getline(cin, searchValue);

    vector<Contact> foundContacts;

    // Ищем контакты в зависимости от выбора поля
    for (const auto& element : phoneBook) {
        switch (fieldChoice) {
        case 1:
            if (element.second.lastName == searchValue) foundContacts.push_back(element.second);
            break;
        case 2:
            if (element.second.firstName == searchValue) foundContacts.push_back(element.second);
            break;
        case 3:
            if (element.second.middleName == searchValue) foundContacts.push_back(element.second);
            break;
        case 4:
            if (element.second.email == searchValue) foundContacts.push_back(element.second);
            break;
        case 5:
            for (const auto& element1 : element.second.phoneNumbers) {
                if (element1.second == searchValue) {
                    foundContacts.push_back(element.second);
                    break;
                }
            }
            break;
        default:
            cout << "Неверный выбор поля.\n";
            return;
        }
    }

    // Выводим найденные контакты
    if (foundContacts.empty()) {
        cout << "Контакт(ы) не найден(ы).\n";
    }
    else {
        for (auto& contact : foundContacts) {
            contact.printContact();
        }
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main() {
    setlocale(LC_ALL, "RUS");

    // Создание телефонной книжки
    map<string, Contact> phoneBook;
    int flag = 1;

    // Предверительная отчистка файла 
    ofstream ofs;
    ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    while (flag)
    {
        cout << "\tВыбирете действие:\n1)Покинуть программу\n2)Показать телефонную книжку\n3)Добавить контакт в телефонную книжку\n\
4)Удалить контакт\n5)Удалить все контакты\n6)Редактировать контакт\n7)Сортировать контакты\n8)Поиск контакт(а/ов)\n\n";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:// Покинуть программу
        {
            cout << "----------------------\nПока!\n----------------------";
            flag = 0;
            break;
        }
        case 2:// Показать телефонную книжку
        {
            cout << "----------------------\n";

            // ЧТЕНИЕ ИЗ ФАЙЛА
            //string line;
            //ifstream in("contacts.txt");  // окрываем файл для чтения
            //if (in.is_open()) {
            //    while (getline(in, line)) {
            //        cout << line << endl;// построчно считаваем
            //    }
            //}
            //in.close();  // закрываем файл
            

            // ЧТЕНИ ИЗ PHONEBOOK
            if (phoneBook.size() > 0) {
                for (auto& contact : phoneBook) {
                    contact.second.printContact();
                }
            }
            else
                cout << "Телефонная книга пуста" << endl;
            cout << "----------------------\n";
            break;
        }
        case 3:// Добавить контакт в телефонную книжку
        {
            cout << "----------------------\n";
            Contact contact1;
            string firstName;
            string lastName;
            string middleName;
            string address;
            string dateOfBirth;
            string email;
            map<string, string> phoneNumbers;

            cout << "Введите имя: ";
            cin >> firstName;
            if (checkString(firstName) == false) {
                break;
            }

            cout << "Введите фамилию: ";
            cin >> lastName;
            if (checkString(lastName) == false) {
                break;
            }

            cout << "Введите отчество: ";
            cin >> middleName;
            if (checkString(middleName) == false) {
                break;
            }

            cout << "Введите адрес( пример: '1-ya/Utinaya/19' ): ";
            cin >> address;


            cout << "Введите дату рождения( пример: '17/01/2005' ): ";
            cin >> dateOfBirth;
            if (!isValidDate(dateOfBirth)) {
                cout << "Неправильно введена дата рождения.\n----------------------\n";
                break;
            }

            cout << "Введите email: ";
            cin >> email;
            if (emailCheck(email, firstName) == false) {
                break;
            }

            int amount;
            cout << "Сколько номеров вы хотите добавить? ( маскимум 100 ): ";
            cin >> amount;
            if (amount >= 100) {
                cout << "Нельзя добавить столько номеров.\n----------------------\n";
                break;
            }

            for (int i = 0; i < amount; i++) {
                string tempType;
                string tempNumber;
                cout << "Введите тип номера телефона ( 'Home','Work','Cell' ): ";
                cin >> tempType;
                if (tempType != "Home" and tempType != "Work" and tempType != "Cell") {
                    cout << "Такого типа нет.\n----------------------\n";
                    amount += 1;
                    continue;
                }
                cout << "Введите номер телефона ( пример: '+79225757257' ): ";
                cin >> tempNumber;
                if (!isValidPhoneNumber(tempNumber)) {
                    cout << "Неправильно введён номер телефона.\n----------------------\n";
                    amount += 1;
                    continue;
                }

                phoneNumbers[tempType] = tempNumber;
            }
            contact1.firstName = firstName;
            contact1.lastName = lastName;
            contact1.middleName = middleName;
            contact1.address = address;
            contact1.dateOfBirth = dateOfBirth;
            contact1.email = email;
            contact1.phoneNumbers.insert(phoneNumbers.begin(), phoneNumbers.end());
            phoneBook[firstName + "+" + middleName] = contact1;

            // Очистка файла
            ofstream ofs;
            ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
            ofs.close();

            // Открываем файл
            fstream file("contacts.txt", ios::in | ios::out | ios::app);

            // При ошибке открытия
            if (!file.is_open()) {
                cerr << "Ошибка открытия файла." << endl;
            }

            // Сохраняем данные в файл  
            for (const auto& element : phoneBook) {
                file << element.first << endl;
                file << element.second.firstName << endl;
                file << element.second.lastName << endl;
                file << element.second.middleName << endl;
                file << element.second.address << endl;
                file << element.second.dateOfBirth << endl;
                file << element.second.email << endl;
                for (const auto& element1 : element.second.phoneNumbers) {
                    file << element1.first + " номер: " + element1.second << endl;
                }
                file << "-=-=-=-=-=-=-=-=-=-=-=-" << endl;
            }
            file.close();
            cout << "\nКонтакт успешно добавлен!\n----------------------\n";
            break;
        }
        case 4:// Удалить контакт
        {
            cout << "----------------------\n";

            cout << "Введите имя и отчество контакта ( first name + '+' + middle name ): ";
            string str;
            cin >> str;
            string kill_str = str;

            int i = 0;
            for (auto& element : phoneBook)
            {
                if (element.first == str)
                {
                    phoneBook.erase(kill_str);

                    // Очистка файла
                    ofstream ofs;
                    ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
                    ofs.close();

                    // Открываем файл
                    fstream file("contacts.txt", ios::in | ios::out | ios::app);

                    // При ошибке открытия
                    if (!file.is_open()) {
                        cerr << "Ошибка открытия файла." << endl;
                        return 1;
                    }
                    // Сохраняем данные в файл  
                    for (const auto& element : phoneBook) {
                        file << element.first << endl;
                        file << element.second.firstName << endl;
                        file << element.second.lastName << endl;
                        file << element.second.middleName << endl;
                        file << element.second.address << endl;
                        file << element.second.dateOfBirth << endl;
                        file << element.second.email << endl;
                        for (const auto& element1 : element.second.phoneNumbers) {
                            file << element1.first + " number: " + element1.second << endl;
                        }
                        file << "-=-=-=-=-=-=-=-=-=-=-=-" << endl;
                    }
                    file.close();

                    cout << "Done.\n----------------------\n";
                    i += 1;
                    break;
                }
            }
            if (i == 0)
                cout << "В телефонной книжке нет такого контакта.\n----------------------\n";
            break;
        }
        case 5:// Удалить все контакты
        {
            cout << "----------------------\n";
            //Очистка map
            phoneBook.clear();

            // Очистка файла
            ofstream ofs;
            ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
            ofs.close();
            
            cout << "Сделано.\n----------------------\n";
            break;
        }
        case 6:// Редактировать контакт
        {
            cout << "----------------------\n";
            if (phoneBook.size() > 0) {
                string key;
                cout << "Введите имя и отчество контакта ( first name + '+' + middle name ): ";
                cin >> key;

                updateContact(phoneBook, key);
            }
            else
                cout << "Добавьте в телефонную книжку контант(ы) чтобы редактировать их";
            cout << "\n----------------------\n";
            break;
        }
        case 7:// Сортировать контакты
        {
            if (phoneBook.size() > 1) {
                cout << "----------------------\n";
                sortAndDisplayContacts(phoneBook);

                cout << "\n----------------------\n";
                break;
            }
            else{
                cout << "Недостаточно контактов для сортировки.\n";
                break;
            }
        }
        case 8:// Поиск контакта(ов)
        {
            cout << "----------------------\n";
            searchContacts(phoneBook);

            cout << "\n----------------------\n";
            break;
        }
        default:
            cout << "----------------------\nНеправильный выбор! Попробуйте ещё раз...\n----------------------\n";
            break;
        }
    }

    return 0;
}