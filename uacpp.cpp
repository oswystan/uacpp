/*
 **************************************************************************************
 *       Filename:  uacpp.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-10-25 12:04:23
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <iostream>
#include <regex>
#include "uacpp.h"

typedef int(*UAParser)(const string&, UAResult&);

struct WindowsVersionMapper {
    string no;
    string version;
};

static WindowsVersionMapper win_mapper[] = {
    {"5.0" , "2000" },
    {"5.1" , "xp"   },
    {"5.2" , "2003" },
    {"6.0" , "vista"},
    {"6.1" , "7"    },
    {"6.2" , "8"    },
    {"6.3" , "8.1"  },
    {"10.0", "10"   },
};

static const char* windowsMapper(const string& in) {
    for (auto &one : win_mapper) {
        if (one.no == in) {
            return one.version.c_str();
        }
    }
    return nullptr;
}

static int browserInternetExplorer(const string& ua, UAResult& result) {
    static std::regex ex(".*MSIE\\s(\\d+(?:\\.\\d+));[\\s\\S]+Windows\\sNT\\s(\\d+(?:\\.\\d+));.*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() == 3) {
        result.name = "ie";
        result.version = std::stoi(sm[1]);
        return 0;
    }
    static std::regex ex2(".*Windows\\sNT\\s(\\d+(?:\\.\\d+));[\\s\\S]+Trident\\/\\d+\\.\\d+;[\\s\\S]+rv:(\\d+(?:\\.\\d+)).*");
    std::regex_match(ua, sm, ex2);
    if (sm.size() == 3) {
        result.name = "ie";
        result.version = std::stoi(sm[2]);
        return 0;
    }

    return -1;
}
static int browserEdge(const string& ua, UAResult& result) {
    static std::regex ex(".*Windows\\sNT\\s(\\d+(?:\\.\\d+)+);[\\s\\S]+Edge\\/(\\d+(?:\\.\\d+))$");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 3) { return -1; }

    result.name = "edge";
    result.version = std::stoi(sm[2]);
    return 0;
}
static int browserFirefox(const string& ua, UAResult& result) {
    static std::regex ex(".*(Firefox|FxiOS)\\/(\\d+(?:\\.\\w+)+).*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 3) { return -1; }

    result.name = "firefox";
    result.version = std::stoi(sm[2]);
    return 0;
}
static int browserSafari(const string& ua, UAResult& result) {
    static std::regex ex(".*Version\\/(\\d+(?:\\.\\d+)+)\\s(Mobile\\/\\w+\\s)?Safari\\/(\\d+(?:\\.\\d+)+).*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 4) { return -1; }

    result.name = "safari";
    result.version = std::stoi(sm[1]);
    return 0;
}
static int browserChrome(const string& ua, UAResult& result) {
    static std::regex ex(".*(Chrome|CriOS)\\/(\\d+(?:\\.\\d+)+).*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 3) { return -1; }

    result.name = "chrome";
    result.version = std::stoi(sm[2]);
    return 0;
}
static int osAndroid(const string& ua, UAResult& result) {
    static std::regex ex(".*(Android){1}.*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 2) { return -1; }

    result.os = "android";
    return 0;
}
static int osIOS(const string& ua, UAResult& result) {
    static std::regex ex(".*(iPad|iPhone|iPod\\stouch);\\sCPU\\s(?:iPhone\\s)?OS\\s(\\d+(?:_\\d+)*)\\slike\\sMac\\sOS\\sX.*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 3) { return -1; }

    result.os = "ios";
    return 0;
}
static int osMacOS(const string& ua, UAResult& result) {
    static std::regex ex(".*(Macintosh;){1}.*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 2) { return -1; }

    result.os = "macos";
    return 0;
}
static int osWindows(const string& ua, UAResult& result) {
    static std::regex ex(".*(Windows\\sNT\\s\\d+){1}.*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 2) { return -1; }
    result.os = "windows";
    return 0;
}
static int osLinux(const string& ua, UAResult& result) {
    static std::regex ex(".*(X11;){1,}[\\s\\S]+(Linux){1,}.*");
    std::smatch sm;
    std::regex_match(ua, sm, ex);
    if (sm.size() != 3) { return -1; }

    result.os = "linux";
    return 0;
}

static UAParser browserParsers[] = {
    browserInternetExplorer,
    browserEdge,
    browserChrome,
    browserSafari,
    browserFirefox,
};
static UAParser osParsers[] = {
    osAndroid,
    osIOS,
    osMacOS,
    osWindows,
    osLinux,
};

static int parseBrowser(const string& ua, UAResult& result) {
    for(auto parser : browserParsers) {
        if (parser(ua, result) == 0) {
            return 0;
        }
    }
    return -1;
}
static int parseOS(const string& ua, UAResult& result) {
    for(auto parser : osParsers) {
        if (parser(ua, result) == 0) {
            return 0;
        }
    }
    return -1;
}

int UACpp::Parse(const string& ua, UAResult& result) {
    return parseBrowser(ua, result) + parseOS(ua, result);
}

/********************************** END **********************************************/

