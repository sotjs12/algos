<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%--	목록을 출력하자.	 --%>
	<table align="center" width="1000" border="1">
			<tr>
				<th width="10%">번호</th>
				<th width="60%">제목</th>
				<th width="10%">작성자</th>
				<th width="10%">작성날짜</th>
				<th width="10%">조회수</th>
			</tr>

	<c:forEach var="data" items="${RESULT}" varStatus="status">
			<tr>
	<!-- idx는 데이터 빈 클래스의 getIdx에서 따온것이다. -->
				<td>${data.idx}</td>
				<td>
					<a href="./${data.idx}">
						${data.b_title}
					</a>
				</td>
				<td>${data.user_name}</td>
				<td>${data.b_date}</td>
				<td>${data.b_hit}</td>
			</tr>
	</c:forEach>
	</table>
	<table align="center" width="1000">
			<tr>
				<td align="right">
					<a href="./write">글쓰기</a>
				</td>
			</tr>
	</table>
</body>
</html>