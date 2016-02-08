<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form"%>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags"%>

<table class="table table-hover">
	<thead>
		<tr>
			<th>번호</th>
			<th>일정</th>
			<th>From</th>
			<th>To</th>
		</tr>
	</thead>
	<tbody>
		<tr ng-repeat="s in s_list">
			<td>{{ s.s_idx }}</td>
			<td><a href="" ng-click="toggleModal(s.s_idx,2)">{{ s.s_title }}</a></td>
			<td>{{ s.s_from_date | date:'yyyy-MM-dd'}}</td>
			<td>{{ s.s_to_date | date:'yyyy-MM-dd'}}</td>
		</tr>
	</tbody>
</table>
<div>

<uib-pagination boundary-links="true" total-items="totalItems" ng-model="currentPage" class="pagination-sm" 
	previous-text="&lsaquo;" next-text="&rsaquo;" first-text="&laquo;"
	last-text="&raquo;" items-per-page="sPerPage" ng-change="pageChanged()"></uib-pagination>
    <pre>Page: {{currentPage}} / {{totalPages}}</pre>
</div>



