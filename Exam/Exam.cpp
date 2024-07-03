// Exam.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class RadioDetal
{
public:
    string designation;
    string type;
    string releseDate;
    int quality;
    RadioDetal(const string d, const string& t, const string& r, int q) :
        designation(d), type(t), releseDate(r), quality(q) {}
    void print() const {
        cout << "Обозначение: " << designation << endl
            << "Тип: " << type << endl
            << "Дата выпуска: " << releseDate << endl
            << "Коли-во на схеме устройства: " << quality << endl;
    }
};
void saveToFile(const vector<RadioDetal>& details, const string& filename)
{
    ofstream outFile(filename, ios::out);
    if (!outFile.is_open())
    {
        cerr << "Ошибка открытия файла";
        return;
    }
    for (const auto& detail : details)
    {
        outFile << detail.designation << ", " << detail.type << ", " <<
            detail.releseDate << ", " << detail.quality << ", " << endl;
    }
    outFile.close();
}
void addDetail(std::vector<RadioDetal>& details) {
    std::string d, t, r;
    int q;
    std::cout << "Введите Обозначение: ";
    std::cin >> d;
    std::cout << "Введите Тип: ";
    std::cin >> t;
    std::cout << "Введите дату выпуска(YYYY-MM-DD): ";
    std::cin >> r;
    std::cout << "Введите кол-во: ";
    std::cin >> q;
    details.emplace_back(d, t, r, q);
}
vector<RadioDetal> loadFromFile(const std::string& filename) {
    vector<RadioDetal> details;
    ifstream inFile(filename);
    string line;
    string d, t, r, qStr;
    int q;
    while (getline(inFile, d, ',') && getline(inFile, t, ',')&& getline(inFile, r, ',') && getline(inFile, qStr)) {
        try {
            q = stoi(qStr);
            details.emplace_back(d, t, r, q);
        }
        catch (const invalid_argument& e) {
            cout << "ошибка преобразования";
        }
    }
    inFile.close();
    return details;
}
int main()
{
    setlocale(LC_ALL, "ru");
    vector<RadioDetal> details;
    string filename = "RadioDetal.txt";
    int choice;
    bool running = true;
    while (running)
    {
        cout << "1. Добавить" << endl;
        cout << "2. Список" << endl;
        cout << "3. Сохранить в файл" << endl;
        cout << "4. Считать из файла" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            addDetail(details);
            break;
        case 2:
            for (const auto& detail : details) {
                detail.print();
            }
        case 3:
            saveToFile(details, filename);
            break;
        case 4:
            loadFromFile(filename);
        default:
            break;
        }
    }
}
