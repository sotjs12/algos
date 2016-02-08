var express = require('express');
var router = express.Router();
var fs = require('fs');
var background = require("./background.js");

var html_dir = "./views/";
var model_dir = "./models/";

background.Cron_Do();

router.get('/', function(req, res, next) {
	res.render('index.html');
});
router.get('/Algorithm/:order', function(req, res) {
	var pram = req.params.order;
	switch(pram){
		case 'IOJ':
			background.Init_Daily_Main('initOriginJ');
			break;
		case 'IAJ':
			background.Init_Daily_Main('initAnalisisJ');
			break;
		case 'UAT':
			background.Init_Daily_Main('updateAllTable');
			break;
		case 'UDT':
			background.Init_Daily_Main('updateDailyTable');
			break;
		case 'AJ':
			background.Init_Daily_Main('analisisJava');
			break;
		case 'MJ':
			background.Init_Daily_Main('modelJava');
			break;
		case 'down':
			background.Init_Daily_Main('download');
			break;
	}
	res.send('GET');
});
module.exports = router;
