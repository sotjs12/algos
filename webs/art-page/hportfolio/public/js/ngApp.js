var app = angular.module('papp',['ui.bootstrap']);


app.controller("init",['$scope','$http',function($scope,$http){
    if(!$scope.hasOwnProperty("page")){
    $http.get("./husers/"+domain+".json").success(function(response) {
          $scope.page = response;
          $scope.userImgUrl = "img/"+domain+"/";
          $scope.husers = {};
          for(var user in husers)
            if(husers[user].hasOwnProperty("Domain"))
              $scope.husers[husers[user].Domain] = husers[user].Domain;
       });
    }    
}]);

app.filter('unsafe', function($sce) {
    return function(val) {
        return $sce.trustAsHtml(val);
    };
});

app.controller('ModalCtrl', function ($scope) {
    $scope.showModal = false;
    $scope.showAboutModal = false;
    $scope.toggleModal = function(aIndex){
        $scope.showModal = !$scope.showModal;
        $scope.aIndex = aIndex;
        $scope.post = $scope.page.designImg[aIndex];
    };
    $scope.aboutCtrl = function(){
      $scope.showAboutModal = !$scope.showAboutModal;
    };
    $scope.myInterval = 10000;
});



app.directive('modal', function () {
  return {
    template: '<div class="modal fade">' + 
        '<div class="modal-dialog">' + 
          '<div class="modal-content">' + 
            '<div class="modal-header">' + 
              '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>' + 
              '<h4 class="modal-title">{{ title }}</h4>' + 
            '</div>' + 
            '<div class="modal-body" ng-transclude ></div>' + 
          '</div>' + 
        '</div>' + 
      '</div>',
    restrict: 'E',
    transclude: true,
    replace:true,
    scope:true,
    link: function postLink(scope, element, attrs) {
      scope.title = attrs.title;

      scope.$watch(attrs.visible, function(value){
        if(value == true)
          $(element).modal('show');
        else
          $(element).modal('hide');
      });

      $(element).on('shown.bs.modal', function(){
        scope.$apply(function(){
          scope.$parent[attrs.visible] = true;
        });
      });

      $(element).on('hidden.bs.modal', function(){
        scope.$apply(function(){
          scope.$parent[attrs.visible] = false;
        });
      });
    }
  };
});