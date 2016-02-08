package kr.co.edsk.ojt.service;

import java.util.List;

import kr.co.edsk.ojt.model.ScheduleData;

public interface ScheduleService {
	public int insert(ScheduleData schedule);
	public void update(ScheduleData schedule);
	public ScheduleData getById(int id);
	public void deleteById(int id);
	public List<ScheduleData> getAll();
	public List<ScheduleData> getByOffset(int offset);
	public long count();
	
}
