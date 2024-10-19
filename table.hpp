#include <iostream>
#include <vector>
#include <iomanip> //std::setw

#include <sys/ioctl.h>
#include <unistd.h>
#include <cmath>
#include <algorithm>

#ifndef SimpleTable_HPP_
#define SimpleTable_HPP_
class table
{
private:
    std::string printHeader;
    std::string printBody;
    std::string finalOutput;
    std::string p(size_t n, size_t size);
    std::string space(std::string s, size_t size, size_t centerDelimeter = 0, bool is = true);
    int widthHeader = 0, headerValueLength = 0, headerLength = 0, centerdelim = 0, centerD = 0;
    //  int centerdelim[] = 0;
    std::vector<std::vector<std::string>> finaloutputBody;
    std::vector<int> lengthHeaderCols;
    std::vector<std::string> v_colors = {"\033[37m", "\033[31m", "\033[32m", "\033[34m"};

public:
    table();
    ~table();
    int padding = 2;

    typedef struct TableChar_
    {
        std::string centerDelimeter = "|";
        std::string leftDelimeter = "|";
        std::string rightDelimeter = "|";
        std::string downDelimeter = "+";
        std::string topHeader = "-";
        std::string downHeader = "-";
    } TableChar;

    typedef enum colours_
    {
        DEFAULT,
        RED,
        GREEN,
        BLUE
    } colors;

    typedef enum setPosition_
    {

        center,
        left,
        right
    } setPosition;

    inline void setTableChar(TableChar t)
    {
        tbl.centerDelimeter = (t.centerDelimeter.empty() ? tbl.centerDelimeter : t.centerDelimeter);
        tbl.topHeader = (t.topHeader.empty() ? tbl.topHeader : t.topHeader);
        tbl.downHeader = (t.downHeader.empty() ? tbl.downHeader : t.downHeader);
        tbl.leftDelimeter = (t.leftDelimeter.empty() ? tbl.leftDelimeter : t.leftDelimeter);
        tbl.rightDelimeter = (t.rightDelimeter.empty() ? tbl.rightDelimeter : t.rightDelimeter);
        tbl.downDelimeter = (t.downDelimeter.empty() ? tbl.downDelimeter : t.downDelimeter);
    }
    inline void setPositions(setPosition pst)
    {
        position = pst;
    }
    void createHeader(std::vector<std::string> s, size_t centerDelimeter = 0, colors colours = colors::DEFAULT);
    void createBody(std::vector<std::vector<std::string>> buy, std::vector<std::vector<std::string>> sell);
    void createBody(std::vector<std::vector<std::string>> buy);
    friend std::ostream &operator<<(std::ostream &os, table &tb);
    std::string printFinalTable();

private:
    colours_ colour;
    TableChar tbl;
    setPosition position;
    int m_center = 10, m_right = 20;
};

#endif