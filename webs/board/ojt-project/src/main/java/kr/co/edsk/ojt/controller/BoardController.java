package kr.co.edsk.ojt.controller;

import java.util.List;

import javax.annotation.Resource;

import kr.co.edsk.ojt.model.BoardDao;
import kr.co.edsk.ojt.model.BoardData;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
public class BoardController {
	private static final Logger logger = LoggerFactory.getLogger(BoardController.class);
	  // Resource 어노테이션을 이용하여 BoardDao 선언.
	    @Resource(name = "boardDao")
	    private BoardDao boardDao;
	    
	    // 게시판 목록 불러오기 
	    /*
	    @RequestMapping(value = "/", method = RequestMethod.GET)
	    public String dispBbsList(Model model) {
	        logger.info("display view Board list");
	        List<BoardData> list = this.boardDao.getAll();
	        model.addAttribute("RESULT", list);
	        logger.info("totcal count" + list.size() );
	        return "bbs.list";

	    }
	    */
}
