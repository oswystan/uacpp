/*
 **************************************************************************************
 *       Filename:  main.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-10-25 12:12:24
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */


#include <iostream>
#include "uacpp.h"

using std::cout;
using std::endl;

string allUA[] = {
    "Mozilla/5.0 (Linux; U; Android 7.0; en-US; SM-G610F Build/NRD90M) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/40.0.2214.89 UCBrowser/11.4.8.1012 Mobile Safari/537.36",
};
int main(int argc, char *argv[])
{
    for (uint32_t i=0; i<sizeof(allUA)/sizeof(allUA[0]); i++) {
        auto result = UACpp::Parse(allUA[i]);
        cout << result.browser << "\t" << result.version.str() << "\t" <<result.os << endl;
    }
    return 0;
}

/********************************** END **********************************************/

