package kr.co.edsk.ojt.security;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.web.authentication.AuthenticationSuccessHandler;

public class LoginSuccessHandler implements AuthenticationSuccessHandler {
	@Override
	public void onAuthenticationSuccess(HttpServletRequest req,HttpServletResponse res,
			Authentication auth) throws IOException,ServletException {
		boolean flag = false;
		for (GrantedAuthority authority : auth.getAuthorities()) {
			if (authority.getAuthority().contentEquals("ROLE_NOTAUTH")) {
				flag = true;
				break;
			}
		}
		if(flag){
			res.sendRedirect(req.getContextPath() + "/login_ready");			
		}else{
			res.sendRedirect(req.getContextPath() + "/login_success");			
		}
	}

}
