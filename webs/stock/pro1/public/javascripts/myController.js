var mainController = angular.module('mainController',['angular.filter','angularModalService']);
var globalDaily;
mainController.controller("myRowController",function($scope,$http){
  	$http.get("./models/daily_analysis.json").success(function(response) {
      $scope.daily = response;   
      var obj = [];
      for(var t in response)
      {
        obj.push(response[t]);
      }
      $scope.aData = obj;
      globalDaily = obj; 
    });
});


mainController.controller("adminController",function($scope,$http, ModalService){
  $scope.show = function(order) {
        ModalService.showModal({
            templateUrl: 'pages/modal.html',
            controller: "ModalController",
            inputs:{
              inType:order
            }
        }).then(function(modal) {
            modal.element.modal();
            modal.close.then(function(result) {
              if(result =="Yes")
              {  
                $http.get('/Algorithm/'+order).success(function(response){
                    $scope.Result = order;
                });  
              }
            });
        });
    };

});
mainController.controller('ModalController', function($scope,inType, close) {
  var input;
  var title;
  switch(inType){
    case 'IAJ':
      input = "Take about 10 seconds, Make Json File from MYSQL Database. ";
      title = "Make Ananalsis JSON FIle";
      break;
    case 'UAT':    
      input = "Take about 5 minutes, Get Big stock data from Yahoo Finace API";
      title = "Update 10Years Stock Data";
      break;
    case 'UDT':
      input = "Take about 10 seconds, Get Daily stock data from Yahoo Finace API";
      title = "Update Daily Stock Data";
      break;
    case 'AJ':
      input = "Take about 5 minutes, Make Child Process and Run JAR File";
      title = "Run Machine Learning Java Program";
      break;
    case 'down':
      input = "Download NASAQ 100List From nasdaq.com";
      title = "Download NASDAQ 100 Company List";
      break;
  }

  $scope.textOut = input;
  $scope.modalTitle = title;

 $scope.close = function(result) {
    close(result, 500); // close, but give 500ms for bootstrap to animate
 };

});

mainController.controller('TableController', ['$scope', '$filter', function($scope, $filter) {
  var orderBy = $filter('orderBy');
  $scope.aData = globalDaily;
  $scope.orderLabel = "Ascending";
  $scope.order = function(predicate, reverse) {
    $scope.aData = orderBy($scope.aData, predicate, reverse);
    if(reverse == false)
        $scope.orderLabel = "Ascending";
    else
        $scope.orderLabel = "Descending";
};
}]);

mainController.controller('TableController2', ['$scope', '$filter', function($scope, $filter) {
  var orderBy = $filter('orderBy');
  $scope.orderLabel = "Ascending";
  $scope.order = function(predicate, reverse) {
    $scope.aData2 = orderBy($scope.aData2, predicate, reverse);
    if(reverse == false)
        $scope.orderLabel = "Ascending";
    else
        $scope.orderLabel = "Descending";
};
}]);

mainController.controller("myAnalysisController",function($scope,$http,$routeParams){
	$http.get("models/"+ $routeParams.symbol + "_analysis.json")
  .success(function(response) {
   $scope.aData2 = response;

   var Real = [];
   var Short = [];
   var scs = [];
   var macd = [];
   var vr = [];
   var rsi = [];
   var accuracy = [];
   for( var i=0; i<$scope.aData2.length ; i++)
   {
    var tempDate = Date.parse($scope.aData2[i].dates);
    tempDate += 86400000;
    Real.unshift({ x:tempDate, y: $scope.aData2[i].close });  
    scs.unshift({ x:tempDate, y: $scope.aData2[i].scs });  
    macd.unshift({ x:tempDate, y: $scope.aData2[i].macd });  
    vr.unshift({ x:tempDate, y: $scope.aData2[i].vr });  
    rsi.unshift({ x:tempDate, y: $scope.aData2[i].rsi });
    accuracy.unshift({ x:tempDate, y: $scope.aData2[i].longpre });
    if(i+1 == $scope.aData2.length)  
          Short.unshift({ x:tempDate, y: $scope.aData2[i].close }); 
    else
          Short.unshift({ x:tempDate, y: $scope.aData2[i+1].shortpre });  
    }
  
  $(function () {
      createChart = function (){
        $('#container').highcharts('StockChart',{
        rangeSelector: {
           selected: 1
        },
        title: {
            text: $routeParams.symbol + '  Historical'
        },
        yAxis: [{
            labels: {
                align: 'right',
                x: -3
            },
            title: {
                text: 'Stock Price'
            },
            height: '60%',
            lineWidth: 2
        }, {
            labels: {
                align: 'right',
                x: -3
            },
            title: {
                text: 'Index Volume'
            },
            top: '65%',
            height: '35%',
            offset: 0,
            lineWidth: 3
        }],
        legend: {
            enabled: true
        },

        series: [{
            name: 'Real',
            id: 'real',
            type: 'spline',
            yAxis: 0,
            marker: {
                radius: 5,
                symbol: 'diamond'
            },
            data: Real
        }, {
            name: 'Prediction',
            type: 'spline',
            yAxis: 0,
            data: Short
        }, {
            name: 'RSI',
            type: 'column',
            yAxis: 1,
            data: rsi,
           visible: false
        }, {
            name: 'SCS',
            type: 'column',
            yAxis: 1,
            data: scs,
           visible: false
        }, {
            name: 'MACD',
            type: 'column',
            yAxis: 1,
            data: macd,
           visible: false
        }, {
            name: 'Volume Rate',
            type: 'column',
            yAxis: 1,
            data: vr,
           visible: false
        }, {
            name: 'Accuracy Rate',
            type: 'column',
            yAxis: 1,
            data: accuracy
        }]});
    }
});   

createChart();
});
});
