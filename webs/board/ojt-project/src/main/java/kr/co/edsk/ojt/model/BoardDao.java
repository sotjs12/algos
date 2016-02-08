package kr.co.edsk.ojt.model;

import java.util.List;

import javax.annotation.Resource;

import org.springframework.stereotype.Service;

@Service(value = "boardDao")
public class BoardDao {

	@Resource(name = "boardMapper")
	private	BoardMapper boardMapper;
	
	//게시글 전체 리스트
	public List<BoardData> getList() {
		return this.boardMapper.getList();
	}
	//게시글 총 갯수
	/*
	public List<BoardData> getMax() {
		return this.boardMapper.getMax();
	}
	//게시판 목록 출력
	public List<BoardData> getAll() {
		return this.boardMapper.getAll();
	}
	//조회수 증가
	public void hitadd(int b_hit) {
		this.boardMapper.hitadd(b_hit);;
	}
	//게시글 상세보기
	public void getview(int idx) {
		this.boardMapper.getview(idx);
	}
	//게시판 글쓰기 
	public void bwrite(BoardData boardData){
		this.boardMapper.bwrite(boardData);
	}
	//게시판 수정하기
	public void bmodify(BoardData boardData){
		this.boardMapper.bmodify(boardData);
	}
	//게시글 삭제하기(최상위글 삭제)
	public void bdelete(String user_id) {
		this.boardMapper.bdelete(user_id);
	}
	//게시글 답변쓰기
	public void rewrite(BoardData boardData){
		this.boardMapper.rewrite(boardData);
	}
	//게시글 답변쓴 후 순서 갱신
	public void updatelevel(int b_group, int b_level) {
		this.boardMapper.updatelevel(b_group, b_level);
	}
	//답변삭제하기 전 부모글 확인
	// 답변글 삭제시 그 밑의 답변이 parent번호를 가지고 있으므로 함께 삭제
	public void getparent(int b_parent) {
		this.getparent(b_parent);
	}
	//답변 삭제
	public void rdelete(int idx) {
		this.boardMapper.rdelete(idx);
	}
*/
	
}
