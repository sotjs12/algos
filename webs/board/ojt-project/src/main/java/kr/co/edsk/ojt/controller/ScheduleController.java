/**
 * 
 */
package kr.co.edsk.ojt.controller;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.annotation.Resource;
import javax.servlet.http.HttpSession;

import kr.co.edsk.ojt.model.ScheduleData;
import kr.co.edsk.ojt.service.ScheduleServiceImpl;

import org.apache.logging.log4j.core.config.plugins.validation.constraints.Required;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * <pre>
 * �뒪罹먯Ⅴ 愿�由� 而⑦듃濡ㅻ윭
 * �뒪罹먯Ⅴ ajax 諛� rest 留ㅽ븨 而⑦듃濡ㅻ윭 
 * </pre>
 * 
 * 
 * @Company : (二�)�븳援��씠�뵒�뿉�뒪
 * @Author  : hoon
 * @Date    : 2016. 1. 14. �삤�썑 2:56:22
 * @Version : 4.0
 */

@Controller
public class ScheduleController {
	private static final Logger logger = LoggerFactory.getLogger(LoginController.class);
	@Resource(name = "scheduleService")
	ScheduleServiceImpl ScheduleService;
    /**
     * Simply selects the home view to render by returning its name.
     */
    @RequestMapping(value = "schedule", method = RequestMethod.GET)
    public String scheduleHome(HttpSession session,Model model) {
        logger.info("connect schedule", session.getId());
        return "schedule/schedule";
    }
    /*
    @RequestMapping(value="/jsonData", method=RequestMethod.POST,consumes="application/json")
    public @ResponseBody List<Map<String,Object>> getCheckListSpecificByAjax(@RequestBody Map<String,Object> map){   
            List<Map<String,Object>> list = ScheduleService.getAll();     
            return list;
    }
    */
    @RequestMapping(value = "schedule/schedule_list", method = RequestMethod.GET)
	public @ResponseBody List<ScheduleData> get_list(ModelMap model) {
		List<ScheduleData> ScheduleDataList = new ArrayList<ScheduleData>();
		ScheduleDataList = ScheduleService.getAll();
		return ScheduleDataList;
	}
    @RequestMapping(value = "schedule/schedule_list2", method = RequestMethod.GET)
	public @ResponseBody List<ScheduleData> get_list2(@RequestParam(value = "offset") Integer offset) {
		List<ScheduleData> ScheduleDataList = new ArrayList<ScheduleData>();
		ScheduleDataList = ScheduleService.getByOffset(offset);
		return ScheduleDataList;
	}
    @RequestMapping(value = "schedule/schedule_count", method = RequestMethod.GET)
	public @ResponseBody long schedule_count() {  	
    	long cnt = ScheduleService.count();
		return cnt;
	}
    
    @RequestMapping(value="schedule/schedule_insert", method=RequestMethod.POST)
    public @ResponseBody ScheduleData schedule_insert(@RequestBody String schedule) throws JsonParseException, JsonMappingException, IOException{ 	
    	ObjectMapper mapper = new ObjectMapper();
    	ScheduleData ms = mapper.readValue(schedule, ScheduleData.class);
    	ScheduleService.insert(ms);
    	return ms;
    }
    @RequestMapping(value="schedule/schedule_update", method=RequestMethod.PUT)
    public @ResponseBody ScheduleData schedule_update(@RequestBody String schedule) throws JsonParseException, JsonMappingException, IOException{ 	
    	ObjectMapper mapper = new ObjectMapper();
    	ScheduleData ms = mapper.readValue(schedule, ScheduleData.class);
    	ScheduleService.update(ms);
    	return ms;
    }
    @RequestMapping(value="schedule/schedule_delete", method=RequestMethod.POST)
    public @ResponseBody ScheduleData schedule_delete(@RequestBody String schedule) throws JsonParseException, JsonMappingException, IOException{ 	
    	ObjectMapper mapper = new ObjectMapper();
    	ScheduleData ms = mapper.readValue(schedule, ScheduleData.class);
    	ScheduleService.deleteById(ms.getS_idx());
    	return ms;
    }
}
