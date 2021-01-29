/*
 * 1.三个数据源格式的确定
 * 2.三个数据源对离线模式的支持
 * 3.新增对已批改数据源的读取
 * // // gb2312  utf8  
 * 
 * 
 * 
 * 
 * 
 */



$(function() {
	
	StudentDataModule.init();
	PaperDataModule.init();
	PaperAnswerModule.init();
	$('#scoreEditArea').bind('keyup', function(event) {
        if (event.keyCode == "13") {
            //回车执行查询
            $('#showNextQuestionInfoBtn').click();
        }
    });
});



/**
 * 试题数据源处理
 * [
 * {answerType:(select/edit),
 * 	questionId:题目编号, 
 * questionScore:题目分数, 
 * questionTitle:题目描述, 
 * questionItems:(如果是选择题，则是题目选项)}
 * ]
 */
var PaperDataModule = {
	paperReader : new FileReader(),
	encodingType : undefined,
	paperData : [],
	init : function() {
		// perDataModule.paperData = questionData;
		//PaperDataModule.loadPaperData();
		PaperDataModule.paperReader.onload = function() {
			if (PaperDataModule.paperReader.result) {
				var data = PaperDataModule.paperReader.result;
				data = data.replace(/\r\n/g," ");
				data = data.replace(/\t/g," ");
				//data = '\'' + data + '\'';
				PaperDataModule.paperData = JSON.parse(data);
				PaperDataModule.loadPaperData();
			}
		};
		PaperDataModule.paperReader.onloadend = function() {
			
		}
	},
	loadData : function(event) {
		PaperDataModule.encodingType = prompt("请输入编码格式", "选择编码格式");
		var input = event.target;
		var file = input.files[0];
		PaperDataModule.paperReader.readAsText(file, PaperDataModule.encodingType);
	},
	loadPaperData : function() {
		$('#questionSelectArea').html('');
		var list = PaperDataModule.paperData;
		for(var i=0, j=1; i<list.length; i++, j++) {
			if (list[i].answerType == 'select') {
				list[i].questionScore = 3;
			} else if (list[i].answerType == 'edit') {
				list[i].questionScore = 5;
			}
			var html = "<input id='questionUnit"+list[i].questionId+"' type='button' onclick='QuestionSelectModule.loadQuestionById(\""+list[i].questionId+"\")' style='height:39px; width:39px; margin-left:5px; margin-top:4px; ' value='"+list[i].questionId+"'  />"
			$('#questionSelectArea').append(html);
		}
	},
	getQuestionById : function(id) {
		var list = PaperDataModule.paperData;
		for (var i=0; i<list.length; i++) {
			var cell = list[i];
			if (cell.questionId == id) {
				return cell;
			}
		}
		return undefined;
	}
}
/**
 * 学生数据源处理
 * [{
 * studentName : 学生姓名,
 * studentId : 学生编号,
 * key : 解码关键字,
 * data : [{
 * id : 题目编号,
 * answer : 题目答案
 * }]
 * }]
 */
// 用于生产临时的studentId
var testStudentIdKey = 11010;
var StudentDataModule = {
	studentReader : new FileReader(),
	encodingType : undefined, // gb2312  utf8
	fileName : undefined,
	fileQueue : [],
	startWork : function() {
		if (StudentDataModule.fileQueue.length > 0) {
		    var temp = StudentDataModule.fileQueue[0];
		    StudentDataModule.fileName = temp.name;
		    StudentDataModule.fileQueue.splice(0, 1);
		    StudentDataModule.studentReader.readAsText(temp.target, StudentDataModule.encodingType);
		}
	},
	work : function(data, key) {
		var temp = data;
		var dataArray = temp.split(' ');
		key = dataArray[0];
		dataArray.splice(0, 1);
		var w = 0;
		for(var i=0; i<key.length; i++) {
		    w = (w + key.charCodeAt(i)) % 9;
		}
		for(var i=0, j=0; i<dataArray.length; i++, j++) {
			if (j >= key.length) {
				j = 0;
			}
			dataArray[i] = dataArray[i] ^ key.charCodeAt(j) ^ w;
			dataArray[i] = String.fromCharCode(dataArray[i]);
		}
		var jsonString = dataArray.join("");
		var obj = JSON.parse(jsonString);
		var dataObj = JSON.parse(obj.data);
		obj.data = dataObj;
		obj.key = key;
		// 临时用，因为最初设计上没有studentId这个东西
		obj.studentId = testStudentIdKey++;
		StudentSelectModule.addStudentUnit(obj);
		StudentSelectModule.currentStudentId = obj.studentId;
		PaperResult.loadCurrentStudentPaperData();
		StudentSelectModule.currentStudentId = undefined;
	},
	init : function() {
		StudentDataModule.studentReader.onload = function() {
			if(StudentDataModule.studentReader.result) {
			    StudentDataModule.work(StudentDataModule.studentReader.result, StudentDataModule.fileName);
			}
		};
		StudentDataModule.studentReader.onloadend = function() {
			StudentDataModule.startWork();
		};
		StudentDataModule.studentReader.onerror = function() {
			console.log(StudentDataModule.studentReader);
		}
	},
	loadData : function(event) {
		StudentDataModule.encodingType = prompt("请输入编码格式", "选择编码格式");
		var input = event.target;
		var i=0;
		while(i < input.files.length) {
		    var temp = input.files[i].name;
		    temp = temp.split('.');
		    temp = temp[0];
		    StudentDataModule.fileQueue[i] = {
		        name : temp,
		        target : input.files[i]
		    }
		    i++;
		}
		StudentDataModule.startWork();
	}
	
}
/**
 * 参考答案数据源处理
 * {
 * studentName : 学生姓名,
 * studentId : 学生编号,
 * key : 解码关键字,
 * data : [{
 * id : 题目编号,
 * answer : 题目答案
 * }]
 * }
 */
var PaperAnswerModule = {
	paperReader : new FileReader(),
	encodingType : undefined,
	answerData : [],
	fileName : undefined,
	key : undefined,
	init : function() { 
		// PaperAnswerModule.answerData = JSON.parse(QuestionAnswer.data);
		PaperAnswerModule.paperReader.onload = function() {
			if (PaperAnswerModule.paperReader.result) {
				var data = PaperAnswerModule.paperReader.result;
				
				var temp = data;
				var dataArray = temp.split(' ');
				var key = dataArray[0];
				dataArray.splice(0, 1);
				var w = 0;
				for(var i=0; i<key.length; i++) {
				    w = (w + key.charCodeAt(i)) % 9;
				}
				for(var i=0, j=0; i<dataArray.length; i++, j++) {
					if (j >= key.length) {
						j = 0;
					}
					dataArray[i] = dataArray[i] ^ key.charCodeAt(j) ^ w;
					dataArray[i] = String.fromCharCode(dataArray[i]);
				}
				var jsonString = dataArray.join("");
				var obj = JSON.parse(jsonString);
				var dataObj = JSON.parse(obj.data);
				obj.data = dataObj;
				PaperAnswerModule.answerData = dataObj;
			}
		};
		PaperAnswerModule.paperReader.onloadend = function() {
			
		}
	},
	loadData : function(event) {
		PaperAnswerModule.encodingType = prompt("请输入编码格式", "选择编码格式");
		var input = event.target;
		var file = input.files[0];
		var temp = input.files[0].name;
		    temp = temp.split('.');
		    temp = temp[0];
		PaperAnswerModule.fileName = temp;
		PaperAnswerModule.key = temp;
		PaperAnswerModule.paperReader.readAsText(file, PaperAnswerModule.encodingType);
	},
	getAnswerById : function(id) {
		var list = PaperAnswerModule.answerData; 
		for (var i=0; i<list.length; i++) {
			var cell = list[i];
			if (cell.id == id) {
				return cell.answer;
			}
		}
		return undefined;
	}
}




/**
 * 学生选择模块
 */
var StudentSelectModule = {
	studentArray : [],
	currentIndex : undefined,
	currentStudentId : undefined,
	currentStudentQuestionData : [],
	getStudentInfoById : function(studentId) {
		var list = StudentSelectModule.studentArray;
		for(var i=0; i<list.length; i++) {
			if (list[i].studentId == studentId) {
				return list[i];
			}
		}
		return undefined;
	},
	addStudentUnit : function(data) {
		var index = StudentSelectModule.studentArray.length;
		//data.score = 0;
		StudentSelectModule.studentArray[index] = data;
		var html = "<input id='studentUnit"+index+"' type='button' style='height:30px; width:60px; margin-left:5px; margin-top:3px;' value='"+data.key+"' onclick='StudentSelectModule.selectUnit(\""+index+"\")'  />"
		$('#studentSelectArea').append(html);
	},
	selectUnit : function(index) {
		var cell = StudentSelectModule.studentArray[index];
		$('#studentUnit'+StudentSelectModule.currentIndex).removeClass('studentUnit-selected');
		$('#studentUnit'+index).addClass('studentUnit-selected');
		//StudentSelectModule.currentIndex = index;
		$('#studentName').text(cell.studentName);
		$('#studentScore').text(cell.score);
		// 加载指定学生的做题情况
		StudentSelectModule.loadStudentPaperData(index);
		StudentSelectModule.currentStudentQuestionData = cell.data;
		StudentSelectModule.refreshStudentStatus();
		
	},
	loadStudentPaperData : function(studentIndex) {
		
		// 更新当前选中的学生的相关数据
		
		var studentPaperData = StudentSelectModule.studentArray[studentIndex];
		StudentSelectModule.currentIndex = studentIndex;
		StudentSelectModule.currentStudentId = studentPaperData.studentId;
		var result = PaperResult.getPaperResultByStudentId(StudentSelectModule.currentStudentId);
		// 对学生的答题数据进行初步打分
		PaperResult.loadCurrentStudentPaperData();
		// 对题目按钮状态进行初始化
		var list = PaperDataModule.paperData;
		for(var i=0; i<list.length; i++) {
			$('#questionUnit'+list[i].questionId).removeClass('questionStatus-right');
			$('#questionUnit'+list[i].questionId).removeClass('questionStatus-wrong');
			$('#questionUnit'+list[i].questionId).removeClass('questionStatus-unknow');
			$('#questionUnit'+list[i].questionId).removeClass('questionStatus-know');
			
		}
		// 加载当前学生的作答结果
		list = PaperResult.getPaperResultByStudentId(StudentSelectModule.currentStudentId);
		for(var i=0; i<list.length; i++) {
			var questionId = list[i].questionId;
			var questionInfo = PaperDataModule.getQuestionById(questionId);
			// $('#questionUnit'+questionId).removeClass('questionStatus-unknow');
			if (list[i].score == undefined) {
				$('#questionUnit'+questionId).addClass('questionStatus-unknow');
			} else if (list[i].score <=0 ) {
				$('#questionUnit'+questionId).addClass('questionStatus-wrong');
			} else if (list[i].score <= questionInfo.questionScore) {
				$('#questionUnit'+questionId).addClass('questionStatus-know');
			} else {
				$('#questionUnit'+questionId).addClass('questionStatus-right');
			}
		}
		// 答题情况统计
		var temp = PaperDataModule.paperData.length - studentPaperData.data.length;
		$('#noAnswerQuestionNumber').text(temp);
		$('#studentScore').text(PaperResult.getStudentCurrentScore(StudentSelectModule.currentStudentId));
		temp = PaperDataModule.paperData.length - PaperResult.getPaperResultByStudentId(StudentSelectModule.currentStudentId).length;
		$('#noScoreQuestionNumber').text(temp);
		// 默认加载第一题
		$('#questionUnit'+PaperDataModule.paperData[0].questionId).trigger("click");
		
	},
	getQuestionAnswerByQuestionId : function(questionId) {
		// ------------------------------------------------------------------
		var data = StudentSelectModule.getStudentInfoById(StudentSelectModule.currentStudentId);
		if (undefined == data) {
			return "";
		}
		var list = data.data;
		for(var i=0; i<list.length; i++) {
			if (list[i].id == questionId) {
				return list[i].answer;
			}
		}
		return "";
	},
	refreshStudentStatus : function() {
		var list = StudentSelectModule.studentArray;
		var i, j;
		for( i=0; i<list.length; i++) {
			var result = PaperResult.getPaperResultByStudentId(list[i].studentId);
			for( j=0; j<result.length; j++) {
				if (result[j].score == undefined) {
					break;
				}
			}
			if (j < result.length) {
				$('#studentUnit'+i).removeClass('studentUnit-hasScore');
			} else {
				$('#studentUnit'+i).addClass('studentUnit-hasScore');
			}
		}
	}
}



/**
 * 试题选择模块
 */
var QuestionSelectModule = { 
	questionArray : [],
	currentIndex : undefined,
	currentQuestionId : undefined,
	setQuestionData : function(questionData) {
		QuestionSelectModule.questionArray = questionData;
	},
	getQuestionById : function(questionId) {
		var list = QuestionSelectModule.questionArray;
		var cell;
		for(var i=0; i<list.length; i++) {
			cell = list[i];
			if (cell.questionId == questionId) {
				return cell;
			}
		}
		return undefined;
	},
	loadQuestionById : function(questionId) {
		if (undefined != QuestionSelectModule.currentQuestionId) {
			$('#questionUnit' + QuestionSelectModule.currentQuestionId).removeClass('questionUnit-selected');
		}
		$('#questionUnit' + questionId).addClass('questionUnit-selected');
		// 清空上一次编辑的分数
		var questionScore = PaperResult.getStudentQuestionScore(StudentSelectModule.currentStudentId, questionId);
		if (questionScore == undefined) {
			questionScore = '';
		}
		$('#scoreEditArea').val(questionScore);
		// 更新当前当前所选题目的存储变量的值
		QuestionSelectModule.currentIndex = questionId;
		QuestionSelectModule.currentQuestionId = questionId;
		// 获取对应题号的题目信息
		var question = PaperDataModule.getQuestionById(questionId);
		if (undefined == question) {
			return ;
		}
		var questionInfo = question.questionTitle + "\n";
		if (question.answerType == 'select') {
			var itemList = question.questionItems.split(";");
			var selectList=["A","B","C","D","E","F"];
			var temp="";
			for(var i=0; i<itemList.length; i++) {
				temp += selectList[i] + "." + itemList[i] + "\n";
			}
			questionInfo += temp;
		}
		$('#questionNumberArea').text(questionId);
		$('#questionScoreArea').text('( '+question.questionScore+' )');
		$('#questionInfoArea').val(questionId+"."+questionInfo);
		// 获取对应题号的学生做答情况
		var studentAnswer = StudentSelectModule.getQuestionAnswerByQuestionId(questionId);
		$('#studentAnswerArea').val(studentAnswer);
		//
		var questionAnswer = PaperAnswerModule.getAnswerById(questionId);
		$('#questionAnswerArea').val(questionAnswer);
		$('#scoreEditArea').focus();
	},
	setQuestionResult : function() {
		if (undefined == StudentSelectModule.currentStudentId) {
			$('#scoreEditArea').val('');
			return;
		}
		var score = $('#scoreEditArea').val();
		if (score.replace(/(^s*)|(s*$)/g, "").length == 0) {
			return;
		}
		if(!/^\d+$/.test(score))
 			alert("分数必须是整数");
		PaperResult.setStudentScoreWithQuestionId(StudentSelectModule.currentStudentId, QuestionSelectModule.currentQuestionId, score, '');
		$('#studentScore').text(PaperResult.getStudentCurrentScore(StudentSelectModule.currentStudentId));
		var temp = PaperDataModule.paperData.length - PaperResult.getPaperResultByStudentId(StudentSelectModule.currentStudentId).length;
		$('#noScoreQuestionNumber').text(temp);
		if (score > 0) {
			$('#questionUnit'+QuestionSelectModule.currentQuestionId).addClass('questionStatus-know');
		} else {
			$('#questionUnit'+QuestionSelectModule.currentQuestionId).addClass('questionStatus-wrong');
		}
		$('#studentScore').text(PaperResult.getStudentCurrentScore(StudentSelectModule.currentStudentId));
	},
	loadLastQuestion : function() {
		QuestionSelectModule.setQuestionResult();
		var lastCell = $('#questionUnit'+QuestionSelectModule.currentQuestionId).prev();
		if (undefined != lastCell) {
			lastCell.trigger("click");
		}
	}, 
	loadNextQuestion : function() {
		QuestionSelectModule.setQuestionResult();
		var lastCell = $('#questionUnit'+QuestionSelectModule.currentQuestionId).next();
		if (undefined != lastCell) {
			lastCell.trigger("click");
		}
	}

}


/*
 * 试题结果模块
 * [{studentId : 学生编号, result : [{questionId : 题目编号, score : 分数, comment : 评价}, ...]}, ...]
 * 
 */
var PaperResult = {
	paperResultScore : [],
	currentStudentId : undefined,
	getPaperResultByStudentId : function(studentId) {
		// 获取指定学生当前的评分结果，如果没有该学生的成绩，则创建一个新的
		var list = PaperResult.paperResultScore;
		for(var i=0; i<list.length; i++) {
			if (studentId == list[i].studentId) {
				return list[i].result;
			}
		}
		var newStudentResult = {
			'studentId' : studentId,
			'result' : []
		};
		list[list.length] = newStudentResult;
		
		return newStudentResult.result;
	},
	getStudentQuestionScore : function(studentId, questionId) {
		// 获取指定学生下指定题目的成绩
		var result = PaperResult.getPaperResultByStudentId(studentId);
		
		for(var i=0; i<result.length; i++) {
			if (result[i].questionId == questionId) {
				return result[i].score;
			}
		}
		return undefined;
	},
	setStudentScoreWithQuestionId : function(studentId, questionId, score, comment) {
		// 获取对应题号的题目信息
		var question = PaperDataModule.getQuestionById(questionId);
		if (score < 0) {
			alert("分数不能为负！");
			return;
		} 
		if (score > question.questionScore) {
			alert("分数不能超过 "+question.questionScore);
			return;
		}
		// 为当前选中的学生设置指定题目的分数和评论，如果当前没有该题目的作答评分，则新增一个
		var data = PaperResult.getPaperResultByStudentId(studentId);
		for(var i=0; i<data.length; i++) {
			if (data[i].questionId == questionId) {
				data[i].score = score;
				data[i].comment = comment;
				return ;
			}
		}
		var newQuestionResult = {
			'questionId' : questionId,
			'score' : score,
			'comment' : comment
		};
		data[data.length] = newQuestionResult;
	},
	getStudentCurrentScore : function(studentId) {
		var result = PaperResult.getPaperResultByStudentId(studentId);
		var allScore = 0;
		for(var i=0; i<result.length; i++) {
			if (undefined != result[i].score) {
				allScore += parseInt(result[i].score);
			}
		}
		return allScore;
	},
	loadCurrentStudentPaperData : function() {
		// 获取当前学生的题目作答情况
		var paperResult = PaperResult.getPaperResultByStudentId(StudentSelectModule.currentStudentId);
		if (paperResult.length != 0) {
			return ;
		}
		// 获取当前选中的学生的做题数据，并进行初步打分
		var data; // = StudentSelectModule.studentArray[StudentSelectModule.currentIndex];
		for(var i=0; i<StudentSelectModule.studentArray.length; i++) {
			if (StudentSelectModule.studentArray[i].studentId == StudentSelectModule.currentStudentId) {
				data = StudentSelectModule.studentArray[i];
				break;
			}
		}
		var list = data.data;
		for(var i=0; i<list.length; i++) {
			var questionId = list[i].id;
			var questionInfo = PaperDataModule.getQuestionById(questionId);
			if (questionInfo.answerType == 'select') {
				// 选择题判断
				var studentAnswer = StudentSelectModule.getQuestionAnswerByQuestionId(questionId);
				var questionAnswer = PaperAnswerModule.getAnswerById(questionId);
				if (studentAnswer == questionAnswer) {
					PaperResult.setStudentScoreWithQuestionId(StudentSelectModule.currentStudentId, questionId, questionInfo.questionScore, '');
				} else {
					PaperResult.setStudentScoreWithQuestionId(StudentSelectModule.currentStudentId, questionId, 0, '');
				}
			} else if (questionInfo.answerType == 'edit') {
				// 编辑题判断
				PaperResult.setStudentScoreWithQuestionId(StudentSelectModule.currentStudentId, questionId, undefined, '');
			}
		}
		// 获取当前学生已提交题目的作答结果
		var currentResult = PaperResult.getPaperResultByStudentId(StudentSelectModule.currentStudentId);
		var paperData = PaperDataModule.paperData;
		for(var i=0; i<paperData.length; i++) {
			var questionId = paperData[i].questionId;
			var j;
			for(j=0; j<currentResult.length; j++) {
				if (questionId == currentResult[j].questionId) {
					break;
				}
			}
			// 将未做的题目设置为0分
			if (j == currentResult.length) {
				PaperResult.setStudentScoreWithQuestionId(StudentSelectModule.currentStudentId, questionId, 0, '');
			}
		}
	},
	showFinalResult : function() {
		$('#paperOptionArea').hide();
		PaperResult.sortCurrentStudentScore();
		$('#paperResultOutputArea').show();
		var target = $('#studentScoreTable');
		target.html('<tr ><td >学生姓名</td><td >成绩</td></tr>');
		var list = PaperResult.paperResultScore;
		for(var i=0; i<list.length; i++) {
			var studentInfo = StudentSelectModule.getStudentInfoById(list[i].studentId);
			var score = PaperResult.getStudentCurrentScore(list[i].studentId);
			target.append('<tr ><td >'+studentInfo.key+'</td><td >'+score+'</td></tr>')
		}
		$('#finalResultScoreJsonArea').val(JSON.stringify(list));
	},
	cancelShowFinalResult : function() {
		$('#paperResultOutputArea').hide();
		$('#paperOptionArea').show();
	},
	sortCurrentStudentScore : function() {
		var list = PaperResult.paperResultScore;
		for(var i=0; i<list.length; i++) {
			list[i].score = scoreI;
			for (var j=i+1; j<list.length; j++) {
				var scoreJ = PaperResult.getStudentCurrentScore(list[j].studentId);
				var scoreI = PaperResult.getStudentCurrentScore(list[i].studentId);
				if (scoreI < scoreJ) {
					var temp = list[i];
					list[i] = list[j];
					list[j] = temp;
				}
			}
		}
	}
	
}
