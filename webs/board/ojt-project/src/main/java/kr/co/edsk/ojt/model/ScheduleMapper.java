/**
 * 
 */
package kr.co.edsk.ojt.model;

import java.util.List;

import org.springframework.stereotype.Repository;

/**
 * <pre>
 * �뒪罹먯Ⅴ Mapper �씤�꽣�럹�씠�뒪
 * scheduleMapper.xml �뿉�꽌 援ы쁽
 * �뼱�끂�뀒�씠�뀡�쑝濡� Repository �벑濡�
 * </pre>
 * 
 * 
 * @Company : (二�)�븳援��씠�뵒�뿉�뒪
 * @Author  : hoon
 * @Date    : 2016. 1. 14. �삤�썑 6:38:07
 * @Version : 4.0
 */

@Repository("scheduleMapper")
public interface ScheduleMapper {
	public int insert(ScheduleData user);
	public void update(ScheduleData user);
	public ScheduleData getById(int id);
	public void deleteById(int id);
	public List<ScheduleData> getAll();
	public List<ScheduleData> getByOffset(int offset);
	public long count();

}
