#!/usr/bin/env node
/*
 *********************************************************************************
 *                     Copyright (C) 2018 wystan
 *
 *       filename: spider.js
 *    description: download database from developers.whatismybrowser.com and save to csv files
 *        created: 2018-10-24 14:37:11
 *         author: wystan
 *
 *********************************************************************************
 */

const fs = require('fs');
const fetch = require('node-fetch');
var jsdom = require("jsdom");
const { JSDOM } = jsdom;
const { window } = new JSDOM();
const { document } = (new JSDOM('')).window;
global.document = document;
var $ = jQuery = require('jquery')(window);
const ObjectsToCsv = require('objects-to-csv');
const log = console.log;
const rmdir = require('rmdir-recursive').sync;

var base = "https://developers.whatismybrowser.com/useragents/explore/software_name/";
var dir = "db";
var all = [];
var page = 0;
var browser = 0;
const browsers = [
    {
        name: "chrome",
        pages: 3215
    }, {
        name: "firefox",
        pages:  481
    }, {
        name: "safari",
        pages: 229
    }, {
        name: "opera",
        pages: 311
    }, {
        name: "internet-explorer",
        pages: 2088
    }, {
        name: "edge",
        pages: 58
    }, {
        name: "qq-browser",
        pages: 26
    }, {
        name: "lb-browser",
        pages: 6
    }, {
        name: "uc-browser",
        pages: 357
    }, {
        name: "sogou-explorer",
        pages: 4
    }
];


function get(url, cb) {
    fetch(url)
        .then(res=>res.text())
        .then(body=>{cb(body);})
        .then(next);
}

function parse(body) {
    let tr = $(body).find("tbody tr");
    for (let i=0; i<tr.length; i++) {
        let td = $(tr[i]).find("td");
        if (td.length < 5) {
            log("ERROR: invalid format");
            continue;
        }

        let obj = {
            ua: $(td[0]).find("a").text(),
            software: $(td[1]).text(),
            software_type: $(td[2]).text(),
            hw: $(td[3]).text(),
            pop: $(td[4]).text(),
        };
        all.push(obj);
    }
}

function next() {
    if (browser >= browsers.length) {
        log("DONE.")
        return;
    }
    page++;
    if (page > browsers[browser].pages) {
        save(dir + "/" + browsers[browser].name + ".csv");
        browser++;
        page = 0;
        next();
        all = [];
        return;
    }
    let url = base + browsers[browser].name + "/" + page;
    log(url);
    get(url, parse);
}

function save(name) {
    new ObjectsToCsv(all).toDisk(name);
}

function prepare() {
    rmdir(dir);
    fs.mkdirSync(dir);
}

function main() {
    prepare();
    next();
}

/************************************* END **************************************/

main();
