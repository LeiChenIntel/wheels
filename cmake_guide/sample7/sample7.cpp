
#include <fstream>
#include <iostream>

#include "addressbook.pb.h"

void AddAddress(tutorial::Person* person) {
    std::string name = "Bob";
    int id = 123;
    std::string email = "abc@456.com";
    std::string number1 = "12345678";
    std::string number2 = "87654321";

    person->set_name(name);
    person->set_id(id);
    person->set_email(email);

    tutorial::Person::PhoneNumber* phone_number1 = person->add_phones();
    phone_number1->set_number(number1);
    phone_number1->set_type(tutorial::Person::MOBILE);

    tutorial::Person::PhoneNumber* phone_number2 = person->add_phones();
    phone_number2->set_number(number2);
    phone_number2->set_type(tutorial::Person::HOME);
}

void ListPeople(const tutorial::AddressBook& address_book) {
    std::cout << "Print address book:" << std::endl;
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person& person = address_book.people(i);
        std::cout << "Name: " << person.name() << std::endl;
        std::cout << "ID: " << person.id() << std::endl;
        std::cout << "Email: " << person.email() << std::endl;
        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);
            std::cout << "Phone " << j + 1 << ": " << phone_number.number();
            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    std::cout << " MOBILE" << std::endl;
                    break;
                case tutorial::Person::HOME:
                    std::cout << " HOME" << std::endl;
                    break;
                case tutorial::Person::WORK:
                    std::cout << " WORK" << std::endl;
                    break;
            }
        }
    }
}

// TODO: Add revise and remove operation.

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::AddressBook address_book;

    std::fstream input(argv[1], std::ios::in | std::ios::binary);
    if (!input) {
        std::cout << "Create new address book." << std::endl;
    } else if (!address_book.ParseFromIstream(&input)) {
        std::cout << "Failed to parse address book." << std::endl;
        return -1;
    }
    input.close();

    AddAddress(address_book.add_people());
    ListPeople(address_book);

    std::fstream output(argv[1], std::ios::out | std::ios::trunc | std::ios::binary);
    if (!address_book.SerializeToOstream(&output)) {
        std::cout << "Failed to write address book." << std::endl;
        return -1;
    }
    output.close();

    // Optioanal: Delete global objects allocated by libprotobuf
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}