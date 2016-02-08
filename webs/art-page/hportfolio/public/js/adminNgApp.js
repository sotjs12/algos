var app = angular.module('papp',['ui.bootstrap','ngFileUpload']);


app.controller("adminInit",['$scope','$http','Upload', '$timeout',function($scope,$http, Upload, $timeout){
    $scope.showSetting = false;
    $scope.showProgress = false;
    $scope.showAboutModal = false;
    $scope.showArtSetModal = false;
    $scope.showDesignSetModal = false;
    var bgFile;
    var socialFile;
    var pbgFile;
    var psocialFile;
    var potterFile;
    var ppotterFile;
    if(!$scope.hasOwnProperty("page")){
      $http.get("./husers/"+domain+".json").success(function(response) {
            $scope.page = response;  
            $scope.tPage  =   JSON.parse(JSON.stringify(response));
            $scope.userImgUrl = "img/"+domain+"/";
            $scope.husers = {};
            for(var user in husers)
              if(husers[user].hasOwnProperty("Domain"))
                $scope.husers[husers[user].Domain] = husers[user].Domain;
      });
      ////////////////////////////////////////////////////////
      $scope.newArt = function(){
        var dumy = {
          "title":"",
          "metirial":"",
          "size":"",
          "date":"",
          "description":"",
          "artImgUrls":[]
        };
        $scope.tPage.artImg.unshift(dumy);
      }
      $scope.artCtrl = function(){
        $scope.showArtSetModal = !$scope.showArtSetModal;
        $scope.tPage.artImg = JSON.parse(JSON.stringify($scope.page.artImg));
      }
      $scope.addArt = function(target){
        target.artImgUrls.push("");
      }
      $scope.killArt = function(i){         
        $scope.tPage.artImg.splice(i, 1); 
      }
      $scope.removeArt = function(target,i){
         target.artImgUrls.splice(i, 1); 
      }
      $scope.setArtCtrl = function(){
        $scope.page.artImg = JSON.parse(JSON.stringify($scope.tPage.artImg));     
      }
////////////////////////////////////////////////////////////////////////////////
      $scope.designCtrl = function(){
        $scope.showDesignSetModal = !$scope.showDesignSetModal;
        $scope.tPage.designImg = JSON.parse(JSON.stringify($scope.page.designImg));     
      }
      $scope.addDesign = function(target){
        var dumy={
          dImg:"",
          dInfo:""
        };
        target.designImgObject.push(dumy);
      }
      $scope.killDesign = function(i){         
        $scope.tPage.designImg.splice(i, 1); 
      }
      $scope.removeDesign = function(target,i){
         target.designImgObject.splice(i, 1); 
      }
      $scope.newDesign = function(){
        var dumy = {
          "title":"",
          "description":"",
          "designImgObject":[]
        };
        $scope.tPage.designImg.unshift(dumy);
      }
      $scope.setDesignCtrl = function(){
        $scope.page.designImg = JSON.parse(JSON.stringify($scope.tPage.designImg));          
      }
/////////////////////////////////////////////////////////////////////////////////////      
      $scope.aboutCtrl = function(){
        $scope.showAboutModal = !$scope.showAboutModal;
        $scope.tPage.artistInfo.potterImg = $scope.page.artistInfo.potterImg;
        potterFile = ppotterFile;
      }
      $scope.setAboutCtrl = function(){
        $scope.page.artistInfo.potterImg = $scope.tPage.artistInfo.potterImg;
        ppotterFile = potterFile;
        $scope.page.artistInfo.artistStatement = $scope.tPage.artistInfo.artistStatement;
      }
      $scope.toggleModalAdmin = function(){
        $scope.tPage.socialImg = $scope.page.socialImg;
        $scope.tPage.mainBgImg = $scope.page.mainBgImg;
        $scope.showSetting = !$scope.showSetting;
        bgFile = pbgFile;
        socialFile = psocialFile;
      };
      $scope.defulatPreSet = function(){
        $scope.page.pageTitle = $scope.tPage.pageTitle;
        $scope.page.navFontColor = $scope.tPage.navFontColor;
        $scope.page.artistSlogan = $scope.tPage.artistSlogan;
        $scope.page.artSlogan = $scope.tPage.artSlogan;
        $scope.page.designSlogan = $scope.tPage.designSlogan;
        $scope.page.displayName = $scope.tPage.displayName;
        $scope.page.socialImg = $scope.tPage.socialImg;
        $scope.page.mainBgImg = $scope.tPage.mainBgImg;
        $scope.page.friends = $scope.tPage.friends;
        pbgFile = bgFile;
        psocialFile = socialFile;
      };
      $scope.bgPreLoad = function(file){
        $scope.tPage.mainBgImg = file;
      }
      $scope.imageUpload = function(element,Case){
          var reader = new FileReader();
          switch(Case){
            case "bg":
              reader.onload = $scope.bgImageIsLoaded;
              bgFile = element.files[0];
              break;
            case "social":
              reader.onload = $scope.socialImageIsLoaded;
              socialFile = element.files[0];
              break;
            case "potter":
              reader.onload = $scope.potterImageIsLoaded;
              potterFile = element.files[0];
              break;
          }
          reader.readAsDataURL(element.files[0]);
      };
      $scope.bgImageIsLoaded = function(e){
          $scope.$apply(function() {
              $scope.tPage.mainBgImg = e.target.result;              
          });
      };
      $scope.socialImageIsLoaded = function(e){
          $scope.$apply(function() {
              $scope.tPage.socialImg = e.target.result;              
          });
      };
      $scope.potterImageIsLoaded = function(e){
          $scope.$apply(function() {
              $scope.tPage.artistInfo.potterImg = e.target.result;              
          });
      };
      var upsize =0;
      var upsize2 =0;
      $scope.confirm = function() {
        $scope.progressPercentage=0;
        $scope.showProgress = true;
        if(pbgFile != null && pbgFile.type.indexOf('image') != -1){
          $scope.upload(pbgFile,'bg');
          upsize++;
        }
        if(psocialFile != null && psocialFile.type.indexOf('image') != -1){
          $scope.upload(psocialFile,'social');
          upsize++;
        }
        if(ppotterFile != null && ppotterFile.type.indexOf('image') != -1){
          $scope.upload(ppotterFile,'potter');
          upsize++;
        }
        if(upsize == 0){
          $scope.progressPercentage = 100;
          $http.post('/defualtJson/'+domain,JSON.stringify($scope.page)).success(function(data, status) {
            console.log(data);
          });
        }
      };
    } 

    $scope.upload = function (file,type) {
        Upload.upload({
            url: '/defualtSet/'+domain,
            fields: {'target':type },
            method:'POST',
            file: file
        }).success(function (data, status, headers, config) {
            upsize2++;
            if(upsize2 == upsize){
              $scope.progressPercentage = 100;
              $http.post('/defualtJson/'+domain,JSON.stringify($scope.page)).success(function(data, status) {
                console.log(data);
              });
            }else{              
              $scope.progressPercentage= (upsize2/upsize)*100;
            }
        }).error(function (data, status, headers, config) {
            console.log('error status: ' + status);
        })
    };
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