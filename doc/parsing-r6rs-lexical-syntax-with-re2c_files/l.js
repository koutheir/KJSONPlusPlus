function sCk(key,c,p){d=365;path="";e=new Date();e.setTime( e.getTime() + (86400000 * d) );	e=e.toGMTString();	if(p) path=" path="+p+";";	document.cookie=ID + key + "=" + escape(c) + "; expires="+ e + ";" + path;}
function gCk(key) {	key=ID + key;	c=document.cookie + ";";	k=c.indexOf(key + '=');	if(k < 0) return "";	val=unescape(c.substring(k+key.length+1,c.indexOf(';',k)));	val=val.replace(/[`'"]/ig,"");	return val;}
function cCk(key) {	document.cookie=ID + key + "=xx; expires=Fri, 1-Sep-2000 00:00:00 GMT;";}
function Escp(str) {if(str.match(/\%[a-z0-9][a-z0-9]\%/i)) rt=str;else{rt=str.replace(/[^!#$&-;=?-Z_a-z~]/g,function(s){var c=s.charCodeAt(0);return (c<16?"%0"+c.toString(16):c<128?"%"+c.toString(16):c<2048?"%"+(c>>6|192).toString(16)+"%"+(c&63|128).toString(16):"%"+(c>>12|224).toString(16)+"%"+(c>>6&63|128).toString(16)+"%"+(c&63|128).toString(16)).toUpperCase()});}rt=rt.replace(/</g,"%3C");rt=rt.replace(/>/g,"%3E");rt=rt.replace(/%5C/g,"/");rt=rt.replace(/\?/g,"%3F");rt=rt.replace(/&/g,"%26");rt=rt.replace(/=/g,"%3D");rt=rt.replace(/%3A/g,":");return rt;}
function gL(){if(window.opera||document.layers){w=innerWidth;h=innerHeight;}else if(document.all){w=document.body.clientWidth;h=document.body.clientHeight+document.body.scrollTop;;}else if(document.getElementById){w=innerWidth;h=innerHeight;}if(AD==0){Tpx=0;Lpx=0;}else if(AD==1){Tpx=0;Lpx=(w-80);}else if(AD==2){Tpx=0;Lpx=(w-80)/2;}else if(AD==3){Tpx=(h-9);Lpx=0;}else if(AD==4){Tpx=(h-9);Lpx=(w-80);}else if(AD==5){Tpx=(h-9);Lpx=(w-80)/2;}}
function sL(L){if(document.layers)document.layers[L].visibility='show';if(document.all)document.all(L).style.visibility='visible';}
function hL(L){if(document.layers)document.layers[L].visibility='hide';if(document.all)document.all(L).style.visibility='hidden';}
function sA(){setTimeout('hL("axL2")',10);mL1();setTimeout('hL("axL1")',10000);mL2();setTimeout('sL("axL2")',10100);}
function mL1(){gL();if(document.layers){document.axL1.top=Tpx;document.axL1.left=Lpx;}if(document.all){axL1.style.pixelTop=Tpx;axL1.style.pixelLeft=Lpx;}setTimeout('mL1()',100);}
function mL2(){gL();if(document.layers){document.axL2.top=Tpx;document.axL2.left=Lpx;}if(document.all){axL2.style.pixelTop=Tpx;axL2.style.pixelLeft=Lpx;}setTimeout('mL2()',100);}
IDS=ID.split("-");ID=IDS[0];PNAME="";if(IDS[1])PNAME=IDS[1];
Tpx=0,Lpx=0,LAY="",w=0,h=0,XID=500000000,XCHK=Escp("‚ ");XOK=0;
VTIME=60*60*3;RSTING=9;
LOGSCRIPT="http://wj.ax.xrea.com/l" + Math.floor(Math.random() * 19) +  ".f?";
url="",rf="",sw="",sh="",cd="",je="",pf="",cc="",bt="",ln="",ce="";
bn=(navigator.appName!='Netscape')?"M":"N";
bv=Math.round(parseFloat(navigator.appVersion)*100);
osec=0,vt=0,today=0,time=0,Prt=0,Pvf=0,Pvl=0,Pvt=0,Drt=0,Dvf=0,Dvl=0,Dvt=0;
gL();
B1='<A HREF="http://wj.ax.xrea.com/c.f?id='+ID+'" TARGET=_blank><IMG style="width:80px;height:9px;" WIDTH=80 HEIGHT=9 SRC="http://j1.ax.xrea.com/';
BTS='ts';
if(navigator.userAgent.match(/KDDI/))BTS='ts_noad';
B2='.gif" BORDER=0></A>';
LAY += '<DIV style="top:'+Tpx+';left:'+Lpx+';position:absolute;z-index:2;visibility:hidden;" id="axL2" onmouseover="sL(\'axL1\')" onmouseout="sA()">'+B1+'x'+B2+'</DIV>';
LAY += '<DIV style="top:'+Tpx+';left:'+Lpx+';position:absolute;z-index:2;visibility:hidden;" id="axL1">'+B1+BTS+B2+'</DIV>';document.open();
if(ID<XID&&!(bn=="N"&&bv<500)){document.write(LAY);}
if(FRAME==1){rf=Escp(top.document.referrer)+"";url=Escp(top.document.URL)+"";bt=Escp(top.document.title);}
else if(FRAME==2){rf=Escp(parent.document.referrer)+"";url=Escp(parent.document.URL)+"";bt=Escp(parent.document.title);}
else{rf=Escp(document.referrer)+"";url=Escp(document.URL)+"";bt=Escp(document.title);}
if ((rf=="")||(rf.match(/^(undefined|unknown|bookmark)$/i))) rf="";
if(url==rf) rf="S";
P_=url.split("/");Path="/";for(i=3;P_[i+1];i++)Path+=P_[i]+'/';
dt=new Date();
time=Math.round(dt.getTime()/1000);
X=gCk("X");	O="";
if(!X||X.length!=RSTING) {	S="0123456789";
A=S.split("");	for(i=0;i<RSTING;i++){	R= Math.floor(Math.random() * S.length);	O+=A[R];}
X=O;sCk("X",O,"/");}else{sCk("X",X,"/");}
C="";
A=Array("","","","");
P=gCk("P");	A=P.split("-");	Prt=A[0];Pvf=A[1];Pvl=A[2];Pvt=A[3];
if(!Prt)Prt="";	if(!Pvf)Pvf="";	if(!Pvl)Pvl="";	if(!Pvt)Pvt="";	
if(!Prt||(!Prt.match(/^[0-9]+$/))) {C+="1"+"-";}else{++Prt;	C+=Prt+"-";}
if(!Pvf) {C+=time+"-";}else{C+=Pvf+"-";}
C+=time+"-";
if((!Pvl)||((Pvl)&&((time-Pvl)>VTIME))){vt=time;today=time;}else{vt=Pvt;today=Pvt;}
if((Pvt)&&((time-Pvt)<VTIME)){	today=Pvt;	osec=time-today;}
if(osec>VTIME)	{osec=VTIME;}	else if(osec<0) {osec=0;vt=time;}
C+=vt+"-";
sCk("P",C,Path);C="";
D=gCk("D");	A=D.split("-");	Drt=A[0];Dvf=A[1];Dvl=A[2];Dvt=A[3];
if(!Drt)Drt="";	if(!Dvf)Dvf="";	if(!Dvl)Dvl="";	if(!Dvt)Dvt="";
if(!Drt||(!Drt.match(/^[0-9]+$/))) {C+="1"+"-";}else{++Drt;	C+=Drt+"-";}
if(!Dvf) {C+=time+"-";}else{C+=Dvf+"-";}
C+=time+"-";
if((!Dvl)||((Dvl)&&((time-Dvl)>VTIME))){vt=time;today=time;}else{vt=Dvt;today=Dvt;}
if((Dvt)&&((time-Dvt)<VTIME)){	today=Dvt;	osec=time-today;}
if(osec>VTIME)	{osec=VTIME;}	else if(osec<0) {osec=0;vt=time;}
C+=vt+"-";
sCk("D",C,"/");
sw=screen.width;	sh=screen.height;
cd=(bn=="N")?screen.pixelDepth:screen.colorDepth;
je=(navigator.javaEnabled()==true)?"1":"";
if(bv>=400)	{pf=escape(navigator.platform);	if(pf=="Win32") pf="1";	else if(pf=="Win16") pf="2";	else if(pf=="MacPPC") pf="3";	else if(pf=="Mac68K") pf="4";	else if(pf=="HP-UX") pf="5";	else if(pf=="SunOS") pf="6";	else if(pf=="WinCE") pf="7";	else pf="0";}
if(bn=="M"&&bv>=400){cc=escape(navigator.cpuClass);	if(cc=="x86") cc="1";	else if(cc=="68K") cc="2";	else if(cc=="Alpha") cc="3";	else if(cc=="PPC") cc="4";	else cc="0";}
if(bn=="M"&&bv>=400) ln=navigator.browserLanguage;	else if(bn=="N"&&bv>=400) ln=navigator.language;	else ln="";
ct=ln.substring(3,5);		ct=ct.toLowerCase();	ln=ln.substring(0,2);
ce=(navigator.cookieEnabled==true)?"1":"";
tm=Pvf;if(tm>Pvl)tm=Pvl;if(tm>Pvt)tm=Pvt;if(tm>Pvf)tm=Dvf;if(tm>Dvl)tm=Dvl;if(tm>Dvt)tm=Dvt;
Pvf=Pvf-tm;Pvl=Pvl-tm;Pvt=Pvt-tm;Dvf=Dvf-tm;Dvl=Dvl-tm;Dvt=Dvt-tm;
logurl=LOGSCRIPT+"&x="+X+"&id="+ID+"&url="+url+"&rf="+rf+"&sw="+sw+"&sh="+sh+"&cd="+cd+"&je="+je+"&pf="+pf+"&cc="+cc+"&bt="+bt+"&ln="+ln+"&ct="+ct+"&ce="+ce+"&osec="+osec+"&tm="+tm+"&prt="+Prt+"&pvf="+Pvf+"&pvl="+Pvl+"&pvt="+Pvt+"&drt="+Drt+"&dvf="+Dvf+"&dvl="+Dvl+"&dvt="+Dvt+"&pname="+PNAME+"&chk="+XCHK;
if(XOK!=1){document.write('<SCR'+'IPT SRC="' + logurl + '" defer></SCR'+'IPT>');XOK=1;}
document.close();
