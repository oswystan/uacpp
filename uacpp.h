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

struct UAResult {
    UAResult() : version(0) {}
    string str() {
        ostringstream oss;
        oss << "UAResult {name:" << name << ", os:" << os << ", version:" << version << "}";
        return oss.str();
    }
    string   name;
    uint16_t version;
    string   os;
};

class UACpp {
public:
    static int Parse(const string &ua, UAResult& result);
};

#endif /*UACPP_H_INCLUDED*/

/********************************** END **********************************************/
