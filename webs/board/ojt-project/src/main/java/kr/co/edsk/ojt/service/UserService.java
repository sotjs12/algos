package kr.co.edsk.ojt.service;

import java.util.List;

import kr.co.edsk.ojt.model.UserData;


public interface UserService {
	public UserData insert(UserData user);
	public UserData update(UserData user);
	public UserData getById(String id);
	public List<UserData> getAll();
	public long count();
}
