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

struct UAData {
    string   ua;
    string   name;
    string   os;
    uint16_t version;
};

UAData allUA[] = {
    // chrome
    {
        .ua = "Mozilla/5.0 (Linux; Android 7.1; Mi A1 Build/N2G47H) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36",
        .name = "chrome",
        .os = "android",
        .version = 58
    }, {
        .ua = "Mozilla/5.0 (iPhone; CPU iPhone OS 11_2_5 like Mac OS X) AppleWebKit/604.1.34 (KHTML, like Gecko) CriOS/64.0.3282.112 Mobile/15D60 Safari/604.1",
        .name = "chrome",
        .os = "ios",
        .version = 64
    }, {
        .ua = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36",
        .name = "chrome",
        .os = "macos",
        .version = 65
    }, {
        .ua = "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36",
        .name = "chrome",
        .os = "windows",
        .version = 69
    }, {
        .ua = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.92 Safari/537.36",
        .name = "chrome",
        .os = "linux",
        .version = 69
    },
    // safari
    {
        .ua = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/11.1.2 Safari/605.1.15",
        .name = "safari",
        .os = "macos",
        .version = 11
    }, {
        .ua = "Mozilla/5.0 (iPhone; CPU iPhone OS 11_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/11.0 Mobile/15E148 Safari/604.1",
        .name = "safari",
        .os = "ios",
        .version = 11
    }, {
        .ua = "Mozilla/5.0 (iPad; CPU OS 10_3_3 like Mac OS X) AppleWebKit/603.3.8 (KHTML, like Gecko) Version/10.0 Mobile/14G60 Safari/602.1",
        .name = "safari",
        .os = "ios",
        .version = 10
    }, {
        .ua = "Mozilla/5.0 (iPod touch; CPU iPhone OS 9_3_5 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13G36 Safari/601.1",
        .name = "safari",
        .os = "ios",
        .version = 9
    },
    // firefox
    {
        .ua = "Mozilla/5.0 (Android 6.0.1; Mobile; rv:48.0) Gecko/48.0 Firefox/48.0",
        .name = "firefox",
        .os = "android",
        .version = 48
    }, {
        .ua = "Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_2 like Mac OS X) AppleWebKit/603.2.4 (KHTML, like Gecko) FxiOS/7.5b3349 Mobile/14F89 Safari/603.2.4",
        .name = "firefox",
        .os = "ios",
        .version = 7
    }, {
        .ua = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:63.0) Gecko/20100101 Firefox/63.0",
        .name = "firefox",
        .os = "windows",
        .version = 63
    }, {
        .ua = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:61.0) Gecko/20100101 Firefox/61.0",
        .name = "firefox",
        .os = "linux",
        .version = 61
    }, {
        .ua = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:52.0) Gecko/20100101 Firefox/52.0",
        .name = "firefox",
        .os = "macos",
        .version = 52
    },
};

int main(int argc, char *argv[])
{
    for (auto one : allUA) {
        UAResult result;
        int ret = UACpp::Parse(one.ua, result);
        if (0 != ret) {
            cout << "ERROR:" << one.ua << endl;
            break;
        }
        if (one.name != result.name || one.os != result.os || one.version != result.version) {
            cout << "ERROR: verify failed" << endl;
            break;
        }
        cout << result.str() << endl;
    }
    return 0;
}

/********************************** END **********************************************/

