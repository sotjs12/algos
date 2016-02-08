package kr.co.edsk.ojt.security;

import java.util.ArrayList;
import java.util.List;



import javax.annotation.Resource;

import kr.co.edsk.ojt.controller.LoginController;
import kr.co.edsk.ojt.model.UserData;
import kr.co.edsk.ojt.service.UserServiceImpl;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.security.authentication.AuthenticationProvider;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.stereotype.Component;

@Component
public class CustomAuthenticationProvider implements AuthenticationProvider {
	private static final Logger logger = LoggerFactory.getLogger(LoginController.class);
	private final int ADMIN = 0;
	private final int AUTHORIZED_USER = 1;
	private final int NOT_AUTHORIZED_USER = 2;
	
	@Resource(name = "userService")
    private UserServiceImpl userService;
    @Override
    public boolean supports(Class<?> authentication) {
        return authentication.equals(UsernamePasswordAuthenticationToken.class);
    }
  
    @Override
    public Authentication authenticate(Authentication authentication) throws AuthenticationException {
         
        String user_id = (String)authentication.getPrincipal();    
        String user_pw = (String)authentication.getCredentials();       
        logger.info("사용자가 입력한 로그인정보입니다. {}", user_id + "/" + user_pw);
        UserData logUser = this.userService.getById(user_id); 
        
        
        if(user_id.isEmpty() || user_pw.isEmpty())
            throw new BadCredentialsException("Bad credentials");
        if(logUser == null)
            throw new BadCredentialsException("Bad credentials");
        if(user_id.equals(logUser.getId())&&user_pw.equals(logUser.getPassword())){
            logger.info("정상 로그인입니다.");
            List<GrantedAuthority> roles = new ArrayList<GrantedAuthority>();
            roles.add(GetRole(logUser.getLevel()));             
            UsernamePasswordAuthenticationToken result = new UsernamePasswordAuthenticationToken(user_id, user_pw, roles);
            result.setDetails(new CustomUserDetails(user_id, user_pw,roles));
            return result;         
        }else{
            logger.info("사용자 크리덴셜 정보가 틀립니다. 에러가 발생합니다.");
            throw new BadCredentialsException("Bad credentials");
        }
    }
    private SimpleGrantedAuthority GetRole(int code){
    	switch (code) {
		case ADMIN:			
			return new SimpleGrantedAuthority("ROLE_ADMIN");
		case AUTHORIZED_USER:		
			return new SimpleGrantedAuthority("ROLE_USER");
		case NOT_AUTHORIZED_USER:			
			return new SimpleGrantedAuthority("ROLE_NOTAUTH");
		default:
			return new SimpleGrantedAuthority("ROLE_NOTAUTH");
		}
    }

}
