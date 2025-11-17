#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

void vector_operation() {
    std::vector<float> a;
    float tmpVal;
    std::cout << "Please enter a list of positive numbers, ending with a negative one: " << std::endl;
    for (int i=0; i< 100; i++) {
        std::cin >> tmpVal;
        if (tmpVal < 0) {
            std::cout << "Input finished!" << std::endl;
            break;
        }
        a.push_back(tmpVal);
    }

    std::cout << "Sorting..." << std::endl;

    std::sort(a.begin(), a.end());

    for (float val : a) {
        std::cout << val << std::endl;
    }
}   

void lst_operation() {
    std::list<float> a;
    float tmpVal;
    std::cout << "Please enter a list of positive numbers, ending with a negative one: " << std::endl;
    for (int i=0; i< 100; i++) {
        std::cin >> tmpVal;
        if (tmpVal < 0) {
            std::cout << "Input finished!" << std::endl;
            break;
        }
        a.push_back(tmpVal);
    }

    std::cout << "Sorting..." << std::endl;

    a.sort();

    for (float val : a) {
        std::cout << val << std::endl;
    }
}   

void telephone_map() {
    std::map<std::string, std::string> tele_map;
    tele_map["Dr Doolittle"] = "03402 646257";
    tele_map["Prof Smith"] = "05624 814253";
    tele_map["Mr Hyde"] = "06417 639124";
    tele_map["Dr Jekyll"] = "06417 639124";

    std::string name;
    std::cout << "Enter the name: ";
    std::getline(std::cin, name);

    auto it = tele_map.find(name);
    std::string ans = (it != tele_map.end()) ? it->second : "not found";
    std::cout << "Number: " << ans << std::endl;
}

int main(void) {
    // vector_operation();
    // lst_operation();
    telephone_map();
    return 1;
}