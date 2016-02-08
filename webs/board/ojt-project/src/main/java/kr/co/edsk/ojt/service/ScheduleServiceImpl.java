/**
 * 
 */
package kr.co.edsk.ojt.service;

import java.util.List;

import javax.annotation.Resource;

import org.springframework.stereotype.Service;

import kr.co.edsk.ojt.model.ScheduleData;
import kr.co.edsk.ojt.model.ScheduleMapper;

/**
 * <pre>
 * �뒪罹먯Ⅴ 愿�由� �꽌鍮꾩뒪
 * �뼱�끂�뀒�씠�뀡 諛⑹떇�쑝濡� �꽌鍮꾩뒪 �벑濡� @Service scheduleService
 * call controller  ScheduleController
 * ScheduleMapper 由ъ냼�뒪濡� 媛��졇�샂
 * </pre>
 * 
 * 
 * @Company : (二�)�븳援��씠�뵒�뿉�뒪
 * @Author  : hoon
 * @Date    : 2016. 1. 14. �삤�썑 6:58:28
 * @Version : 4.0
 */

@Service("scheduleService")
public class ScheduleServiceImpl implements ScheduleService {

	@Resource(name = "scheduleMapper")
	ScheduleMapper scheduleMapper;
	
	/* (non-Javadoc)
	 * @see kr.co.edsk.ojt.service.ScheduleService#insert(kr.co.edsk.ojt.model.ScheduleData)
	 */
	@Override
	public int insert(ScheduleData schedule) {
		return scheduleMapper.insert(schedule);
	}

	/* (non-Javadoc)
	 * @see kr.co.edsk.ojt.service.ScheduleService#update(kr.co.edsk.ojt.model.ScheduleData)
	 */
	@Override
	public void update(ScheduleData schedule) {
		scheduleMapper.update(schedule);
	}

	/* (non-Javadoc)
	 * @see kr.co.edsk.ojt.service.ScheduleService#getById(int)
	 */
	@Override
	public ScheduleData getById(int id) {
		return scheduleMapper.getById(id);
	}

	/* (non-Javadoc)
	 * @see kr.co.edsk.ojt.service.ScheduleService#deleteById(int)
	 */
	@Override
	public void deleteById(int id) {
		scheduleMapper.deleteById(id);
	}

	/* (non-Javadoc)
	 * @see kr.co.edsk.ojt.service.ScheduleService#getAll()
	 */
	@Override
	public List<ScheduleData> getAll() {
		return scheduleMapper.getAll();
	}

	/* (non-Javadoc)
	 * @see kr.co.edsk.ojt.service.ScheduleService#count()
	 */
	@Override
	public long count() {
		return scheduleMapper.count();
	}

	@Override
	public List<ScheduleData> getByOffset(int offset) {
		return scheduleMapper.getByOffset(offset);
	}

}
