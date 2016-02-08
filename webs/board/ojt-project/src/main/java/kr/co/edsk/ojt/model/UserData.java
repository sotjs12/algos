package kr.co.edsk.ojt.model;

import javax.validation.constraints.Size;

public class UserData {
	@Size(max=20) 
	String id;
	@Size(max=20) 
	String nickname;
	String password;
	int level;
	
	public UserData() {
	}	
	public UserData( String id, String password, String nickname,int level) {
		super();
		this.id = id;
		this.password = password;
		this.nickname = nickname;
		this.level = level;
	}
	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getNickname() {
		return nickname;
	}

	public void setNickname(String nickname) {
		this.nickname = nickname;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public int getLevel() {
		return level;
	}

	public void setLevel(int level) {
		this.level = level;
	}
	
	public String toString() {
		return "";
	}

	public boolean equals(Object obj) {
		if (this == obj) return true;
		if (obj == null) return false;
		if (getClass() != obj.getClass()) return false;
		UserData other = (UserData) obj;
		if (id != other.id) return false;
		return true;
	}

}
