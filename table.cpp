#include "table.hpp"

table::table()
{
    struct winsize w;
    // Mendapatkan ukuran terminal
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        std::cerr << "Error getting terminal size" << std::endl;
    }

    m_center = w.ws_col / 2;
    m_right = w.ws_col;
}

table::~table()
{
}

std::string table::p(size_t n, size_t size)
{

    std::string space = "";
    // std::cout << "size: " << size;
    for (int i = 0; i < (n - size); i++)
        space += " ";
    return space;
}

std::string table::space(std::string s, size_t size, size_t centerDelimeter, bool is)
{
    std::string ss;
    for (int i = 0; i < size; i++)
    {
        // if (i == (size - 1) / 2 && is == true)
        if (i == centerDelimeter && is == true)
            ss += "+";
        else
            ss += s;
    }

    return ss;
}

void table::createHeader(std::vector<std::string> s, size_t centerDelimeter_, colors colours)
{
    // std::transform(centerDelimeter_.begin(), centerDelimeter_.end(), centerDelimeter_.begin(), ::toupper);

    // if (!centerDelimeter_.empty() && centerDelimeter_ == "ALL")
    //     this->centerdelim = {0, 1, 2, 3, 4, 5, 6, 7};
    // else
    this->centerdelim = centerDelimeter_;
    this->headerLength = s.size();
    std::string value;

    for (int i = 0; i < this->headerLength; i++)
    {
        value += (i == 0 ? tbl.leftDelimeter + " " : "") + s[i];
        value += (i == (this->headerLength - 1) ? (p(padding, 0) + tbl.rightDelimeter + "\n") : this->centerdelim == 0   ? (p(padding, 0) + "")
                                                                                            : i == this->centerdelim - 1 ? (p(padding, 0) + tbl.centerDelimeter + p(padding, 0))
                                                                                                                         : (p(padding, 0) + ""));

        // value += (i == 0 ? tbl.leftDelimeter + " " : "") + s[i] + p(padding, 0);
        // if (this->centerdelim.size() > 1 && centerDelimeter_ == "ALL")
        //     value += (i == this->headerLength - 1 ? "" : tbl.centerDelimeter + p(padding, 0));
        // else if (this->centerdelim.size() == 1)
        //     value += (i == this->headerLength - 1 ? "" : (this->centerdelim[0] == 0 ? "" : i == this->centerdelim[0] - 1 ? tbl.centerDelimeter + p(padding, 0)
        //                                                                                                                  : ""));
        // value += (i == this->headerLength - 1 ? tbl.rightDelimeter + "\n" : "");

        this->widthHeader += std::string(s[i]).length() + padding;
        lengthHeaderCols.emplace_back(s[i].length());
    }
    headerValueLength = value.length();
    for (int i = 0; i < this->centerdelim; i++)
    {
        centerD += lengthHeaderCols[i];
        centerD += padding;
    }

    if (setPosition::center == position)
    {
        printHeader += space(" ", m_center - (headerValueLength / 2), 0, false);
        printHeader += (colors::DEFAULT == colours ? v_colors[colors::DEFAULT] : v_colors[colours]);
        printHeader += space(tbl.topHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) += "\n";
        printHeader += space(" ", m_center - (headerValueLength / 2), 0, false);
        printHeader += value;
        printHeader += space(" ", m_center - (headerValueLength / 2), 0, false);
        printHeader += space(tbl.topHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) += "\n\033[0m";
    }
    else if (setPosition::right == position)
    {
        printHeader += space(" ", m_right - headerValueLength, 0, false);
        printHeader += (colors::DEFAULT == colours ? v_colors[colors::DEFAULT] : v_colors[colours]);
        printHeader += space(tbl.topHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) += "\n";
        printHeader += space(" ", m_right - headerValueLength, 0, false);
        printHeader += value;
        printHeader += space(" ", m_right - headerValueLength, 0, false);
        printHeader += space(tbl.topHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) += "\n\033[0m";
    }
    else
    {

        // std::cout << "this->centerdelim: " << this->centerdelim << " | " << centerD + 2 << std::endl;
        printHeader += (colors::DEFAULT == colours ? v_colors[colors::DEFAULT] : v_colors[colours]);
        printHeader += space(tbl.topHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) += "\n";
        printHeader += value;
        printHeader += space(tbl.topHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) += "\n\033[0m";
    }
}

void table::createBody(std::vector<std::vector<std::string>> buy, std::vector<std::vector<std::string>> sell)
{

    size_t maxRows = std::max(buy.size(), sell.size());

    for (size_t i = 0; i < maxRows; i++)
    {
        std::vector<std::string> row;

        if (i < buy.size())
            row.insert(row.end(), buy[i].begin(), buy[i].end());
        else
        {
            if (i < sell.size())
            {
                row.insert(row.end(), sell[i].size(), "-");
            }
            else
            {
                row.insert(row.end(), 4, "-");
            }
        }

        if (i < sell.size())
            row.insert(row.end(), sell[i].begin(), sell[i].end());
        else
        {
            if (i < sell.size())
            {
                row.insert(row.end(), sell[i].size(), "-");
            }
            else
            {
                row.insert(row.end(), 4, "-");
            }
        }

        finaloutputBody.push_back(row);
    }

    createBody(finaloutputBody);
    // for (const auto &row : finaloutputBody)
    // {
    //     for (const auto &val : row)
    //     {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // if (setPosition::center == position)
    // {

    //     printBody += space(" ", m_center - (headerValueLength / 2), 0, false);
    //     printBody += s + "\n";
    //     printBody += space(" ", m_center - (headerValueLength / 2), 0, false);
    //     printBody += space(tbl.downHeader, this->widthHeader + (this->centerdelim == 0 ? 3 : 5), this->centerdelim - 1) += "\n";
    // }
    // else if (setPosition::right == position)
    // {
    //     printBody += space(" ", m_right - headerValueLength, 0, false);
    //     printBody += s + "\n";
    //     printBody += space(" ", m_right - headerValueLength, 0, false);
    //     printBody += space(tbl.downHeader, this->widthHeader + (this->centerdelim == 0 ? 3 : 5), this->centerdelim - 1) += "\n";
    // }
    // else
    // {

    //     printBody += space(tbl.topHeader, this->widthHeader + (this->centerdelim == 0 ? 3 : 5), this->centerdelim - 1) += "\n";
    //     printBody += s;
    //     printBody += space(tbl.downHeader, this->widthHeader + (this->centerdelim == 0 ? 3 : 5), this->centerdelim - 1) += "\n";
    // }
}

void table::createBody(std::vector<std::vector<std::string>> final)
{
    std::string a, b;
    std::stringstream ss;
    for (int i = 0; i < final.size(); i++)
    {

        if (setPosition::center == position)
        {
            a += space(" ", m_center - (headerValueLength / 2), 0, false);
        }
        else if (setPosition::right == position)
            a += space(" ", m_right - headerValueLength, 0, false);
        for (int j = 0; j < final[i].size(); j++)
        {
            int ab = std::abs(static_cast<int>(final[i][j].length()) - lengthHeaderCols[j]);

            // a += (j == 0 ? tbl.leftDelimeter + " " : "") + final[i][j];
            // a += ((j == (this->headerLength - 1))
            //           ? (p(ab + padding, 0) + tbl.rightDelimeter + "\n" +
            //              (position == setPosition::center
            //                   ? space(" ", m_center - (headerValueLength / 2), 0, false)
            //               : position == setPosition::right
            //                   ? space(" ", m_right - headerValueLength, 0, false)
            //                   : "") +
            //              space(tbl.downHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) + "\n")
            //           : (this->centerdelim == 0
            //                  ? p(padding, 0)
            //                  : ((j == this->centerdelim - 1)
            //                         ? (p(ab + padding, 0) + tbl.centerDelimeter + p(padding, 0))
            //                         : p(ab + padding, 0))));

            // a += "s\n";
            // a += final[i][j];

            a += (j == 0 ? tbl.leftDelimeter + " " : "") + final[i][j] + p(ab + padding, 0);
            a += (j == this->centerdelim - 1 ? tbl.centerDelimeter + p(padding, 0) : "");
            a += (j == this->headerLength - 1 ? tbl.rightDelimeter + "\n" : "");
        }
        if (setPosition::center == position)
        {
            a += space(" ", m_center - (headerValueLength / 2), 0, false);
            a += space(tbl.downHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) + "\n";
        }
        else if (setPosition::right == position)
        {
            a += space(" ", m_right - headerValueLength, 0, false);
            a += space(tbl.downHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) + "\n";
        }
        else
            a += space(tbl.downHeader, this->headerValueLength - 1, centerD + 2, this->centerdelim == 0 ? false : true) + "\n";

        // a += "\n";
    }

    printBody += a;

    // std::cout << a << std::endl;
}

std::string table::printFinalTable()
{
    finalOutput += printHeader;
    finalOutput += printBody;

    return finalOutput;
}
std::ostream &operator<<(std::ostream &os, table &tb)
{

    os << tb.printFinalTable();
    return os;
}
