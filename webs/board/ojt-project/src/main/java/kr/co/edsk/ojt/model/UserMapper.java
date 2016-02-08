package kr.co.edsk.ojt.model;

import java.util.List;

import org.springframework.stereotype.Repository;

@Repository(value = "userMapper")
public interface UserMapper {
	public UserData insert(UserData user);
	public UserData update(UserData user);
	public UserData getById(String id);
	public void deleteById(String id);
	public List<UserData> getAll();
	public long count();
}
