<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form"%>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags"%>

<modal visible="showModal">
<form class="form-horizontal" role="form">
	<div class="form-group">
		<label for="pageTitle" class="col-sm-2 control-label" minlength=1>제목
			: </label>
		<div class="col-md-8">
			<input class="form-control" ng-model="sPost.s_title"
				ng-disabled="isShowCheck2">
		</div>
	</div>

	<label for="pageTitle" class="col-sm-2 control-label" minlength=1>시작일:
	</label>
	<div class="col-md-4" ng-show="isShowCheck">
		<p class="input-group">
			<input type="text" class="form-control" uib-datepicker-popup
				ng-model="sPost.s_from_date" is-open="popup1.opened"
				close-text="Close" /> <span class="input-group-btn">
				<button type="button" class="btn btn-default" ng-click="open1()">
					<i class="glyphicon glyphicon-calendar"></i>
				</button>
			</span>
		</p>
	</div>
	<div class="col-md-4" ng-show="isShowCheck2">
	  	<p>{{sPost.s_from_date | date:'yyyy-MM-dd'}}</p>
	</div>
	<label for="pageTitle" class="col-sm-2 control-label" minlength=1>종료일:
	</label>
	<div class="col-md-4" ng-show="isShowCheck">
		<p class="input-group">
			<input type="text" class="form-control" uib-datepicker-popup
				ng-model="sPost.s_to_date" is-open="popup2.opened"
				close-text="Close" /> <span class="input-group-btn">
				<button type="button" class="btn btn-default" ng-click="open2()">
					<i class="glyphicon glyphicon-calendar"></i>
				</button>
			</span>
		</p>
	</div>
	<div class="col-md-4" ng-show="isShowCheck2">
	 	<p>{{sPost.s_to_date | date:'yyyy-MM-dd'}}</p>
	</div>
	<div class="form-group">
		<label class="col-md-2 control-label">내용 : </label>
		<div class="col-md-8">
			<textarea ng-model="sPost.s_content" maxlength=100 cols="55"
				ng-disabled="isShowCheck2"></textarea>
		</div>
	</div>

	<div class="btn-group">
		<button type="button" class="btn btn-success"
			ng-click="comform_schedule()" ng-show="isShowCheck_b">추가 완료</button>
		<button type="button" class="btn btn-warning"
			ng-click="toggleModal(sPost.s_idx,3)" ng-show="isShowCheck2">일정
			수정</button>
		<button type="button" class="btn btn-danger"
			ng-click="delete_schedule()" ng-show="isShowCheck2">일정 삭제</button>
		<button type="button" class="btn btn-danger"
			ng-click="modify_schedule()" ng-show="isShowCheck3">수정 완료</button>
	</div>
</form>
</modal>


