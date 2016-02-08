var app = angular.module('myApp', ['ngRoute','mainController']);


app.config(function($routeProvider) {
    $routeProvider
    .when('/home', {
        templateUrl : 'pages/realMain.html',
        controller  : 'adminController'
    })
    .when('/analysis/:symbol', {
        templateUrl : 'pages/analysisPage.html',
        controller  : 'myAnalysisController'
    })
    .when('/Thumb_Main',{        
        templateUrl : 'pages/mainThumb.html',
        controller  : 'myRowController'
    })
    .when('/tableST',{        
        templateUrl : 'pages/mainTable.html',
        controller  : 'TableController'
    })
    .when('/Index',{        
        templateUrl : 'pages/mainIndexInfo.html'
    })
    .otherwise({redirectTo:'/home'});
});



