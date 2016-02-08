
package kr.co.edsk.ojt.controller;

import javax.servlet.http.HttpSession;

import kr.co.edsk.ojt.security.CustomUserDetails;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

/**
* <pre>
* Login 컨트롤러
* 로그인 세션 처리 및 로그인 비즈니스 컨트롤러
* </pre>
* 
* 
* @Company : (주)한국이디에스
* @Author  : hoon
* @Date    : 2016. 1. 14. 오전 11:01:49
* @Version : 4.0
*/
@Controller
public class LoginController {
	private static final Logger logger = LoggerFactory.getLogger(LoginController.class);
	
    /**
     * Simply selects the home view to render by returning its name.
     */
    @RequestMapping(value = "login", method = RequestMethod.GET)
    public void login(HttpSession session) {
        logger.info("Welcome login! {}", session.getId());
    }     
    @RequestMapping(value = "logout", method = RequestMethod.GET)
    public void logout(HttpSession session) {
        CustomUserDetails userDetails = (CustomUserDetails)session.getAttribute("userLoginInfo");         
        logger.info("Welcome logout! {}, {}", session.getId(), userDetails.getUsername());         
        session.invalidate();
    }     
    @RequestMapping(value = "login_success", method = RequestMethod.GET)
    public void login_success(HttpSession session) {
        CustomUserDetails userDetails = (CustomUserDetails)SecurityContextHolder.getContext().getAuthentication().getDetails();         
        logger.info("Welcome login_success! {}, {}", session.getId(), userDetails.getUsername() + "/" + userDetails.getPassword());
        session.setAttribute("userLoginInfo", userDetails);
    }
    @RequestMapping(value = "/login_ready", method = RequestMethod.GET)
    public String login_ready() {  
        return "/login_ready";   
    }   
    @RequestMapping(value = "/login_failed", method = RequestMethod.GET)
    public String login_failed() { 
        return "/login_failed";            	
    }  
     
}
