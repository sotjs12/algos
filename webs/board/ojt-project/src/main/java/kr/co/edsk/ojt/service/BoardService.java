/**
 * 
 */
package kr.co.edsk.ojt.service;

import java.util.List;

import kr.co.edsk.ojt.model.BoardData;

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

public interface BoardService {
	
	/**
	  * <pre>
	  *	
	  * </pre>
	  * @param idx
	  * @return
	*/
	public BoardData boardView(int idx);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @return
	*/
	public List<BoardData> getAll();
	/**
	  * <pre>
	  *
	  * </pre>
	  * @return
	*/
	public List<BoardData> getList();
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param idx
	*/
	public void addHit(int idx);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param boardData
	*/
	public void boardWrite(BoardData boardData);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param user_id
	  * @param idx
	*/
	public void boardModify(String user_id, int idx);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param user_id
	  * @param b_group
	*/
	public void boardDelete(String user_id, int b_group);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param boardData
	*/
	public void replyWrite(BoardData boardData);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param b_group
	  * @param b_level
	*/
	public void updateLevel(int b_group, int b_level);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param b_parent
	*/
	public void getParent(int b_parent);
	/**
	  * <pre>
	  *
	  * </pre>
	  * @param idx
	*/
	public void replyDelete(int idx);

}
