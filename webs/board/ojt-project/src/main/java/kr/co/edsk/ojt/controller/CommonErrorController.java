package kr.co.edsk.ojt.controller;

import javax.servlet.http.HttpServletRequest;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/error")
public class CommonErrorController {
	private static final Logger logger = LoggerFactory.getLogger(CommonErrorController.class);
	
	
	@RequestMapping(value = "/throwable")
	public String throwable(HttpServletRequest request,Model model){
		logger.info("throwable err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	@RequestMapping(value = "/exception")
	public String exception(HttpServletRequest request,Model model){
		logger.info("exception err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	@RequestMapping(value = "/400")
	public String pageError400(HttpServletRequest request,Model model){
		logger.info("400 err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	@RequestMapping(value = "/403")
	public String pageError403(HttpServletRequest request,Model model){
		logger.info("403 err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	@RequestMapping(value = "/404")
	public String pageError404(HttpServletRequest request,Model model){
		logger.info("404 err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	@RequestMapping(value = "/405")
	public String pageError405(HttpServletRequest request,Model model){
		logger.info("405 err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	@RequestMapping(value = "/500")
	public String pageError500(HttpServletRequest request,Model model){
		logger.info("500 err");
		model.addAttribute("msg", "에외 발생");
		return "common/commom_error";
	}
	
}
