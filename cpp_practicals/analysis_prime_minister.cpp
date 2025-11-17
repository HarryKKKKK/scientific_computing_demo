#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

std::vector<std::pair<std::string, std::string>> read_data() {
    std::ifstream DataFile("prime_ministers.txt");

    std::vector<std::pair<std::string, std::string>> prime_ministers;
    
    std::string firstName, lastName;
    while (DataFile >> firstName >> lastName) {
        prime_ministers.emplace_back(firstName, lastName);
    }

    return prime_ministers;
}

template<typename T>
typename std::vector<std::pair<T, T>>::const_iterator find_element(const std::vector<std::pair<T, T>>& vec, const T& target) {
    return std::find_if(vec.begin(), vec.end(), 
        [&target](const std::pair<T, T>& p) {
            return p.first == target; 
        }
    );
}

template<typename T>
int count_element(const std::vector<std::pair<T, T>>& vec, const T& target) {
    return std::count_if(vec.begin(), vec.end(), 
        [&target](const std::pair<T, T>& p) {
            return p.first == target; 
        }
    );
}


int main(void) {
    std::vector<std::pair<std::string, std::string>> prime_ministers = read_data();
    
    std::vector<std::pair<std::string, std::string>>::const_iterator it = find_element(prime_ministers, std::string("George"));
    std::cout << std::distance(prime_ministers.cbegin(), it) << " " << it->first << " " << it->second << std::endl;

    int num = count_element(prime_ministers, std::string("Charles"));
    std::cout << num << std::endl;

    return 1;
}