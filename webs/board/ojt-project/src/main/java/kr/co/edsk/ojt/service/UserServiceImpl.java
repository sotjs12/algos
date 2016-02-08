package kr.co.edsk.ojt.service;

import java.util.List;

import javax.annotation.Resource;

import org.springframework.stereotype.Service;

import kr.co.edsk.ojt.model.UserData;
import kr.co.edsk.ojt.model.UserMapper;

@Service(value = "userService")
public class UserServiceImpl implements UserService {

    @Resource(name = "userMapper")
	private UserMapper userMapper;
	
	
	@Override
	public UserData insert(UserData user) {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public UserData update(UserData user) {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public UserData getById(String id) {
		// TODO Auto-generated method stub
		return this.userMapper.getById(id);
	}
	@Override
	public List<UserData> getAll() {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public long count() {
		// TODO Auto-generated method stub
		return 0;
	}
}
