#include <iostream>
#include <vector>
#include "table.hpp"
int main()
{

    struct buy
    {
        std::string brok;
        std::string val;
        std::string lot;
        std::string avg;
    };
    buy buyS;

    table tabel;
    table::TableChar settingH;
    table::colors::BLUE;
    settingH.centerDelimeter = "|";
    settingH.topHeader = '=';
    settingH.downHeader = '-';
    settingH.leftDelimeter = "|";
    tabel.setTableChar(settingH);

    tabel.setPositions(table::setPosition::center);
    typedef std::vector<std::vector<std::string>> V_data;

    V_data buy = {
        {"ON", "111", "11", "111"},
        {"JH", "1", "1", "1"},
        {"HJ", "1", "1", "1"},
        {"KL", "1", "1", "1"},
        {"JL", "1", "1", "1"},

    };

    V_data sell = {
        {"GN", "0", "0", "0"},
        {"GH", "0", "0", "0"},
        {"GH", "0", "0", "0"},
        {"GH", "0", "0", "0"},
        {"GH", "0", "0", "0"},
        {"GH", "0", "0", "0"}};

    V_data ltot = {
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
        {"GN", "0", "0", "0", "GN", "0", "0", "0"},
    };

    tabel.padding = 6;
    tabel.createHeader({"BY", "B.val", "B.lot", "B.avg", "SL", "S.val", "S.lot", "S.avg"}, 4, table::colors::GREEN);
    tabel.createBody(buy, sell);
    // tabel.createBody(ltot);

    std::cout
        << tabel;
    std::cout << "\n";
    return 0;
}