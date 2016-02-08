package kr.co.edsk.ojt.security;

import java.util.Collection;
import java.util.List;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

public class CustomUserDetails implements UserDetails {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String username;
    private String password;
    List<GrantedAuthority> roles;
    
    public CustomUserDetails(String userName, String password,List<GrantedAuthority> roles)
    {
        this.username = userName;
        this.password = password;
        this.roles = roles;
    }
	/**
	 * <pre>
	 * return the roles
	 * </pre>
	 * @return 
	 */
	
	public List<GrantedAuthority> getRoles() {
		return roles;
	}
	/**
	 * <pre>
	 * the roles to set
	 * </pre>
	 * @param roles 
	 */
	
	public void setRoles(List<GrantedAuthority> roles) {
		this.roles = roles;
	}

	@Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return roles;
    }
  
    @Override
    public String getPassword() {
        return password;
    }
  
    @Override
    public String getUsername() {
        return username;
    }
  
    @Override
    public boolean isAccountNonExpired() {
        return true;
    }
  
    @Override
    public boolean isAccountNonLocked() {
        return true;
    }
  
    @Override
    public boolean isCredentialsNonExpired() {
        return true;
    }
  
    @Override
    public boolean isEnabled() {
        return true;
    }

}
