/*
 **************************************************************************************
 *       Filename:  uacpp.h
 *    Description:   header file
 *
 *        Version:  1.0
 *        Created:  2018-10-25 12:04:17
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef UACPP_H_INCLUDED
#define UACPP_H_INCLUDED

#include <string>
#include <sstream>
using std::string;
using std::ostringstream;

struct SemanticVersion {
    SemanticVersion() {
        major = minor = patch = 0;
    }
    string str() {
        ostringstream oss;
        oss << major << "." << minor << "." << patch;
        return oss.str();
    }

    uint16_t major;
    uint16_t minor;
    uint16_t patch;
};

struct UAResult {
    string          browser;
    SemanticVersion version;
    string          os;
};

class UACpp {
public:
    static UAResult Parse(const string &ua);
};

#endif /*UACPP_H_INCLUDED*/

/********************************** END **********************************************/
