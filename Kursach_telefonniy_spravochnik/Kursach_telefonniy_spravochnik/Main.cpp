#include "stdafx.h"
#include "Header.h"

// ������� ��� �������� �������� � ������ ������  
string trimLeadingSpaces(const string& str) {
    size_t start = str.find_first_not_of(' '); // ������� ������ ������, �� ���������� ��������  
    if (start == string::npos) {
        // ���� ������ ������� ������ �� ��������, ���������� ������ ������  
        return "";
    }
    return str.substr(start); // ���������� ��������� ��� ��������� ��������  
}

// ������� ��� �������� �������� � ����� ������  
string trimTrailingSpaces(const string& str) {
    size_t end = str.find_last_not_of(' '); // ������� ��������� ������, �� ���������� ��������  
    if (end == string::npos) {
        // ���� ������ ������� ������ �� ��������, ���������� ������ ������  
        return "";
    }
    return str.substr(0, end + 1); // ���������� ��������� ��� �������� ��������  
}

// ������� �������� �������� �����, �������, ��������
bool checkString(const string& inputString) {
    trimLeadingSpaces(inputString);
    trimTrailingSpaces(inputString);
    if (inputString == "") {
        cout << "������ ������\n";
        return 0;
    }

    bool onlyAlphaAndDash = true;
    bool isFirstUpper = false;
    bool isLastDash = false;

    // ���������, ������� �� ������ ������ �� ���� � �������  
    for (char c : inputString) {
        if (!isalpha(c) and c != '-') {
            onlyAlphaAndDash = false;
            break;
        }
    }

    // ���������, �������� �� ������ ������ ������ ������ � ������� ��������  
    if (isalpha(inputString[0]) and isupper(inputString[0])) {
        isFirstUpper = true;
    }

    // ���������, �������� �� ��������� ������ ������ �������  
    if (inputString.back() == '-') {
        isLastDash = true;
    }

    // ������� ���������� ��������  
    if (onlyAlphaAndDash == false){
        cout << "������ �������� ������ ������� ������ ��������� ���� � �������" << endl << endl;
    }

    if (isFirstUpper == false){
        cout << "������ ������ ������ �� �������� ��������� ������ � ������� ��������" << endl << endl;
    }

    if (isLastDash == true) {
        cout << "��������� ������ ������ �������� �������" << endl << endl;
    }
    
    //���������� ��������� �������
    if (onlyAlphaAndDash and isFirstUpper and !isLastDash) {
        return 1;
    }
    else
        return 0;
}

// ������� �������� ��������� email
bool emailCheck(const string& inputString, const string& inputName) {

    //�������� ������ �������� � �������� �� ������ ������.
    trimLeadingSpaces(inputString);
    trimTrailingSpaces(inputString);
    if (inputString == "") {
        cout << "������ ������\n";
        return 0;
    }

    bool onlyAlphaAndDigit = true;
    bool isAtSigned = false;
    bool isNameIn = true;

    //���������, ������� �� ������ ������ �� ����, ����, ������ � �����
    for (char c : inputString) {
        if (!isalpha(c) and !isdigit(c) and c != '@' and c != '.') {
            onlyAlphaAndDigit = false;
            break;
        }
    }

    //��������� �� ������� ������ '@' � ������
    for (char c : inputString) {
        if (c == '@') {
            isAtSigned = true;
            break;
        }
    }

    //��������� ���� �� � email ��� ������������
    if (inputString.find(inputName) == string::npos) {
        isNameIn = false;
    }

    //������� ���������� ��������
    if (onlyAlphaAndDigit == false) {
        cout << "������ �������� ������ ������� ������ ����, ���� � ������" << endl << endl;
    }

    if (isAtSigned == false) {
        cout << "������ �� �������� ������� ������" << endl << endl;
    }
    
    if (isNameIn == false) {
        cout << "Email �� �������� ��� ������������" << endl << endl;
    }

    //���������� ��������� �������
    if (onlyAlphaAndDigit and isAtSigned and isNameIn) {
        return 1;
    }
    else
        return 0;
}

// �������� �� ���������� ���
bool isLeapYear(int year) {
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0);
}

// �������� �������� ���� ��������
bool isValidDate(const string& dateStr) {
    int day, month, year;

    // ���������� ������ �� ����������
    char delimiter;
    istringstream dateStream(dateStr);
    if (!(dateStream >> day >> delimiter >> month >> delimiter >> year)) {
        return false;
    }

    // �������� �������
    if (delimiter != '/') {
        return false;
    }

    // �������� ����������
    if (year < 1 or month < 1 or month > 12 or day < 1 or day > 31) {
        return false;
    }

    // �������� ���������� ���� � ������
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // ������� � ���������� ���
    }
    if (day > daysInMonth[month - 1]) {
        return false;
    }

    // �������� �� ������� �����
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

// �������� ��������� ������ ��������
bool isValidPhoneNumber(const string& phoneNumber) {
    // �������� ����� ������
    if (phoneNumber.length() != 12) {
        return false;
    }

    // �������� �� ���� "+" � ������ ������
    if (phoneNumber[0] != '+') {
        return false;
    }

    // ��������, ��� ��������� ������� �������� �������
    for (size_t i = 1; i < phoneNumber.length(); ++i) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }

    return true;
}

// �������������� ��������
void updateContact(map<string, Contact>& phoneBook, const string& key) {
    
    auto it = phoneBook.find(key);
    if (it == phoneBook.end()) {
        cout << "������� � ����� ������ �� ������.\n";
    }
    else {
        Contact& contact = it->second;
        bool flag = 1;
        while (flag) {
            string input;
            cout << "������� ����� ��� (�������� ������, ����� �� ��������): ";
            getline(cin, input);
            getline(cin, input);
            if (!input.empty()) {
                contact.firstName = input;
            }
            else if (checkString(contact.firstName) == false) {
                break;
            }

            cout << "������� ����� ������� (�������� ������, ����� �� ��������): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.lastName = input;
            }
            else if (checkString(contact.lastName) == false) {
                break;
            }

            cout << "������� ����� �������� (�������� ������, ����� �� ��������): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.middleName = input;
            }
            else if (checkString(contact.middleName) == false) {
                break;
            }

            cout << "������� ����� ����� (�������� ������, ����� �� ��������): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.address = input;
            }

            cout << "������� ����� ���� �������� (�������� ������, ����� �� ��������): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.dateOfBirth = input;
            }
            else if (!isValidDate(contact.dateOfBirth)) {
                cout << "����������� ������� ���� ��������.\n----------------------\n";
                break;
            }

            cout << "������� ����� email (�������� ������, ����� �� ��������): ";
            getline(cin, input);
            if (!input.empty()) {
                contact.email = input;
            }
            else if (emailCheck(contact.email, contact.firstName) == false) {
                break;
            }

            cout << "������ �������� ������ ���������? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                contact.phoneNumbers.clear();
                while (true) {
                    string label, number;
                    cout << "������� ��� �������� ( 'Home','Work','Cell'; ����� ��������� ��������� ������ ������� 'q'): ";
                    getline(cin, label);
                    if (label == "q") break;
                    if (label.empty()) continue;
                    else if (label != "Home" and label != "Work" and label != "Cell") {
                        cout << "������ ���� ���.\n----------------------\n";
                        continue;
                    }

                    cout << "������� ����� ��������: ";
                    getline(cin, number);
                    if (!isValidPhoneNumber(number)) {
                        cout << "����������� ����� ����� ��������.\n----------------------\n";
                        continue;
                    }
                    contact.phoneNumbers[label] = number;
                }
            }
            flag = 0;
        }
        

        // ������� �����
        ofstream ofs;
        ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
        ofs.close();

        // ��������� ����
        fstream file("contacts.txt", ios::in | ios::out | ios::app);

        // ��� ������ ��������
        if (!file.is_open()) {
            cerr << "������ �������� �����." << endl;
        }
        // ��������� ������ � ����  
        for (const auto& element : phoneBook) {
            file << element.first << endl;
            file << element.second.firstName << endl;
            file << element.second.lastName << endl;
            file << element.second.middleName << endl;
            file << element.second.address << endl;
            file << element.second.dateOfBirth << endl;
            file << element.second.email << endl;
            for (const auto& element1 : element.second.phoneNumbers) {
                file << element1.first + " �����: " + element1.second << endl;
            }
            file << "-=-=-=-=-=-=-=-=-=-=-=-" << endl;
        }
        file.close();

        cout << "������� �������.\n";
    }
}

// ���������� ���������
void sortAndDisplayContacts(map<string, Contact>& phoneBook) {
    cout << "�������� ���� ��� ����������:\n";
    cout << "1) �������\n2) ���\n3) ��������\n4) Email\n";
    int fieldChoice;
    cin >> fieldChoice;

    vector<Contact> contacts;
    for (const auto& element : phoneBook) {
        contacts.push_back(element.second);
    }

    // ��������� ���������� � ����������� �� ������
    sort(contacts.begin(), contacts.end(), [fieldChoice](const Contact& a, const Contact& b) {
        switch (fieldChoice) {
        case 1: return a.lastName < b.lastName;
        case 2: return a.firstName < b.firstName;
        case 3: return a.middleName < b.middleName;
        case 4: return a.email < b.email;
        default: return true;
        }
        });

    // ������� ��������������� ��������
    for (auto& contact : contacts) {
        contact.printContact();
    }
}

// ������� ��� ������ ���������
void searchContacts(map<string, Contact>& phoneBook) {
    cout << "�������� ���� ��� ������:\n";
    cout << "1) �������\n2) ���\n3) ��������\n4) Email\n5) ����� ��������\n";
    int fieldChoice;
    cin >> fieldChoice;

    cout << "������� �������� ��� ������: ";
    string searchValue;
    cin.ignore();
    getline(cin, searchValue);

    vector<Contact> foundContacts;

    // ���� �������� � ����������� �� ������ ����
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
            cout << "�������� ����� ����.\n";
            return;
        }
    }

    // ������� ��������� ��������
    if (foundContacts.empty()) {
        cout << "�������(�) �� ������(�).\n";
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

    // �������� ���������� ������
    map<string, Contact> phoneBook;
    int flag = 1;

    // ��������������� �������� ����� 
    ofstream ofs;
    ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    while (flag)
    {
        cout << "\t�������� ��������:\n1)�������� ���������\n2)�������� ���������� ������\n3)�������� ������� � ���������� ������\n\
4)������� �������\n5)������� ��� ��������\n6)������������� �������\n7)����������� ��������\n8)����� �������(�/��)\n\n";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:// �������� ���������
        {
            cout << "----------------------\n����!\n----------------------";
            flag = 0;
            break;
        }
        case 2:// �������� ���������� ������
        {
            cout << "----------------------\n";

            // ������ �� �����
            //string line;
            //ifstream in("contacts.txt");  // �������� ���� ��� ������
            //if (in.is_open()) {
            //    while (getline(in, line)) {
            //        cout << line << endl;// ��������� ���������
            //    }
            //}
            //in.close();  // ��������� ����
            

            // ����� �� PHONEBOOK
            if (phoneBook.size() > 0) {
                for (auto& contact : phoneBook) {
                    contact.second.printContact();
                }
            }
            else
                cout << "���������� ����� �����" << endl;
            cout << "----------------------\n";
            break;
        }
        case 3:// �������� ������� � ���������� ������
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

            cout << "������� ���: ";
            cin >> firstName;
            if (checkString(firstName) == false) {
                break;
            }

            cout << "������� �������: ";
            cin >> lastName;
            if (checkString(lastName) == false) {
                break;
            }

            cout << "������� ��������: ";
            cin >> middleName;
            if (checkString(middleName) == false) {
                break;
            }

            cout << "������� �����( ������: '1-ya/Utinaya/19' ): ";
            cin >> address;


            cout << "������� ���� ��������( ������: '17/01/2005' ): ";
            cin >> dateOfBirth;
            if (!isValidDate(dateOfBirth)) {
                cout << "����������� ������� ���� ��������.\n----------------------\n";
                break;
            }

            cout << "������� email: ";
            cin >> email;
            if (emailCheck(email, firstName) == false) {
                break;
            }

            int amount;
            cout << "������� ������� �� ������ ��������? ( �������� 100 ): ";
            cin >> amount;
            if (amount >= 100) {
                cout << "������ �������� ������� �������.\n----------------------\n";
                break;
            }

            for (int i = 0; i < amount; i++) {
                string tempType;
                string tempNumber;
                cout << "������� ��� ������ �������� ( 'Home','Work','Cell' ): ";
                cin >> tempType;
                if (tempType != "Home" and tempType != "Work" and tempType != "Cell") {
                    cout << "������ ���� ���.\n----------------------\n";
                    amount += 1;
                    continue;
                }
                cout << "������� ����� �������� ( ������: '+79225757257' ): ";
                cin >> tempNumber;
                if (!isValidPhoneNumber(tempNumber)) {
                    cout << "����������� ����� ����� ��������.\n----------------------\n";
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

            // ������� �����
            ofstream ofs;
            ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
            ofs.close();

            // ��������� ����
            fstream file("contacts.txt", ios::in | ios::out | ios::app);

            // ��� ������ ��������
            if (!file.is_open()) {
                cerr << "������ �������� �����." << endl;
            }

            // ��������� ������ � ����  
            for (const auto& element : phoneBook) {
                file << element.first << endl;
                file << element.second.firstName << endl;
                file << element.second.lastName << endl;
                file << element.second.middleName << endl;
                file << element.second.address << endl;
                file << element.second.dateOfBirth << endl;
                file << element.second.email << endl;
                for (const auto& element1 : element.second.phoneNumbers) {
                    file << element1.first + " �����: " + element1.second << endl;
                }
                file << "-=-=-=-=-=-=-=-=-=-=-=-" << endl;
            }
            file.close();
            cout << "\n������� ������� ��������!\n----------------------\n";
            break;
        }
        case 4:// ������� �������
        {
            cout << "----------------------\n";

            cout << "������� ��� � �������� �������� ( first name + '+' + middle name ): ";
            string str;
            cin >> str;
            string kill_str = str;

            int i = 0;
            for (auto& element : phoneBook)
            {
                if (element.first == str)
                {
                    phoneBook.erase(kill_str);

                    // ������� �����
                    ofstream ofs;
                    ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
                    ofs.close();

                    // ��������� ����
                    fstream file("contacts.txt", ios::in | ios::out | ios::app);

                    // ��� ������ ��������
                    if (!file.is_open()) {
                        cerr << "������ �������� �����." << endl;
                        return 1;
                    }
                    // ��������� ������ � ����  
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
                cout << "� ���������� ������ ��� ������ ��������.\n----------------------\n";
            break;
        }
        case 5:// ������� ��� ��������
        {
            cout << "----------------------\n";
            //������� map
            phoneBook.clear();

            // ������� �����
            ofstream ofs;
            ofs.open("contacts.txt", ofstream::out | ofstream::trunc);
            ofs.close();
            
            cout << "�������.\n----------------------\n";
            break;
        }
        case 6:// ������������� �������
        {
            cout << "----------------------\n";
            if (phoneBook.size() > 0) {
                string key;
                cout << "������� ��� � �������� �������� ( first name + '+' + middle name ): ";
                cin >> key;

                updateContact(phoneBook, key);
            }
            else
                cout << "�������� � ���������� ������ �������(�) ����� ������������� ��";
            cout << "\n----------------------\n";
            break;
        }
        case 7:// ����������� ��������
        {
            if (phoneBook.size() > 1) {
                cout << "----------------------\n";
                sortAndDisplayContacts(phoneBook);

                cout << "\n----------------------\n";
                break;
            }
            else{
                cout << "������������ ��������� ��� ����������.\n";
                break;
            }
        }
        case 8:// ����� ��������(��)
        {
            cout << "----------------------\n";
            searchContacts(phoneBook);

            cout << "\n----------------------\n";
            break;
        }
        default:
            cout << "----------------------\n������������ �����! ���������� ��� ���...\n----------------------\n";
            break;
        }
    }

    return 0;
}