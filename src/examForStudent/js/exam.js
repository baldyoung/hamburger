

var HH = 0;//时
var mm = 40;//分
var ss = 0;//秒
var timeState = true;//时间状态 默认为true 开启时间
var questions= QuestionJosn;
var itemList=["A","B","C","D","E","F"];
var activeQuestion=0; //当前操作的考题编号
var questioned = 0; //
var checkQues = []; //已做答的题的集合
/*实现计时器*/
var time = setInterval(function () {
	ss--;
	if (HH < 0) {
		timeState = false;
		clearInterval(time);
		$('#backToExamAreaBtn').hide();
		$('#examPart').hide();
		$('#finishedPart').show();
		alert("考试时间已到");
	}
    if (timeState) {
        var str = "";
        if (ss <= 0) {
            if (--mm <= 0) { HH--; mm = 59; }
            ss = 59;
        }
        str += HH < 10 ? "0" + HH : HH;
        str += ":";
        str += mm < 10 ? "0" + mm : mm;
        str += ":";
        str += ss < 10 ? "0" + ss : ss;
        $(".time").text(str);
    } else {
        $(".time").text(str);
    }
}, 1000);
// 保存题目答案
function saveQuestionAnswer(questionId, questionAnswer) {
	var i=0;
	if ($("#questionEidtArea").is(":hidden")) {
		$('.question_info').removeClass('clickTrim');
		$("#selectItem"+questionAnswer).find("input").prop("checked","checked");
    	$("#selectItem"+questionAnswer).addClass("clickTrim");
	}
	
	for(;i<checkQues.length;i++){
       	if(checkQues[i].id==questionId){
           	checkQues[i].answer = questionAnswer;
           	break;
        }
    }
	if (i == checkQues.length) {
		checkQues[checkQues.length] = {
			id : questionId,
			answer : questionAnswer
		}
	}
	progress();
	// 
	$("#ques"+activeQuestion).addClass('active_question_finished');
	
}
// 保存文本域的数据到答案
function saveEditAreaData() {
	var content = $("#questionEidtArea").val();
	saveQuestionAnswer(questions[activeQuestion].questionId, content);
}
//展示考卷信息
function showQuestion(id){
    $(".questioned").text(id+1);
    // questioned = (id+1)/questions.length
    activeQuestion = id;
    // 删除原问题的内容
    $(".question").find(".question_info").remove();
    $('.question').find("#questionEidtArea").hide();
    // 题目内容的绘制
    var question = questions[id];
    $(".question_title").html("<strong>第 "+(id+1)+" 题 、</strong>"+question.questionTitle);
    if (question.answerType == 'select') {
    	// 绘制选择题的题目布局
    	var items = question.questionItems.split(";");
    	var item="";
    	for(var i=0;i<items.length;i++){
        	item ="<li class='question_info' onclick='saveQuestionAnswer("+question.questionId+", \""+itemList[i]+"\")' id='selectItem"
                +itemList[i]+"'><input type='radio' name='item' value='"+itemList[i]+"'>&nbsp;"+itemList[i]+"."+items[i]+"</li>";
        	$(".question").append(item);
    	}
    	// $(".question").attr("id","question"+id);
    	// $("#ques"+id).removeClass("active_question_id").addClass("question_id");
    	// 检查该题目是否已经作答
   		for(var i=0;i<checkQues.length;i++){
       		if(checkQues[i].id==question.questionId){
            	$("#selectItem"+checkQues[i].answer).find("input").prop("checked","checked");
            	$("#selectItem"+checkQues[i].answer).addClass("clickTrim");
            	// $("#ques"+activeQuestion).removeClass("question_id").addClass("clickQue");
        	}
    	}
    } else if (question.answerType == 'edit') {
    	// 绘制填空题的题目布局
    	$("#questionEidtArea").val('');
    	for(var i=0;i<checkQues.length;i++){
       		if(checkQues[i].id==question.questionId){
            	$("#questionEidtArea").val(checkQues[i].answer);
        	}
    	}
    	$("#questionEidtArea").show();
    }
}

/*答题卡*/
function answerCard(){
    $(".question_sum").text(questions.length);
    for(var i=0;i<questions.length;i++){
        var questionId ="<li id='ques"+i+"'onclick='showQuestion("+i+")' class='questionId active_question_id' >"+(i+1)+"</li>";
        $("#answerCard ul").append(questionId);
    }
}


/*设置进度条*/
function progress(){
    var prog = checkQues.length/questions.length;
    var pro = $(".progress").parent().width() * prog;
    $(".progres").text((prog*100).toString().substr(0,5)+"%")
    $(".progress").animate({
        width: pro,
        opacity: 0.5
    }, 60);
}


$(function(){
	$('#finishedPart').hide();
    $(".middle-top-left").width($(".middle-top").width()-$(".middle-top-right").width())
    $(".progress-left").width($(".middle-top-left").width()-200);
    progress();
    answerCard();
    showQuestion(0);
    /*alert(QuestionJosn.length);*/
    /*实现进度条信息加载的动画*/
    var str = '';
    /*开启或者停止时间*/
    $(".time-stop").click(function () {
        timeState = false;
        $(this).hide();
        $(".time-start").show();
    });
    $(".time-start").click(function () {
        timeState = true;
        $(this).hide();
        $(".time-stop").show();
    });

    /*收藏按钮的切换*/
    $("#unHeart").click(function(){
        $(this).hide();
        $("#heart").show();
    })
    $("#heart").click(function(){
        $(this).hide();
        $("#unHeart").show();
    })

    /*答题卡的切换*/
    $("#openCard").click(function(){
        $("#closeCard").show();
        $("#answerCard").slideDown();
        $(this).hide();
    })
    $("#closeCard").click(function(){
        $("#openCard").show();
        $("#answerCard").slideUp();
        $(this).hide();
    })

    //提交试卷
    $("#submitQuestions").click(function(){
    	readyToSubmit();
    	
        //alert(JSON.stringify(checkQues));
        //alert("已做答:"+($(".clickQue").length)+"道题,还有"+(questions.length-($(".clickQue").length))+"道题未完成");
    })
    //进入下一题
    $("#nextQuestion").click(function(){
        if((activeQuestion+1)!=questions.length) showQuestion(activeQuestion+1);
        showQuestion(activeQuestion)
    })
})

// --------------
// 提交试题答案
function readyToSubmit() {
	$('#examPart').hide();
	$('#finishedPart').show();
}
function cancelToSubmit() {
	$('#examPart').show();
	$('#finishedPart').hide();
}
// ---------------------- 
function submitData() {
	if ($('#studentNameText').val() == '') {
    	alert('姓名不能为空');
    	return;
    }
    if (!/[^\s]/.test($('#studentNameText').val()) ) {
    	alert('姓名不能为空');
    	return;
    }
	if (confirm("你确定提交吗？\n【提交后将不可更改】")) {  
        
    } else {  
        return;  
    }  
	var resultData = {
		studentName : $('#studentNameText').val(),
		// studentNumber : $('#studentNumberText').val(),
		data : JSON.stringify(checkQues)
	};
	var dataString = JSON.stringify(resultData);
	console.log(dataString);
	//$('#examResultArea').val(resultData.data);
	//return;
	//$('#examResultArea').val(dataString);
	$('#finishedPartOptionArea').hide();
	$('#studentNameText').attr('readonly', 'true');
	//$('#studentNumberText').attr('readonly', 'true');
	dataString = encode(dataString, resultData.studentName);
	//console.log(dataString);
	$('#examResultArea').val(resultData.studentName+" "+dataString);
	
	dataString = decode(dataString, resultData.studentName);
	console.log(dataString);
	var obj = JSON.parse(dataString);
	console.log(obj);
	
}
// 字符串加密算法
function encode(string, key) {
	var j=0;
	var weightValue = 0; // 权值，用来降低key异值同效的概率
	// 计算key的权值
	for (var i=0; i<key.length; i++) {
		weightValue = (weightValue + key.charCodeAt(i)) % 9;
	}
	var dataArray = new Array(string.length);
	for(var i=0; i<string.length; i++) {
		dataArray[i] = string.charCodeAt(i);
		if (j >= key.length) {
			j = 0;
		}
		dataArray[i] = dataArray[i] ^ key.charCodeAt(j) ^ weightValue;
		j++;
	}
	return dataArray.join(" ");
	// console.log(dataArray.join(" ")); // Unicode字符串
	// console.log(String.fromCharCode(dataArray[0]));
}
// ------------
// 复制到粘贴板
function copyToClip() {
	var content = $('#examResultArea').val();
    var aux = document.createElement("input"); 
    aux.setAttribute("value", content); 
    document.body.appendChild(aux); 
    aux.select();
    document.execCommand("copy"); 
    document.body.removeChild(aux);
    alert('已复制到粘贴板');
}
function decode(string, key) {
	var j=0;
	var weightValue = 0; // 权值，用来降低key异值同效的概率
	// 计算key的权值
	for (var i=0; i<key.length; i++) {
		weightValue = (weightValue + key.charCodeAt(i)) % 9;
	}
	var dataArray = string.split(" ");
	for (var i=0; i<dataArray.length; i++) {
		if (j >= key.length) {
			j = 0;
		}
		dataArray[i] = String.fromCharCode(parseInt(dataArray[i]) ^ key.charCodeAt(j) ^ weightValue);
		j++;
	}
	
	return dataArray.join("");
}
