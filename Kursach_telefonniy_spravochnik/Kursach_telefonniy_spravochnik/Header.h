#pragma once

class Contact {
public:
    string firstName;
    string lastName;
    string middleName;
    string address;
    string dateOfBirth;
    string email;
    map<string, string> phoneNumbers;

    void printContact();
};