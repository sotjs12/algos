var express = require('express');
var router = express.Router();
var fs = require('fs');
var jsonfile = require('jsonfile');
var util = require('util');
router.rootPath = process.env.PWD;
var user_path = router.rootPath + "/husers.json";
var huserPath =  router.rootPath + "/public/husers/";
var userImgPath = router.rootPath + '/public/img/';
var multipart = require('connect-multiparty');
var multipartMiddleware = multipart();
/* GET home page. */
router.get('/', function(req, res) {
  res.render('noDomain', { logUser: router.husers });
});

/* No admin Area  */
router.get('/admin',function(req,res){  
		res.redirect('/auth/facebook');
});
router.get('/logout', function(req, res){
  req.logout();
  res.redirect('/');
});
router.get('/:Domain', function(req, res) {
	var Domain = req.params.Domain;		
	if(router.husers[Domain] != null){	
		var path = huserPath+Domain+'.json';
		fs.exists(path,function(exists){
  			if(exists){
  				if(!req.user)
					res.render("index",{auth:false,domain:Domain,husers:router.husers});		
  				else {
					if(ensureAuthenticated(req, res))
						res.render("index",{auth:true,domain:Domain,husers:router.husers});
				  	else{
						res.render("index",{auth:false,domain:Domain,husers:router.husers});
				  	}
  	 			}
  			}else
  				res.render('404page',{message:"Fail to read domain data :( "});
  		});		 		
	}else
		res.render('404page',{message:"Fail to find domain :( "})
}); 


/*  Post Filed  */

router.post('/defualtSet/:Domain', multipartMiddleware, function(req, resp) {
	var target = req.body.target;
	var Domain = req.params.Domain;
	var filePath = "";
	if(target == 'bg')
		filePath = userImgPath+Domain +'/bgImg.jpg';
	else if(target == 'social')
		filePath = userImgPath+Domain +'/socialImg.jpg';
	else if(target == 'potter')
		filePath = userImgPath+Domain +'/pmain.jpg';

	fs.readFile(req.files.file.path, function (err, data) {
		fs.writeFile(filePath, data, function (err) {		
		resp.send(200);
	});
});
  
  // don't forget to delete all req.files when done 
});
router.post('/defualtJson/:Domain', function(req, res) {
	jsonfile.writeFile(huserPath+req.body.domain+'.json', req.body, function (err) {
	  console.error(err);
	});
});
router.post('/setDomain', function(req, res) {
	if(req.user){
		var newDomain = req.body.domain;
		if(router.husers.hasOwnProperty(req.body.domain)){
			res.render('setDomain.jade',{message:"이미 있는 도메인이에요 ㅠㅠ 재시도!"});
  		}else{
  			add_User(req,newDomain);
			res.redirect('/'+newDomain);
		}
	}else{
		res.statusCode = 500;
		res.setHeader('Content-Type', 'text/plain');
		res.end('badddd connection! ');
  	}	
});


/* function */
/* Read User Data From /husers/husers.Json */

function add_User(req,Domain){	
	router.husers[Domain] = req.user.id;
	router.husers[req.user.id] = {
		"Domain":Domain
	};
	var dumy={
		"domain":Domain,
		"pageTitle":"TITLE",
		"displayName":"",
		"eMail":"",
		"navFontColor":"#f7f7f7",
		"artistSlogan":"",
		"artSlogan":"",
		"designSlogan":"",
		"facebook":"",
		"friends":[],
		"mainBgImg":"img/"+Domain+"/bgImg.jpg",
		"socialImg":"img/"+Domain+"/socialImg.jpg",
		"artistInfo":{
			"artistStatement":"네이버나 다음 메일쓰기에서 예쁘게 꾸미고 html 소스보기해서 갖고오면되욤",
			"potterImg":"img/"+Domain+"/pmain.jpg"
		},
		"artImg":[],
		"designImg":[]
	};
	if (!fs.existsSync(userImgPath+Domain)){
	    fs.mkdirSync(userImgPath+Domain);
	}
	jsonfile.writeFile(user_path,router.husers, function (err) {
  		console.log(err);
	});
	jsonfile.writeFile(huserPath+Domain+".json",dumy, function (err) {
  		console.log(err);
	});
}
router.init_Server = function(){
	fs.exists(user_path,function(exists){
		if(exists){			
			router.husers = JSON.parse(fs.readFileSync(user_path,'utf8'));
			console.log('read user data success');
		}
		else {
			console.log("read fail");
		}
	});
}
function get_Parsed_Json(path){
	path += '/pageData.json';
	jsonfile.readFile(file, function(err, obj) {
  		console.dir(obj)
	});
}
function ensureAuthenticated(req, res) {  
  if (req.isAuthenticated()) 
  	if(req.user.id == router.husers[req.params.Domain])
  		return true;
  return false;   
}
module.exports = router;
