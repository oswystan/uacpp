#!/usr/bin/env node
/*
 *********************************************************************************
 *                     Copyright (C) 2018 wystan
 *
 *       filename: verify.js
 *    description:
 *        created: 2018-10-26 14:33:10
 *         author: wystan
 *
 *********************************************************************************
 */

const log = console.log;
const csv2json = require("csvtojson");

class UA {
    constructor(name, major, os) {
        this.name = name;
        this.major = major;
        this.os = os;
    }
}

function firefox(ua) {
    let result = /Firefox\/(\d+)\.([\.\w]+)$/.exec(ua);
    result = result || /FxiOS\/(\d+)\.([\.\w]+)/.exec(ua);
    if (result) {
        return new UA('firefox', result[1], result.input);
    }
    return result;
}
function chrome(ua) {
    return null;
}
function safari(ua) {
    return null;
}
function android(ua) {
    return null;
}
function windows(ua) {
    return null;
}
function macos(ua) {
    return null;
}
function ios(ua) {
    let result = /(iPad|iPhone);\sCPU\s(?:iPhone\s)?OS\s(\d+(?:_\d+)*)\slike\sMac\sOS\sX/.exec(ua);
    return (result ? "ios" : null);
}
function linux(ua) {
    return null;
}

var browserMatcher = [
    firefox,
    chrome,
    safari,
];
var osMatcher = [
    android,
    windows,
    macos,
    ios,
    linux,
];
function parse_browser(ua) {
    for (let parser of browserMatcher) {
        let result = parser(ua);
        if (result) { return result }
    }
    return null;
}
function parse_os(ua) {
    for (let parser of osMatcher) {
        let result = parser(ua);
        if (result) { return result }
    }
    return null;
}

function parse(ua) {
    let browser = parse_browser(ua);
    let osname = parse_os(ua);
    if (!browser || !osname) {
        return null;
    }
    browser.os = osname;
    return browser;
}

var counter = 0;
csv2json()
    .fromFile("database/firefox-ios.csv")
    .then(ls=>{
        for (let i=0; i<ls.length; i++) {
            let result = parse(ls[i].ua);
            if (!result) {
                counter++;
                log(ls[i].ua);
            }
        }
        log(counter);
    });

/************************************* END **************************************/

