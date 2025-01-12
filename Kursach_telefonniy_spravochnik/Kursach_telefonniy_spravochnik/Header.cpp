#include "stdafx.h"
#include "Header.h"

void Contact::printContact()
{
    cout << "Name: " << firstName << " " << lastName << " " << middleName << endl;
    cout << "Address: " << address << endl;
    cout << "Date of Birth: " << dateOfBirth << endl;
    cout << "Email: " << email << endl;
    for (const auto& element : phoneNumbers) {
        cout << element.first << " number: " << element.second << endl;
    }
    cout << endl;
}
