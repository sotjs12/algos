
package kr.co.edsk.ojt.model;

import java.util.Date;


/**
* <pre>
* 
* 
* </pre>
* 
* 
* @Company : (주)한국이디에스
* @Author  : SuJi Kim
* @Date    : 2016. 1. 14. 오후 12:49:58
* @Version : 4.0
*/

public class BoardData {
	//게시글의 순번
	private int idx;
	//게시글의 제목
	private String b_title;
	//게시글의 작성날짜
	private Date b_date;
	//게시글의 내용
	private String b_content;
	//게시글의 그룹 (원글 및 답변들을 하나의 그룹으로 묶는다.)
	private int b_group;
	//게시글의 부모글(삭제를 편하게 하기 위함)
	private int b_parent;
	//게시글의 답변 정렬순서
	private int b_orderby;
	//게시글의 들여쓰기 level 
	private int b_level;
	//게시글의 조회수
	private int b_hit;
	//유저의 ID
	private String user_id;
	//유저 NICKNAME
	private String nickname;
	
	public BoardData() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * <pre>
	 * return the idx
	 * </pre>
	 * @return 
	 */
	
	public int getIdx() {
		return idx;
	}

	/**
	 * <pre>
	 * the idx to set
	 * </pre>
	 * @param idx 
	 */
	
	public void setIdx(int idx) {
		this.idx = idx;
	}

	/**
	 * <pre>
	 * return the b_title
	 * </pre>
	 * @return 
	 */
	
	public String getB_title() {
		return b_title;
	}

	/**
	 * <pre>
	 * the b_title to set
	 * </pre>
	 * @param b_title 
	 */
	
	public void setB_title(String b_title) {
		this.b_title = b_title;
	}

	/**
	 * <pre>
	 * return the b_date
	 * </pre>
	 * @return 
	 */
	
	public Date getB_date() {
		return b_date;
	}

	/**
	 * <pre>
	 * the b_date to set
	 * </pre>
	 * @param b_date 
	 */
	
	public void setB_date(Date b_date) {
		this.b_date = b_date;
	}

	/**
	 * <pre>
	 * return the b_content
	 * </pre>
	 * @return 
	 */
	
	public String getB_content() {
		return b_content;
	}

	/**
	 * <pre>
	 * the b_content to set
	 * </pre>
	 * @param b_content 
	 */
	
	public void setB_content(String b_content) {
		this.b_content = b_content;
	}

	/**
	 * <pre>
	 * return the b_group
	 * </pre>
	 * @return 
	 */
	
	public int getB_group() {
		return b_group;
	}

	/**
	 * <pre>
	 * the b_group to set
	 * </pre>
	 * @param b_group 
	 */
	
	public void setB_group(int b_group) {
		this.b_group = b_group;
	}

	/**
	 * <pre>
	 * return the b_parent
	 * </pre>
	 * @return 
	 */
	
	public int getB_parent() {
		return b_parent;
	}

	/**
	 * <pre>
	 * the b_parent to set
	 * </pre>
	 * @param b_parent 
	 */
	
	public void setB_parent(int b_parent) {
		this.b_parent = b_parent;
	}

	/**
	 * <pre>
	 * return the b_orderby
	 * </pre>
	 * @return 
	 */
	
	public int getB_orderby() {
		return b_orderby;
	}

	/**
	 * <pre>
	 * the b_orderby to set
	 * </pre>
	 * @param b_orderby 
	 */
	
	public void setB_orderby(int b_orderby) {
		this.b_orderby = b_orderby;
	}

	/**
	 * <pre>
	 * return the b_level
	 * </pre>
	 * @return 
	 */
	
	public int getB_level() {
		return b_level;
	}

	/**
	 * <pre>
	 * the b_level to set
	 * </pre>
	 * @param b_level 
	 */
	
	public void setB_level(int b_level) {
		this.b_level = b_level;
	}

	/**
	 * <pre>
	 * return the b_hit
	 * </pre>
	 * @return 
	 */
	
	public int getB_hit() {
		return b_hit;
	}

	/**
	 * <pre>
	 * the b_hit to set
	 * </pre>
	 * @param b_hit 
	 */
	
	public void setB_hit(int b_hit) {
		this.b_hit = b_hit;
	}

	/**
	 * <pre>
	 * return the user_id
	 * </pre>
	 * @return 
	 */
	
	public String getUser_id() {
		return user_id;
	}

	/**
	 * <pre>
	 * the user_id to set
	 * </pre>
	 * @param user_id 
	 */
	
	public void setUser_id(String user_id) {
		this.user_id = user_id;
	}

	/**
	 * <pre>
	 * return the nickname
	 * </pre>
	 * @return 
	 */
	
	public String getNickname() {
		return nickname;
	}

	/**
	 * <pre>
	 * the nickname to set
	 * </pre>
	 * @param nickname 
	 */
	
	public void setNickname(String nickname) {
		this.nickname = nickname;
	}


	

}
