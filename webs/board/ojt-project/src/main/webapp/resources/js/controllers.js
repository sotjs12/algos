/**
 * angularjs 컨트롤러 모음
 */

var scheduleApp = angular.module('scheduleApp',	[ 'ngAnimate', 'ui.bootstrap']);

scheduleApp.controller('TabController', [ '$scope', function($scope) {
	$scope.tab = 1;
	$scope.setTab = function(newTab) {
		$scope.tab = newTab;
	};
	$scope.isSet = function(tabNum) {
		return $scope.tab === tabNum;
	};
} ]);


scheduleApp.controller('ModalCtrl', ['$scope', '$http','$window',function($scope, $http,$window) {
	$scope.showModal = false;
	$scope.isShowCheck = true;
	$scope.isShowCheck2 = false;
	$scope.isShowCheck3 = false;
	$scope.isShowCheck_b = true;	 
	var curTime = new Date();	
	var getDummy = function(){
		return {
			s_title : "",
			s_content:"",
			user_id : "",
			s_from_date:curTime,
			s_to_date:curTime
	};};
	
	$scope.open1 = function() {
	    $scope.popup1.opened = true;
	};
	$scope.popup1 = {
		    opened: false
		};
	$scope.open2 = function() {
	    $scope.popup2.opened = true;
	};
	$scope.popup2 = {
		    opened: false
		};
	$scope.sPost = getDummy();
	var restFunction = {
			getPageList: function(){	//temp
				return $http.get("./schedule/schedule_list");;				 
			},
			getPage: function(pIdx){
				return $http.get("./schedule/schedule_list2",{params: {offset: pIdx}});			 
			},	
			getCount: function(){
				return $http.get("./schedule/schedule_count");					
			},
			insertS : function(nSchedule){
				return $http.post("./schedule/schedule_insert",nSchedule);
			},
			updateS : function(uSchedule){
				return $http.put("./schedule/schedule_update",uSchedule);				
			},
			deleteS : function(dSchedule){
				return $http.post("./schedule/schedule_delete",dSchedule);				
			}			
	};
	var resC = restFunction.getCount();
	resC.success(function(data, status, headers, config) {
		$scope.sPerPage = 15;
		$scope.totalItems  = data;
		$scope.totalPages  = parseInt($scope.totalItems/$scope.sPerPage+1);
		$scope.currentPage = 1;
		var res = restFunction.getPage(0);
		res.success(function(data, status, headers, config) {
			$scope.s_list = data;
		}).error(function(data, status, headers, config) {
			$window.alert("fail!");
		});
	}).error(function(data, status, headers, config) {
		$window.alert("fail!");
	});
	var setPage = function (pageNo) {
		$scope.currentPage = pageNo;
		var res = restFunction.getPage((pageNo-1)*$scope.sPerPage);
		res.success(function(data, status, headers, config) {
			$scope.s_list = data;
		}).error(function(data, status, headers, config) {
			$window.alert("fail!");
		});
	};	 
	$scope.pageChanged = function() {
		setPage($scope.currentPage);
	};
	

	$scope.toggleModal = function(idx, mType) {
		if (mType == 0) { //close all
			$scope.showModal = !$scope.showModal;
		}
		else if (mType == 1) {
			$scope.sPost = getDummy();
			$scope.dialog_title = "일정 추가";
			$scope.isShowCheck = true;
			$scope.isShowCheck2 = false;
			$scope.isShowCheck3 = false;
			$scope.isShowCheck_b = true;
			$scope.showModal = !$scope.showModal;
		}
		else if (mType == 2){
			$scope.dialog_title = "일정  상세";
			$scope.isShowCheck = false;
			$scope.isShowCheck2 = true;
			$scope.isShowCheck3 = false;
			$scope.isShowCheck_b = false;
			for(i in $scope.s_list){
				if($scope.s_list[i].s_idx == idx){
					$scope.sPost = $scope.s_list[i];
					$scope.showModal = !$scope.showModal;	
					break;
				}
			}		
		}
		else if (mType == 3){
			$scope.dialog_title = "일정  수정";
			$scope.isShowCheck = true;
			$scope.isShowCheck2 = false;
			$scope.isShowCheck3 = true;
			$scope.isShowCheck_b = false;
		}
	};
	$scope.comform_schedule = function() {
		//이후 user_id 세션검사 및 휴효성검증 추가
		restFunction.insertS($scope.sPost).success(function(response){
	    	$scope.s_list.push(response);
	    	$scope.showModal = false;
	    	$scope.sPost = getDummy();
	    }).error(function(error){
			$window.alert("fail!");
	    });
	}	
	$scope.modify_schedule = function(){
		restFunction.updateS($scope.sPost).success(function(response){
			for(i in $scope.s_list){
			if($scope.s_list[i].s_idx == $scope.sPost.s_idx){
				$scope.s_list[i] = $scope.sPost;
				$scope.showModal = !$scope.showModal;
				$scope.sPost = getDummy();	
				break;
			}
		}
		}).error(function(error){
			$window.alert("fail!");
		});		
	}
	$scope.delete_schedule = function(){
		restFunction.deleteS($scope.sPost).success(function(response){
			for(i in $scope.s_list){
			if($scope.s_list[i].s_idx == $scope.sPost.s_idx){
				$scope.s_list.splice(i,1);
				$scope.showModal = !$scope.showModal;
				break;
			}
		}
		}).error(function(error){
			$window.alert("fail!");
		});		
	}
}]);

scheduleApp.directive('modal',function() {
					return {
						template : '<div class="modal fade">'
								+ '<div class="modal-dialog">'
								+ '<div class="modal-content">'
								+ '<div class="modal-header">'
								+ '<button type="button" class="close" ng-click="toggleModal(0,0)" aria-hidden="true">&times;</button>'
								+ '<h4 class="modal-title">{{ dialog_title }}</h4>'
								+ '</div>'
								+ '<div class="modal-body" ng-transclude ></div>'
								+ '</div>' + '</div>' + '</div>',
						restrict : 'E',
						transclude : true,
						replace : true,
						scope : true,
						link : function postLink(scope, element, attrs) {
							scope.title = attrs.title;
							scope.$watch(attrs.visible, function(value) {
								if (value == true)
									$(element).modal('show');
								else
									$(element).modal('hide');
							});
						}
					};
				});