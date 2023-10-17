#include <iostream>
#include <ctime>

int main(){
    int oilKm, oilYear, plugKm, beltKm, beltYear, currentKm, currentYear;

    currentYear = 1970 + time(NULL)/31537970;

    std::cout << "Input your current mileage: ";
    std::cin >> currentKm;

    std::cout << "Input your last oil change mileage: ";
    std::cin >> oilKm;
    std::cout << "Input your last oil change year: ";
    std::cin >> oilYear;

    std::cout << "Input your last spark plug replacement mileage: ";
    std::cin >> plugKm;

    std::cout << "Input your last timing belt replacement mileage: ";
    std::cin >> beltKm;
    std::cout << "Input your last timing belt replacement year: ";
    std::cin >> beltYear;

    std::cout << std::endl << "Your maintenance activities:" << std::endl;

    std::cout << "Oil change: ";
    int oilYearDiff = currentYear - oilYear;
    int oilKmDiff = currentKm - oilKm;
    if(oilYearDiff >= 2 or oilKmDiff >= 30000 ){
        if(oilYearDiff >= 3 or oilKmDiff >= 30000 * 1.2){
            std::cout << "Urgent! ";
        }
        std::cout << "Needed";
    }
    else{
        std::cout << "Not needed";
    }
    std::cout << std::endl;

    std::cout << "Spark plug change: ";
    int plugKmDiff = currentKm - plugKm;
    if(plugKmDiff >= 50000){
        if(plugKmDiff >= 50000 * 1.2){
            std::cout << "Urgent! ";
        }
        std::cout << "Needed";
    }
    else{
        std::cout << "Not needed";
    }
    std::cout << std::endl;

    std::cout << "Timing belt: ";
    int beltKmDiff = currentKm - beltKm;
    int beltYearDiff = currentYear - beltYear;
    if(beltYearDiff >= 6 or beltKmDiff >= 100000){
        if(beltYearDiff >= 7 or beltKmDiff >= 100000*1.2){
            std::cout << "Urgent! ";
        }
        std::cout << "Needed";
    }
    else{
        std::cout << "Not needed";
    }
    std::cout << std::endl;

    return 0;
}