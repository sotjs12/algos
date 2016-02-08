var express           = require('express');
var path              = require('path');
var favicon           = require('serve-favicon');
var logger            = require('morgan');
var cookieParser      = require('cookie-parser');
var bodyParser        = require('body-parser');
var passport          = require('passport');
var util              = require('util');
var FacebookStrategy  = require('passport-facebook').Strategy;
var session           = require('express-session');
var config            = require('./configuration/config');
var routes            = require('./routes/index');
var users             = require('./routes/users');
var app               = express();


routes.init_Server();
/////////////////////////////////////////////////////////////////
/////////////////////////  social login //////////////////////////////////////
// Passport session setup.
passport.serializeUser(function(user, done) {
  done(null, user);
});
passport.deserializeUser(function(obj, done) {
  done(null, obj);
});
// Use the FacebookStrategy within Passport.
passport.use(new FacebookStrategy({
    clientID: config.facebook_api_key,
    clientSecret:config.facebook_api_secret ,
    callbackURL: config.callback_url
  },
  function(accessToken, refreshToken, profile, done) {
    process.nextTick(function () {
      //Check whether the User exists or not using profile.id
      //Further DB code.
      return done(null, profile);
    });
  }
));
/////////////////////////////////////////////////////////////////
/////////////////////////  social login //////////////////////////////////////


// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(session({ secret: 'keyboard cat', key: 'sid'}));
app.use(passport.initialize());
app.use(passport.session());
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use('/',routes);
app.use('/users', users);


///////////////////////////////////////////////////////////////
//////////////////// user Authentication /////////////////////////////


//Passport Router
app.get('/auth/facebook', passport.authenticate('facebook'));
app.get('/auth/facebook/callback',
  passport.authenticate('facebook', {
       failureRedirect: '/'
  }), 
  function(req, res) {
    if(routes.husers.hasOwnProperty(req.user.id))
      res.redirect('/'+routes.husers[req.user.id].Domain);
    else{
      res.render('setDomain.jade',{message:"도메인이라고 하는놈인데 앞으로 당신 주소가될꺼에요 ex) potter.iptime.org/kimamuge 한번 설정하면 바꿀수없어요 고쳐달라고해do 안고쳐줄꺼지롱!! 신중하게 선택하세요 ㅎ.,ㅎ"});
    }
});



///////////////////////////////////////////////////////////////
//////////////////////// User Authentication ////////////////////////////////////

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
  app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
      message: err.message,
      error: err
    });
  });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
  res.status(err.status || 500);
  res.render('error', {
    message: err.message,
    error: {}
  });
});


module.exports = app;
