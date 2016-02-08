var mysql = require('mysql');
var fs = require('fs');
var csv = require("fast-csv");
var querystring = require('querystring');
var yahooFinance = require('yahoo-finance');
var deteUtil = require('date-utils');
var model_dir = "./public/models/";
var http = require('http');
var nasdaqURL = "http://www.nasdaq.com/quotes/nasdaq-100-stocks.aspx?render=download";
var exec = require('child_process').exec, child;

function Init_Table(){

var client = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '1124',
    database: 'origin_db'
});
client.connect();
var date = new Date();
var fromCount = 0;
var toCount = 0;
date.setDate(date.getDate() - 3650);
var d = date.toFormat('YYYY-MM-DD');
var date2 = new Date();
date2.setDate(date.getDate());
var dTo = date2.toFormat('YYYY-MM-DD');
var stream = fs.FileReadStream(model_dir + "nasdaq100list.csv");
csv.fromStream(stream)
.on("data", function (data) {
    fromCount++;
    var table_name = data[0] + '_origin ';
    client.query('drop table ' + table_name, function (err, results) {
       client.query('create table if not exists ' + table_name
        + ' (dates date not null,open float,high float,low float,close float,volume float,adjClose float,PRIMARY KEY (dates))'
        , function (err, results) {
            if (!err) {
                yahooFinance.historical({
                    symbol: data[0],
                    from: d,
                    to: dTo,
                    period: 'd'  // 'd' (daily), 'w' (weekly), 'm' (monthly), 'v' (dividends only)
                }, function (err, quotes) {
                    var sql = 'insert into ' + table_name + '(dates,open,high,low,close,volume,adjClose) values (?,?,?,?,?,?,?)';
                    for (row in quotes)
                    {
                        var item = [quotes[row].date, quotes[row].open, quotes[row].high, quotes[row].low
                        , quotes[row].close, quotes[row].volume, quotes[row].adjClose];
                        client.query(sql, item
                            , function (err, result) {
                                if (err)
                                    console.log(err);
                            });
                    }
                    toCount++;
                    console.log(data[0]+"done");
                    if(fromCount == toCount)
                        console.log("download original data done");
                });
            }
            else
                console.log(err);
        });
    });
});

    return 0;
};

function Daily_Update_Table(){
    var client = mysql.createConnection({
        host: 'localhost',
        user: 'root',
        password: '1124',
        database: 'origin_db'
    });
    client.connect();
    var date = new Date();
    date.setDate(date.getDate() - 1);
    var d = date.toFormat('YYYY-MM-DD');
    var stream = fs.FileReadStream(model_dir + "nasdaq100list.csv");
    var fromCount = 0;
    var toCount = 0;
    csv.fromStream(stream)
            .on("data", function (data) {
                fromCount++;
                var table_name = data[0] + '_origin ';
                yahooFinance.historical({
                    symbol: data[0],
                    from: d,
                    to: d,
                    period: 'd'  // 'd' (daily), 'w' (weekly), 'm' (monthly), 'v' (dividends only)
                }, function (err, quotes) {
                    toCount++;
                    if (!err) {  
                        for (row in quotes)
                        {
                            var sql = 'insert into ' + table_name + '(dates,open,high,low,close,volume,adjClose) values (?,?,?,?,?,?,?)';
                            var item = [quotes[row].date, quotes[row].open, quotes[row].high, quotes[row].low
                                    , quotes[row].close, quotes[row].volume, quotes[row].adjClose];
                            client.query(sql, item , function (err, result) {});
                        }                 
                    }
                    if(toCount == fromCount)
                        console.log("Daily Update Done..");
                });
            });

    return 0;
};


function Init_Aalysis_Date() {
    var client = mysql.createConnection({
        host: 'localhost',
        user: 'root',
        password: '1124',
        database: 'analysis_db'
    });
    client.connect();
    var cnt = 0;
    var csvSize = 0;
    var mainJson = {}; 
    var jf = require('jsonfile');

    var stream = fs.FileReadStream(model_dir + "nasdaq100list.csv");
    csv.fromStream(stream)
            .on("data", function (data) {
                var sql = 'select * from ' + data[0] + '_analysis '; 
                csvSize++; 
                client.query(sql, function (err, rows, fields) {
                    cnt++;
                    if (err)
                        console.log(err);
                    else
                    {                    
                        var file = model_dir + data[0] + '_analysis.json';
                        jf.writeFile(file, rows, function(err) { 
                            mainJson[data[0]] = rows[0];  
                            mainJson[data[0]].symbol = data[0];
                            mainJson[data[0]].dates =  mainJson[data[0]].dates.toFormat("YYYY-MM-DD :'UTC'");
                            mainJson[data[0]].linkURL = "http://nasdaq.com/symbol/" + data[0];
                            mainJson[data[0]].cName = data[1]; 
                        }); 
                    }
                }).on("end",function(){
                    if(cnt === csvSize){                     
                        var file = model_dir  + 'daily_analysis.json';
                        jf.writeFile(file, mainJson, function(err) {
                            console.log("Daily Analisis update Done");
                        });  
                        return mainJson;                                                     
                    }
                });            
            });
}

function Init_Origin_Data() {
    var companyArr = [];
    var mainJson = {};
    var client = mysql.createConnection({
        host: 'localhost',
        user: 'root',
        password: '1124',
        database: 'origin_db'
    });
    client.connect();
    var cnt = 0;
    var csvSize = 0;
    var stream = fs.FileReadStream(model_dir + "nasdaq100list.csv");
    csv.fromStream(stream)
            .on("data", function (data) {
                var table_name = data[0] + '_origin ';
                var sql = 'select * from ' + table_name;  
                csvSize++; 
                client.query(sql, function (err, rows, fields) {
                    cnt++;
                    if (err)
                        console.log(err);
                    else
                    {   
                        companyArr.push(data[0]);
                        mainJson[data[0]] = rows;  
                        mainJson[data[0]].symbol = data[0];     
                    }                    
                })
                .on("end",function(){
                    if(cnt === csvSize){
                        var jf = require('jsonfile');
                        var file;                        
                        for(var i=0 ; i < companyArr.length ; i++)
                        {
                            file = model_dir + companyArr[i] + '_origin.json';
                            jf.writeFile(file, mainJson[companyArr[i]], function(err) {});  
                        }                                    
                    }
                });                
            });
}
exports.Init_Daily_Main = function (order) {
  switch(order){
    case 'initOriginJ':
        Init_Origin_Data();
        break;
    case 'initAnalisisJ':
        Init_Aalysis_Date()
        break;
    case 'updateAllTable':
        Init_Table();
        break;
    case 'updateDailyTable':
        Daily_Update_Table();
        break;
    case 'analisisJava':
        child = exec('java -jar ML_A1.jar analisis',
              function (error, stdout, stderr) { 
                console.log("Machine Learning Done..");
            });
        break;
    case 'modelJava':
        child = exec('java -jar ML_A1.jar model',
              function (error, stdout, stderr) {});
        break;
    case 'download':
        download(nasdaqURL,model_dir+'nasdaq100list.csv');
        break;
  }
}

 function download(url, dest){
  var request = http.get(url, function(response) {
    if (response.statusCode === 200) {
        var file = fs.createWriteStream(dest);
        response.pipe(file);
        console.log("List download Done");
    }
    // Add timeout.
    request.setTimeout(12000, function () {
        request.abort();
        console.log("List download Fail");
    });
});
}

function downloadCallback(callback){
    download(nasdaqURL,model_dir+'nasdaq100list.csv');
    if(typeof callback === 'function') {
        callback();
    } 
}

exports.Cron_Do = function () {  
    var schedule = require('node-schedule');
    /*var initTableJob = schedule.scheduleJob('00 00 09 1 * *', function () {  //every Month 01 pm in new_york
        //every sun->th
        downloadCallback(function(){
            child = exec('java -jar ML_A1.jar model',
              function (error, stdout, stderr) { 
                Init_Aalysis_Date(); 
            });
        });
    });
*/
    var DailyUpJob = schedule.scheduleJob('00 00 09 * * 2-6', function () {  //every 08 pm in new_york
        //every sun->th
        downloadCallback(Daily_Update_Table());
    });

    var DailyCalcJob = schedule.scheduleJob('00 00 10 * * 2-6', function () {  //every 08 pm in new_york
        //every sun->th
        child = exec('java -jar ML_A1.jar analisis',
          function (error, stdout, stderr) { 
            Init_Aalysis_Date(); 
        });
    });
};
