const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_INITIAL_GUI=100;const UI_TITEL=0;const UI_LABEL=1;const UPDATE_LABEL=6;const UI_BUTTON=2;const UPDATE_BUTTON=17;const UI_SWITCHER=3;const UPDATE_SWITCHER=7;const UI_PAD=4;const UI_CPAD=5;const UI_SLIDER=8;const UPDATE_SLIDER=9;const UI_NUMBER=10;const UPDATE_NUMBER=11;const UI_TEXT_INPUT=12;const UPDATE_TEXT_INPUT=13;const UI_GRAPH=14;const CLEAR_GRAPH=15;const ADD_GRAPH_POINT=16;const FOR=0;const BACK=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_NONE=7;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";break;case C_EMERALD:return"emerald";break;case C_PETERRIVER:return"peterriver";break;case C_WETASPHALT:return"wetasphalt";break;case C_SUNFLOWER:return"sunflower";break;case C_CARROT:return"carrot";break;case C_ALIZARIN:return"alizarin";break;case C_NONE:return"";break;default:return"";}}
var websock;var websockConnected=false;function restart(){$(document).add("*").off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({click:restart});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);websock=new WebSocket("ws://"+window.location.hostname+"/ws");websock.onopen=function(evt){console.log("websock open");$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log("websock close");conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};var handleEvent=function(evt){var data=JSON.parse(evt.data);var e=document.body;var center="";switch(data.type){case UI_INITIAL_GUI:data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element)};handleEvent(fauxEvent);});break;case UI_TITEL:document.title=data.label;$("#mainHeader").html(data.label);break;case UI_LABEL:$("#row").append("<div class='two columns card tcenter "+
colorClass(data.color)+
"' style='"+
data.css+
"'><h5 id='"+
data.id+
"'>"+
data.label+
"</h5><hr /><span id='l"+
data.id+
"' class='label label-wrap'>"+
data.value+
"</span></div>");break;case UI_BUTTON:$("#row").append("<div class='one columns card tcenter "+
colorClass(data.color)+
"' style='"+
data.css+
"'><h5 id='bl"+
data.id+
"'>"+
data.label+
"</h5><hr/><button onmousedown='buttonclick("+
data.id+
", true)' onmouseup='buttonclick("+
data.id+
", false)' id='b"+
data.id+
"'>"+
data.value+
"</button></div>");$("#"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);}});$("#"+data.id).on({touchend:function(e){e.preventDefault();buttonclick(data.id,false);}});break;case UI_SWITCHER:var label="<label id='sl"+data.id+"' class='switch checked'>";var input="<div class='in'><input type='checkbox' id='s"+
data.id+
"' onClick='switcher("+
data.id+
",null)' checked></div>";if(data.value=="0"){label="<label id='sl"+data.id+"' class='switch'>";input="<div class='in'><input type='checkbox' id='s"+
data.id+
"' onClick='switcher("+
data.id+
",null)' ></div>";}
$("#row").append("<div id='"+
data.id+
"' class='one columns card tcenter "+
colorClass(data.color)+
"'><h5>"+
data.label+
"</h5><hr/>"+
label+
input+
"</label>"+
"</div>");break;case UI_CPAD:center="<a class='confirm' onmousedown='padclick(CENTER, "+
data.id+
", true)' onmouseup='padclick(CENTER, "+
data.id+
", false)' href='#' id='pc"+
data.id+
"'>OK</a>";case UI_PAD:$("#row").append("<div class='two columns card tcenter "+
colorClass(data.color)+
"'><h5>"+
data.label+
"</h5><hr/>"+
"<nav class='control'>"+
"<ul>"+
"<li><a onmousedown='padclick(FOR, "+
data.id+
", true)' onmouseup='padclick(FOR, "+
data.id+
", false)' href='#' id='pf"+
data.id+
"'>▲</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+
data.id+
", true)' onmouseup='padclick(RIGHT, "+
data.id+
", false)' href='#' id='pr"+
data.id+
"'>▲</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+
data.id+
", true)' onmouseup='padclick(LEFT, "+
data.id+
", false)' href='#' id='pl"+
data.id+
"'>▲</a></li>"+
"<li><a onmousedown='padclick(BACK, "+
data.id+
", true)' onmouseup='padclick(BACK, "+
data.id+
", false)' href='#' id='pb"+
data.id+
"'>▲</a></li>"+
"</ul>"+
center+
"</nav>"+
"</div>");$("#pf"+data.id).on({touchstart:function(e){e.preventDefault();padclick(FOR,data.id,true);}});$("#pf"+data.id).on({touchend:function(e){e.preventDefault();padclick(FOR,data.id,false);}});$("#pl"+data.id).on({touchstart:function(e){e.preventDefault();padclick(LEFT,data.id,true);}});$("#pl"+data.id).on({touchend:function(e){e.preventDefault();padclick(LEFT,data.id,false);}});$("#pr"+data.id).on({touchstart:function(e){e.preventDefault();padclick(RIGHT,data.id,true);}});$("#pr"+data.id).on({touchend:function(e){e.preventDefault();padclick(RIGHT,data.id,false);}});$("#pb"+data.id).on({touchstart:function(e){e.preventDefault();padclick(BACK,data.id,true);}});$("#pb"+data.id).on({touchend:function(e){e.preventDefault();padclick(BACK,data.id,false);}});$("#pc"+data.id).on({touchstart:function(e){e.preventDefault();padclick(CENTER,data.id,true);}});$("#pc"+data.id).on({touchend:function(e){e.preventDefault();padclick(CENTER,data.id,false);}});break;case UPDATE_LABEL:$("#l"+data.id).html(data.value);break;case UPDATE_BUTTON:$("#bl"+data.id).html(data.value);$("#b"+data.id).html(data.btnText);break;case UPDATE_SWITCHER:if(data.value=="0")switcher(data.id,0);else switcher(data.id,1);break;case UI_SLIDER:$("#row").append("<div class='two columns card tcenter card-slider "+
colorClass(data.color)+
"'>"+
"<h5 id='"+
data.id+
"'>"+
data.label+
"</h5><hr />"+
"<div id='sl"+
data.id+
"' class='rkmd-slider slider-discrete slider-"+
colorClass(data.color)+
"'>"+
"<input type='range' min='0' max='100' value='"+
data.value+
"'>"+
"</div>"+
"</div>");$("#row").append("<script>"+"rkmd_rangeSlider('#sl"+data.id+"');"+"</script>");break;case UPDATE_SLIDER:slider_move($("#sl"+data.id),data.value,"100",false);break;case UI_NUMBER:$("#row").append("<div class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5 id='"+
data.id+
"'>"+
data.label+
"</h5><hr />"+
"<input style='color:black;' id='num"+
data.id+
"' type='number' value='"+
data.value+
"' onchange='numberchange("+
data.id+
")' />"+
"</div>");break;case UPDATE_NUMBER:$("#num"+data.id).val(data.value);break;case UI_TEXT_INPUT:$("#row").append("<div class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5 id='"+
data.id+
"'>"+
data.label+
"</h5><hr />"+
"<input style='color:black;' id='text"+
data.id+
"' value='"+
data.value+
"' onchange='textchange("+
data.id+
")' />"+
"</div>");break;case UPDATE_TEXT_INPUT:$("#text"+data.id).val(data.value);break;default:console.error("Unknown type or event");break;}};websock.onmessage=handleEvent;}
function numberchange(number){var val=$("#num"+number).val();websock.send("nvalue:"+val+":"+number);console.log(val);}
function textchange(number){var val=$("#text"+number).val();websock.send("tvalue:"+val+":"+number);console.log(val);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case FOR:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case BACK:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if($("#s"+number).is(":checked")){websock.send("sactive:"+number);$("#sl"+number).addClass("checked");}else{websock.send("sinactive:"+number);$("#sl"+number).removeClass("checked");}}else if(state==1){$("#sl"+number).addClass("checked");$("#sl"+number).prop("checked",true);}else if(state==0){$("#sl"+number).removeClass("checked");$("#sl"+number).prop("checked",false);}}
)=====";

const uint8_t JS_CONTROLS_GZIP[2155] PROGMEM = { 31,139,8,0,221,153,118,92,2,255,213,89,225,114,219,184,17,254,159,167,224,49,55,145,88,59,178,117,105,174,87,201,244,140,34,43,177,122,58,217,149,229,75,167,127,52,16,9,69,28,83,32,11,128,82,92,143,102,250,14,125,131,62,66,31,161,125,147,62,73,23,0,65,130,52,105,201,214,164,51,253,35,145,139,197,135,15,187,11,236,2,244,34,194,184,117,59,156,13,199,195,233,176,55,154,125,186,29,186,237,211,211,174,167,27,166,195,233,96,228,26,130,81,239,3,8,218,90,112,125,209,155,14,82,225,143,185,214,135,219,233,244,106,236,254,80,84,75,165,237,223,229,138,55,159,135,211,254,229,96,226,190,43,170,102,114,67,247,186,119,225,254,54,127,237,139,247,247,6,212,104,120,1,29,126,42,1,41,233,239,115,189,241,237,47,31,64,210,62,45,42,106,113,219,152,252,224,79,83,48,205,245,237,212,109,151,166,98,54,189,203,123,124,154,244,174,47,221,182,102,217,31,13,122,19,45,212,84,123,23,23,74,52,187,190,26,142,161,191,182,219,199,171,73,102,233,15,189,254,207,153,149,71,131,143,211,204,150,147,225,167,203,105,102,174,254,96,60,5,214,217,128,179,233,237,228,143,183,87,195,155,65,6,213,159,13,126,25,76,122,163,139,12,175,63,187,30,64,175,201,240,87,232,250,67,38,252,60,152,246,110,174,47,123,35,3,126,118,115,59,254,56,186,250,92,24,163,223,155,76,174,166,153,237,251,179,222,104,248,231,222,100,56,206,66,160,63,27,95,141,7,224,188,69,66,60,30,68,196,242,162,48,162,253,16,49,214,148,143,67,223,121,72,31,220,113,178,154,99,154,201,187,108,19,112,111,105,232,33,134,205,169,117,40,230,9,37,54,252,252,37,137,2,134,237,238,156,98,116,215,77,21,211,249,106,53,188,194,20,133,126,73,41,55,129,214,139,49,199,148,6,107,76,75,170,185,97,180,234,6,115,196,226,37,10,121,73,53,51,151,214,100,9,89,132,209,230,17,166,178,161,214,242,16,165,81,25,75,91,85,43,161,48,248,43,162,1,41,169,9,75,107,21,221,228,227,5,74,66,158,139,183,219,87,107,68,173,13,158,179,200,187,235,26,207,253,136,16,236,113,236,187,11,20,50,156,123,140,98,198,17,229,77,231,225,251,166,31,121,201,10,19,238,180,144,239,55,237,223,216,78,43,90,44,154,78,247,251,166,253,154,70,27,120,95,242,85,216,180,109,167,155,226,182,188,48,98,24,84,82,148,238,246,149,17,12,228,134,35,158,176,1,76,155,194,8,53,92,4,122,166,11,99,80,188,138,214,88,69,145,45,195,227,237,23,138,49,177,157,71,170,192,179,160,71,177,95,161,165,72,75,22,214,137,53,142,172,148,129,32,249,230,245,79,63,190,123,223,173,232,149,79,189,32,37,205,7,47,12,188,187,78,106,185,109,97,206,75,68,252,16,255,26,176,96,30,132,1,191,239,131,224,11,216,231,33,88,52,191,43,207,255,205,155,239,180,201,91,203,192,247,49,113,30,50,127,8,103,102,176,218,71,153,58,76,124,176,134,135,81,192,56,38,176,172,236,117,54,166,39,199,180,143,171,185,28,75,163,103,14,116,9,222,88,159,241,252,6,158,49,111,218,27,214,57,57,177,143,54,1,241,163,77,43,140,60,36,8,180,150,17,227,4,173,240,145,125,178,97,134,251,35,18,197,152,184,154,104,19,175,185,88,241,132,69,33,134,222,95,0,80,105,90,66,111,15,15,214,121,154,227,175,192,46,51,93,78,33,143,38,78,19,220,221,26,212,100,108,238,195,77,42,2,100,57,98,11,104,88,200,158,64,19,130,42,4,177,10,149,43,164,199,74,8,162,213,71,28,185,127,184,185,26,183,98,68,97,53,65,67,75,200,28,217,23,187,153,215,231,145,127,47,101,30,188,97,234,194,146,79,119,81,161,222,226,247,49,78,247,209,98,182,239,200,102,224,198,105,20,178,214,34,162,3,4,157,112,136,5,172,123,46,89,192,94,242,85,49,124,16,234,29,73,136,113,216,138,190,4,139,123,173,236,108,187,198,100,154,89,39,152,169,99,238,88,186,170,232,100,228,121,192,67,152,139,96,18,162,57,14,165,139,87,40,32,151,24,249,176,115,166,235,52,87,40,227,201,250,163,147,239,69,40,134,144,130,125,234,204,15,214,224,66,8,34,183,193,55,145,72,66,201,138,48,11,182,91,223,226,202,84,150,125,244,202,72,78,169,61,224,221,57,122,101,55,96,125,221,3,183,6,40,169,22,198,132,248,252,108,249,222,10,252,92,30,248,82,172,95,37,75,144,156,157,44,223,131,46,108,46,231,103,44,70,68,246,9,139,157,52,65,217,199,146,191,111,55,20,197,57,218,26,133,9,150,104,2,227,252,236,4,166,117,110,151,141,160,170,171,29,86,128,96,253,6,86,152,135,123,218,1,204,48,79,56,135,125,43,34,171,40,97,24,182,18,2,253,165,76,110,158,205,2,210,177,37,150,174,211,208,234,73,252,164,178,218,192,26,138,83,13,165,220,152,10,40,55,167,176,156,125,148,246,81,251,57,143,18,111,41,183,216,78,190,56,157,7,220,138,41,22,177,125,161,242,44,172,102,147,85,10,113,44,185,195,110,93,15,13,254,121,9,112,186,81,111,31,45,44,93,54,119,196,178,149,198,119,237,51,21,88,194,38,44,204,72,28,229,129,167,54,10,11,216,192,70,239,131,165,228,70,18,144,56,225,110,33,120,2,2,46,151,114,75,108,40,110,67,118,153,71,95,149,197,89,41,174,35,210,23,172,245,0,34,21,21,220,69,146,48,4,103,165,227,106,63,116,33,31,230,142,114,93,251,212,118,30,158,55,21,49,133,255,25,253,140,247,246,85,205,210,123,188,79,28,182,26,197,178,123,98,133,65,75,42,148,115,149,109,82,32,90,236,154,205,67,28,166,58,58,119,156,33,77,16,18,195,34,160,171,70,113,185,198,200,87,241,168,78,31,199,214,206,53,187,171,135,94,184,75,138,23,110,227,181,114,72,236,149,150,240,213,207,103,39,8,44,173,73,11,206,223,98,211,223,109,96,251,140,160,181,97,36,145,61,27,170,33,73,237,28,6,231,96,199,106,187,193,73,239,57,70,171,82,175,182,216,162,100,177,127,255,227,63,127,251,251,191,254,41,204,6,65,16,236,102,38,79,151,207,225,86,221,161,154,29,61,148,157,56,8,63,135,92,165,126,53,183,240,80,110,226,196,254,28,110,149,250,213,220,230,251,112,59,81,129,167,226,91,10,32,68,139,75,94,172,21,17,34,47,76,113,133,120,172,206,113,213,232,123,100,185,74,108,35,205,73,240,240,112,234,50,34,106,184,135,135,114,47,128,151,201,211,195,201,171,181,86,195,158,30,202,190,136,94,166,63,63,156,190,140,248,26,246,243,67,217,23,192,203,228,189,195,201,167,137,171,134,190,119,40,253,18,124,77,129,103,220,182,202,196,103,70,108,126,68,146,133,83,85,71,227,132,48,127,178,171,212,168,84,152,115,50,133,243,118,21,122,86,123,86,20,112,89,9,165,39,120,234,116,49,76,209,122,212,208,126,84,210,202,11,220,151,230,121,241,242,150,133,129,191,51,231,203,157,242,217,167,58,217,75,23,121,172,230,100,71,239,86,25,9,245,247,214,15,152,71,49,199,250,125,15,110,102,229,74,197,125,77,195,90,5,144,129,78,225,31,125,117,27,237,83,120,82,54,111,148,15,59,13,51,17,148,83,66,201,172,64,44,136,57,168,217,130,247,76,14,117,35,89,54,27,175,139,101,183,211,5,45,56,149,166,61,42,163,66,185,79,77,115,38,174,239,154,98,76,3,199,57,206,169,30,219,48,11,91,135,127,49,16,212,5,253,183,41,248,14,112,190,114,75,122,64,150,144,157,121,136,188,187,174,74,222,36,89,149,130,66,121,144,200,59,239,122,135,65,205,160,110,235,180,170,122,43,158,65,160,82,56,169,175,234,205,239,26,210,108,146,75,182,168,97,168,218,253,194,252,246,241,255,102,113,113,31,88,50,249,30,70,22,189,94,106,226,146,173,20,129,29,118,214,55,244,250,158,80,222,33,54,237,91,114,71,160,174,148,65,98,69,212,146,249,34,27,116,107,222,58,174,48,99,8,168,27,151,110,230,125,115,33,106,212,139,186,83,4,26,110,22,13,105,131,36,153,223,221,50,233,101,34,9,119,236,35,248,63,178,59,153,114,215,188,219,132,182,194,53,183,97,199,170,65,149,109,158,26,149,191,100,84,243,146,68,233,31,7,76,20,232,242,122,61,125,44,142,51,23,50,3,94,166,163,146,74,18,27,10,198,112,89,218,22,110,58,46,13,152,222,187,26,87,174,42,185,119,234,152,196,222,110,42,177,87,224,98,196,32,20,204,245,200,139,61,144,23,117,200,162,164,170,135,222,195,126,241,188,14,90,84,202,245,208,225,30,208,97,29,180,44,99,235,177,233,30,216,180,2,187,240,205,69,23,45,169,231,161,146,228,88,70,154,124,114,93,121,53,36,222,101,170,203,227,61,96,77,187,147,222,119,217,78,246,217,43,29,151,33,128,95,99,99,104,157,41,117,127,227,147,136,6,233,110,197,12,202,72,1,217,137,85,252,150,150,195,73,60,43,159,75,91,124,255,219,77,163,172,19,211,40,206,219,117,189,92,194,62,125,140,93,67,107,7,124,86,47,255,23,218,230,147,226,210,32,0,0 };
