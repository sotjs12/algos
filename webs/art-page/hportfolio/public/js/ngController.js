var potterControllers = angular.module('potterControllers',[]);

potterControllers.controller("init",['$scope','$http',function($scope,$http){
    if(!$scope.hasOwnProperty("page")){
		$http.get("./husers/"+domain+".json").success(function(response) {
	        $scope.page = response;
	     });
    }    
}]);

potterControllers.controller("mainCtr",['$scope',function($scope){
	var index = Math.floor(Math.random() * $scope.page.mainImg.length);
	$scope.mainImgUrl = "img/"+domain+"/main-img/"+$scope.page.mainImg[index];	
}]);

potterControllers.controller("artCtr",['$scope','$http',function($scope,$http){
           
}]);