<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form"%>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags"%>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Schedule</title>
<link rel="stylesheet"
	href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css"
	integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7"
	crossorigin="anonymous">
<link rel="stylesheet" href="<c:url value="/resources/css/schedule.css" />"></link>
<!-- Latest compiled and minified JavaScript -->
<script src="//code.jquery.com/jquery.min.js"></script>
<script
	src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"
	integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS"
	crossorigin="anonymous"></script>
<script
	src="https://ajax.googleapis.com/ajax/libs/angularjs/1.4.5/angular.min.js"></script>
<script src="//ajax.googleapis.com/ajax/libs/angularjs/1.4.8/angular-animate.js"></script>
<script src="//angular-ui.github.io/bootstrap/ui-bootstrap-tpls-1.0.3.js"></script>
<script src="<c:url value="/resources/js/controllers.js" />"></script>
</head>
<body ng-app="scheduleApp">
	<div ng-controller="TabController">
		<header>
			<nav class="navbar navbar-default">
				<div class="container">
					<div class="navbar-header">
						<a class="navbar-brand" href="/ojt-project/schedule">HOME</a>
					</div>
					<ul class="nav navbar-nav navbar-right">
						<li><a href="/ojt-project/board">BOARD</a></li>
						<li><a href="/ojt-project/schedule">SCHEDULE</a></li>
					</ul>
				</div>
			</nav>
		</header>
		<div class="container"  ng-controller="ModalCtrl">
			<nav class="navbar navbar-default">
				<div class="container">
					<ul class="nav navbar-nav navbar-left">
						<li ng-class="{ active: isSet(1) }"><a href
							ng-click="setTab(1)">LIST</a></li>
						<li ng-class="{ active: isSet(2) }"><a href
							ng-click="setTab(2)">CALENDAR</a></li>				
						<li><a href="" ng-click="toggleModal(0,1)">일정 추가</a></li>	
					</ul>
				</div>
			</nav>
			<div class="jumbotron">
				<div ng-show="isSet(1)">
					<%@include file="/WEB-INF/views/schedule/list_schedule.jsp"%>
				</div>
				<div ng-show="isSet(2)">
					<%@include file="/WEB-INF/views/schedule/calendar_schedule.jsp"%>
				</div>
			</div>
			<%@include file="/WEB-INF/views/schedule/modal_schedule.jsp"%>
		</div>
	</div>
</body>
</html>
