#include <cassert>
#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<unsigned int> getMaxAppleValues(const std::vector<unsigned int> &appleVec, unsigned int childTotal, unsigned int childPerShot)
{
    std::deque<unsigned int> oneShot(childPerShot);
    std::vector<unsigned int> maxAppleVec;

    // find max in first shot
    unsigned int i;
    for (i = 0; i < childPerShot; ++i)
    {
        while ((oneShot.size() > 0) && (appleVec.at(i) >= appleVec.at(oneShot.back())))
        {
            oneShot.pop_back();
        }
        oneShot.push_back(i);
    }

    for (i = childPerShot; i < childTotal; ++i)
    {
        maxAppleVec.push_back(appleVec.at(oneShot.front()));

        // out of the shot
        while ((oneShot.size() > 0) && (oneShot.front() <= i - childPerShot))
        {
            oneShot.pop_front();
        }

        // value is less than current
        while ((oneShot.size() > 0) && (appleVec.at(i) >= appleVec.at(oneShot.back())))
        {
            oneShot.pop_back();
        }

        oneShot.push_back(i);
    }

    maxAppleVec.push_back(appleVec.at(oneShot.front()));

    return maxAppleVec;
}

int main()
{
    // Total amount of childrens
    unsigned int childTotal = 0;
    // Amount of childrens per shot
    unsigned int childPerShot = 0;
    // Vector that holds apples number for every child
    std::vector<unsigned int> appleVec;

    // read first line from input file
    std::ifstream inFile;
    std::ios_base::iostate exceptionMask = inFile.exceptions() | std::ios::failbit;
    inFile.exceptions(exceptionMask);

    try {
        inFile.open("input.txt");
    }
    catch (std::ios_base::failure& e) {
        std::cerr << e.what() << std::endl;
    }

    std::string str;
    std::getline(inFile, str);
    std::istringstream ss(str);
    ss >> childTotal;
    ss >> childPerShot;
    assert(childTotal >= childPerShot);

    // read second line from input file
    std::getline(inFile, str);
    ss.clear();
    ss.str(str);
    int n;
    while (ss >> n)
    {
        appleVec.push_back(n);
        ss.get();
    }
    assert(appleVec.size() == childTotal);

    // get resulting vector of maximum apple value for each shot
    std::vector<unsigned int> maxAppleVec = getMaxAppleValues(appleVec, childTotal, childPerShot);

    // write results to output file
    std::ofstream outFile("output.txt");
    for (auto apple : maxAppleVec)
    {
        outFile << apple << " ";
    }

    if (outFile.bad())
    {
        std::cout << "Error writing output file" << std::endl;
    }
    else
    {
        std::cout << "Output file written successfully" << std::endl;
    }

    return 0;
}
