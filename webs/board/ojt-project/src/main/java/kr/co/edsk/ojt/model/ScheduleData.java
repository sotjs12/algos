/**
 * 
 */
package kr.co.edsk.ojt.model;

import java.util.Date;

import javax.validation.constraints.Size;

/**
 * <pre>
 *	USER_SCHEDULE 테이블과 매핑될 모델클레스
 *	ScheduleMapper 인터페이스와 scheduleMapper.xml 에의해 매핑되어 사용된다.
 *	Call Service 는 ScheduleServiceImpl 이다. 
 * </pre>
 * 
 * 
 * @Company : (주)한국이디에스
 * @Author  : hoon
 * @Date    : 2016. 1. 14. 오후 6:38:17
 * @Version : 4.0
 */

public class ScheduleData {
	private int s_idx;
	private String user_id;
	@Size(min=1, max=100) private String s_title;
	@Size(max=500) private String s_content;
	private Date s_from_date;
	private Date s_to_date;
	
	public ScheduleData(){
		
	}
	
	public ScheduleData(String user_id,String s_title,Date s_from_date,Date s_to_date,String s_content){
		this.user_id = user_id;
		this.s_title = s_title;
		this.s_content = s_content;
		this.s_from_date = s_from_date;	
		this.s_to_date = s_to_date;
	}
	/**
	 * <pre>
	 * return the s_idx
	 * </pre>
	 * @return 
	 */
	
	public int getS_idx() {
		return s_idx;
	}
	/**
	 * <pre>
	 * the s_idx to set
	 * </pre>
	 * @param s_idx 
	 */
	
	public void setS_idx(int s_idx) {
		this.s_idx = s_idx;
	}
	/**
	 * <pre>
	 * return the s_title
	 * </pre>
	 * @return 
	 */
	
	public String getS_title() {
		return s_title;
	}
	/**
	 * <pre>
	 * the s_title to set
	 * </pre>
	 * @param s_title 
	 */
	
	public void setS_title(String s_title) {
		this.s_title = s_title;
	}
	/**
	 * <pre>
	 * return the s_from_date
	 * </pre>
	 * @return 
	 */
	
	public Date getS_from_date() {
		return s_from_date;
	}
	/**
	 * <pre>
	 * the s_from_date to set
	 * </pre>
	 * @param s_from_date 
	 */
	
	public void setS_from_date(Date s_from_date) {
		this.s_from_date = s_from_date;
	}
	/**
	 * <pre>
	 * return the s_to_date
	 * </pre>
	 * @return 
	 */
	
	public Date getS_to_date() {
		return s_to_date;
	}
	/**
	 * <pre>
	 * the s_to_date to set
	 * </pre>
	 * @param s_to_date 
	 */
	
	public void setS_to_date(Date s_to_date) {
		this.s_to_date = s_to_date;
	}
	/**
	 * <pre>
	 * return the s_content
	 * </pre>
	 * @return 
	 */
	
	public String getS_content() {
		return s_content;
	}
	/**
	 * <pre>
	 * the s_content to set
	 * </pre>
	 * @param s_content 
	 */
	
	public void setS_content(String s_content) {
		this.s_content = s_content;
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
}
