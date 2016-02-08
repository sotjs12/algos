package kr.co.edsk.ojt.service;

import java.util.List;

import javax.annotation.Resource;

import kr.co.edsk.ojt.model.BoardData;
import kr.co.edsk.ojt.model.BoardMapper;

import org.springframework.stereotype.Service;

/**
 * <pre>
 * 
 * 
 * </pre>
 * 
 * 
 * @Company : (주)한국이디에스
 * @Author  : SuJi Kim
 * @Date    : 2016. 1. 14. 오후 12:37:41
 * @Version : 4.0
 */

@Service(value = "boardService")
public class BoardServiceImpl implements BoardService {
	@Resource(name = "boardMapper")
	private BoardMapper boardMapper;

	@Override
	public BoardData boardView(int idx) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<BoardData> getAll() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<BoardData> getList() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void addHit(int idx) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void boardWrite(BoardData boardData) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void boardModify(String user_id, int idx) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void boardDelete(String user_id, int b_group) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void replyWrite(BoardData boardData) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void updateLevel(int b_group, int b_level) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void getParent(int b_parent) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void replyDelete(int idx) {
		// TODO Auto-generated method stub
		
	}

	

}
