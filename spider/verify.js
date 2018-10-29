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
    let result = /(Firefox|FxiOS)\/(\d+(?:\.\w+)+)/.exec(ua);
    if (result) {
        let major = parseInt(result[2].split(".")[0]);
        return new UA('firefox', major, result.input);
    }
    return result;
}
function chrome(ua) {
    let result = /(Chrome|CriOS)\/(\d+(?:\.\d+)+)/.exec(ua);
    if (result) {
        let major = parseInt(result[2].split(".")[0]);
        return new UA('chrome', major, result.input);
    }
    return result;
}
function safari(ua) {
    let result = /Version\/(\d+(?:\.\d+)+)\s(Mobile\/\w+\s)?Safari\/(\d+(?:\.\d+)+)/.exec(ua);
    if (result) {
        let major = parseInt(result[1].split(".")[0]);
        return new UA('safari', major, result.input);
    }
    return result;
}
function android(ua) {
    let result = /(Android){1}/.exec(ua);
    return (result ? "android" : null);
}
function windows(ua) {
    let result = /(Windows\sNT\s\d+){1}/.exec(ua);
    return (result ? "windows" : null);
}
function macos(ua) {
    let result = /(Macintosh;){1}/.exec(ua);
    return (result ? "macos" : null);
}
function ios(ua) {
    let result = /(iPad|iPhone|iPod\stouch);\sCPU\s(?:iPhone\s)?OS\s(\d+(?:_\d+)*)\slike\sMac\sOS\sX/.exec(ua);
    return (result ? "ios" : null);
}
function linux(ua) {
    let result = /(X11;){1,}[\s\S]+(Linux){1,}/.exec(ua);
    return (result ? "linux" : null);
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
        let err = "";
        if (!browser) { err += "unknown browser|"}
        if (!osname) { err += "unknown os|" }
        log(err, ua);
        return null;
    }
    browser.os = osname;
    return browser;
}

function verify_in_file() {
    var counter = 0;
    csv2json()
        .fromFile("database/firefox-all.csv")
        .then(ls=>{
            for (let i=0; i<ls.length; i++) {
                let result = parse(ls[i].ua);
                log(result);
                if (!result) {
                    counter++;
                }
            }
            log(counter);
        });
}

function verify_in_mem() {
    var all_ua = [
        // safari
        {
            ua    : "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/11.1.2 Safari/605.1.15",
            name  : "safari",
            major : 11,
            os    : "macos",
        }, {
            ua    : "Mozilla/5.0 (iPhone; CPU iPhone OS 11_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/11.0 Mobile/15E148 Safari/604.1",
            name  : "safari",
            major : 11,
            os    : "ios",
        }, {
            ua    : "Mozilla/5.0 (iPad; CPU OS 10_3_3 like Mac OS X) AppleWebKit/603.3.8 (KHTML, like Gecko) Version/10.0 Mobile/14G60 Safari/602.1",
            name  : "safari",
            major : 10,
            os    : "ios",
        }, {
            ua    : "Mozilla/5.0 (iPod touch; CPU iPhone OS 9_3_5 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13G36 Safari/601.1",
            name  : "safari",
            major : 9,
            os    : "ios",
        },

        // chrome
        {
            ua    : "Mozilla/5.0 (Linux; Android 7.1; Mi A1 Build/N2G47H) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36",
            name  : "chrome",
            major : 58,
            os    : "android",
        }, {
            ua    : "Mozilla/5.0 (iPhone; CPU iPhone OS 11_2_5 like Mac OS X) AppleWebKit/604.1.34 (KHTML, like Gecko) CriOS/64.0.3282.112 Mobile/15D60 Safari/604.1",
            name  : "chrome",
            major : 64,
            os    : "ios",
        }, {
            ua    : "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36",
            name  : "chrome",
            major : 65,
            os    : "macos",
        }, {
            ua    : "Mozilla/5.0 (Linux; Android 7.1; Mi A1 Build/N2G47H) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36",
            name  : "chrome",
            major : 58,
            os    : "android",
        }, {
            ua    : "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36",
            name  : "chrome",
            major : 69,
            os    : "windows",
        }, {
            ua    : "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.92 Safari/537.36",
            name  : "chrome",
            major : 69,
            os    : "linux",
        },

        //firefox
        {
            ua    : "Mozilla/5.0 (Android 6.0.1; Mobile; rv:48.0) Gecko/48.0 Firefox/48.0",
            name  : "firefox",
            major : 48,
            os    : "android",
        }, {
            ua    : "Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_2 like Mac OS X) AppleWebKit/603.2.4 (KHTML, like Gecko) FxiOS/7.5b3349 Mobile/14F89 Safari/603.2.4",
            name  : "firefox",
            major : 7,
            os    : "ios",
        }, {
            ua    : "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:63.0) Gecko/20100101 Firefox/63.0",
            name  : "firefox",
            major : 63,
            os    : "windows",
        }, {
            ua    : "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:61.0) Gecko/20100101 Firefox/61.0",
            name  : "firefox",
            major : 61,
            os    : "linux",
        }, {
            ua    : "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:52.0) Gecko/20100101 Firefox/52.0",
            name  : "firefox",
            major : 52,
            os    : "macos",
        },
    ];

    for (let one of all_ua) {
        let result = parse(one.ua);
        if (!result) {
            log("ERROR:", one, result);
            break;
        }
        if (result.os !== one.os || result.major !== one.major || result.name !== one.name) {
            log("ERROR"); log(one); log(result);
            break;
        }
    }
}

verify_in_mem();

/************************************* END **************************************/

