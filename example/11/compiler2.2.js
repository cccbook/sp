// pointer [0] = this, [1]=that
var fs = require("fs");
var lib = require("./lib");
var lexer = require("./lexer");
var gen = require("./code_generator");

var stack = [];
var wsXml = null;
var tokens = null;
var tokenIdx = 0;

var ID="identifier";
var TYPE="type";

var classSymTable={}, methodSymTable={};
var className, classStaticList, classFieldList, classSubroutineList;
var methodName, methodArgList, methodVarList;
var varKind, varType, varId;

var tableAdd=function(symTable, symbol) {
	if (symTable[symbol.name])
	  error("addSymbol: varName "+symbol.name+" duplicate!");
	else
	  symTable[symbol.name] = symbol;
}

var listAdd = function(list, symbol) {
	symbol.id = list.length;
	list.push(symbol);
}

var addSymbol=function(symTable, symList, symbol) {
	tableAdd(symTable, symbol);
	listAdd(symList, symbol);
	console.log("addSymbol: %j", symbol);
}

var symLookup = function(name) {
	if (name in methodSymTable)
		return methodSymTable[name];
	else if (name in classSymTable)
		return classSymTable[name];
	else
		return null;
}

var genPush=function(t) {
	if (typeof t === "Number" || t.match(/\d+/)) {
		gen.command("push constant "+t);
	} else {
		var symbol = symLookup(t);
		if (symbol !== null) {
			gen.command("push "+symbol.)
		}
	}
}

/*
    def vm_push_variable(self, name):
        (type, kind, index) = self.symbols.lookup(name)
        self.vm.write_push(segments[kind], index)
        
    def vm_pop_variable(self, name):
        (type, kind, index) = self.symbols.lookup(name)
        self.vm.write_pop(segments[kind], index)  
*/
				
var genPop=function(t) {
	throw Error("gen:pop");
}

var log = function(msg) {
//	console.log(msg);
	wsXml.write(msg+"\n");
}

var pushNT=function(tag) { // push NonTerminal (NT)
	stack.push(tag);
  log("<"+tag+">");
}

var popNT=function(tag) { // pop NonTerminal (NT)
	var pTag = stack.pop();
	if (pTag !== tag) 
		error("popNT");
  log("</"+tag+">");
}

var error=function(expect) {  
  var token = tokens[tokenIdx];
  log("Error: line=%d token (%s) do not match expect (%s)!", token.lines, token.token, expect); 
  log(new Error().stack);
  throw Error("error");
}

var skip=function(o) { if (isNext(o)) next(o); }

var next=function(o) {
	log(lib.token2xml(tokens[tokenIdx]));
  if (typeof o === 'undefined' || o==null || isNext(o)) {
    return tokens[tokenIdx++].token;
  }
  error(o);
}

var back=function(o) {
	tokenIdx--;
}

var isNext=function(o) {
  if (tokenIdx >= tokens.length) 
    return false;
  var token = tokens[tokenIdx].token;
  if (o instanceof RegExp) {
    return token.match(o);
  } else
    return (token == o);
}

var nextType=function(o) {
	log(lib.token2xml(tokens[tokenIdx]));
  if (o==null || isNextType(o)) {
    return tokens[tokenIdx++].token;
  }
  error(o);
}

var isNextType=function(pattern) {
  var type = tokens[tokenIdx].type;
  return (("|"+pattern+"|").indexOf("|"+type+"|")>=0);
}

function isType() {
	return isNext(/(int)|(char)|(boolean)/) || isNextType(ID);
}

function Type() {
	if (isType()) {
		varType= next();
		return varType;
	}
	else
		error("Type");
}

// class : 'class' VarName '{' classVarDec* subroutineDec* '}'
var Class=function() {
	pushNT("class");
  next("class");
	varKind = "class";
	className = VarName();
	classStaticList=[]; classFieldList=[]; classSubroutineList=[]; classSymTable={};
  next("{");
	while (isNext("static") || isNext("field")) {
		ClassVarDec();
	}
	while (!isNext('}')) {
		SubroutineDec();
	}
	popNT("class");
	console.log("classStaticList=%j", classStaticList);
	console.log("classFieldList=%j", classFieldList);
	console.log("classSubroutineList=%j", classSubroutineList);
}

// classVarDec: {'static'|'field'} type varList ';' 
var ClassVarDec=function() {
	pushNT("classVarDec");
  varKind = next(); // {'static'|'field'}
	Type();
	VarList();
	next(";");
	popNT("classVarDec");
}

// varList: varName (',' varName)*
var VarList=function() {
	var list = [];
	var name=VarName();
	while (isNext(",")) {
		next(",");
		name = VarName();
	}
}

// varName: ID
var VarName=function() {
	var name=nextType(ID);
	if (varKind == "let") return;
	var symbol = { name:name, type:varType, kind:varKind };
	switch (varKind) {
		case "class": break;
		case "static": addSymbol(classSymTable, classStaticList, symbol); break;
		case "field": addSymbol(classSymTable, classFieldList, symbol); break;
		case "subroutine":addSymbol(classSymTable, classSubroutineList, symbol); break;
		case "argument": addSymbol(methodSymTable, methodArgList, symbol); break;
		case "var": addSymbol(methodSymTable, methodVarList, symbol); break;
		default:
		  error("VarKind not Found!");
	}
	return name;
}

// subroutineDec: ('constructor'|'function'|'method') ('void'|type) varName '(' parameterList? ')' subroutineBody
var SubroutineDec=function() {
	pushNT("subroutineDec");
	
	methodArgList=[]; methodVarList=[];	methodSymTable={};
	
  var tag = next(/(constructor)|(function)|(method)/); // ('constructor'|'function'|'method')
	if (isType() || isNext("void")) {
		var vtype = next();
		varKind = "subroutine";
		methodName = VarName();
		next("(");
		var params = 0;
		if (!isNext(")")) {
			varKind = "argument";
			params = ParameterList();
		}
		next(")");
		gen.method(tag, className+"."+methodName, params);
		SubroutineBody();
	}
	
	
	console.log("methodArgList=%j", methodArgList);
	console.log("methodVarList=%j", methodVarList);
	console.log("methodSymTable=%j", methodSymTable);
	
	popNT("subroutineDec");
}

// parameterList: (parameter (',' parameter)*)?
var ParameterList=function() {
	pushNT("parameterList");
	var params = 0;
	Parameter();
	while (isNext(",")) {
		next(",");
		Parameter();
		params ++;
	}
	popNT("parameterList");
	return params;
}

// parameter: type varName
var Parameter=function() {
	Type();
  VarName();
}

// subroutineBody: '{' varDec* statements '}'
var SubroutineBody=function() {
	pushNT("subroutineBody");
	next("{");
	while (isNext("var")) {
		VarDec();
	}
  Statements();	
	next("}");
	popNT("subroutineBody");
}

// varDec: 'var' type varList ';'
var VarDec=function() {
	pushNT("varDec");
	next("var");
	varKind = "var";
	Type();
	VarList();
	next(";");
	popNT("varDec");
}

// statements : statement*
var Statements=function() {
	pushNT("statements");
	while (!isNext("}")) {
		Statement();
	}
	popNT("statements");
}

// statement: letStatement | ifStatement | whileStatement | doStatement | returnStatement
var Statement=function() {
	if (isNext("let")) {
		LetStatement();
	} else if (isNext("if")) {
		IfStatement();
	} else if (isNext("while")) {
		WhileStatement();
	} else if (isNext("do")) {
		DoStatement();
	} else if (isNext("return")) {
		ReturnStatement();
	} else {
		error("STATEMENT=>");
	}
}

// letStatement: 'let' varName ( arraySubscript )? '=' expression ';'
var LetStatement=function() {
	pushNT("letStatement");
	next("let");
	varKind="let";
	var name = VarName();
	if (isNext("[")) {
		ArraySubscript();
	}
	next("=");
	Expression();
	next(";");
	gen.pop(name);
	popNT("letStatement");
}

// arraySubscript: '[' expression ']'
var ArraySubscript=function(arrayName) {
	gen.push(arrayName);
	next("[");
	Expression();
	next("]");
	gen.command("add");
	gen.command("pop pointer 1"); // pop into that ptr
	gen.command("push that 0"); //  push *(base+index) onto stack
}

// block = '{' statements '}'
var Block=function() {
	next("{");
	Statements();
	next("}");
}

// ifStatement : 'if' '(' expression ')' block '('else' block)?
var IfStatement=function() {
	pushNT("ifStatement");
	next("if");
	next("(");
	Expression();
	next(")");
	var elseLabel = newLabel(), endifLabel = newLabel();	
	gen.command("not");
	gen.command("if-goto "+elseLabel);
	Block();
	gen.command("goto "+endifLabel);
  gen.label(elseLabel);
	if (isNext("else")) {
		next("else");
		Block();
	}
	gen.label(endifLabel);
	popNT("ifStatement");
}

// whileStatement: 'while' '(' expression ')' block
var WhileStatement=function() {
	pushNT("whileStatement");
	var whileLabel = newLabel();
	next("while");
	next("(");
	Expression();
	next(")");	
	var wendLabel = newLabel();
	gen.command("not");
	gen.command("if-goto "+wendLabel);
	Block();
	gen.command("goto "+whileLabel);
	popNT("whileStatement");	
}

// doStatement: 'do' call ';'
var DoStatement=function() {
	pushNT("doStatement");
	next("do");
	Call();
	next(";");
	popNT("doStatement");
	gen.command("pop temp 0");
}

// returnStatement: 'return' expression? ';'
var ReturnStatement=function() {
	pushNT("returnStatement");
	next("return");
	if (!isNext(";"))
		Expression();
  else
		gen.push("0");
	next(";")
	gen.ret();
	popNT("returnStatement");
}

// expression: term (op term)* 
var Expression=function() {
	pushNT("expression");
	var t1 = Term();
	while (isNext(/[\+\-\*\/\&\|<>=]/)) { // op in "+/-*&|<>="
		var op = next();
		var t2 = Term();
		gen.op(op);
	}
	popNT("expression");
}

// term: integerConstant | stringConstant | keywordConstant | varName arraySubscript?| call | '(' expression ')' | op1 term
var Term=function() {
	var t;
	pushNT("term");
	if (isNextType("integerConstant")) {
		t = nextType("integerConstant");
    gen.push(t);
	} else if (isNextType("stringConstant")) {
		t = nextType("stringConstant");
		gen.stringConstant(t);
	} else if (isNextType("keywordConstant")) {
		t = nextType("keywordConstant");		
		gen.keywordConstant();
	} else if (isNextType(ID)) {
		var name = nextType(ID);
		if (isNext("[")) {
			ArraySubscript();
		} else if (isNext("(") | isNext(".")) {
			back();
			Call();
		} else {
			gen.push(name);
		}
	} else if (isNext("(")) {
		next("(");
		Expression();
		next(")");
	} else if (isNext("-") || isNext("~")) { // op1 = "-~"
		var op1=next();
		Term();
		gen.op1(op1);
	}
	popNT("term");
}

// call: subroutineName '(' expressionList ')' | (className | varName) '.' subroutineName '(' expressionList ')'
var Call=function() {
  var name = nextType(ID);
	if (isNext("(")) {
		next("(");
		ExpressionList();
		next(")");
		gen.call(name, expCount);
	} else if (isNext(".")) {
		next(".");
		var subName = nextType(ID);
		next("(")
		ExpressionList();
		next(")");
		gen.call(name+"."+subName, expCount);
	}
}

var expCount = 0;
// expressionList: (expression (',' expression)*)?
var ExpressionList=function() {
	pushNT("expressionList");
	Expression();
	expCount=1;
	while (isNext(",")) {
		next(",");
		Expression();
		expCount ++;
	}
	popNT("expressionList");
}

var compileFile=function(path) {
  file = path.split("/").pop();
	console.log("==============scan======================");
  tokens = lexer.scanFile(path);
  tokenIdx = 0;
	console.log("==============parse======================");
	var parseXmlFile = path.replace(".jack", ".xml");
  wsXml = fs.createWriteStream(parseXmlFile);
	var vmFile = path.replace(".jack", ".vm");
  gen.openVmFile(vmFile);
  stack = [];
  Class();
	wsXml.end();
	gen.closeVmFile();
	console.log(JSON.stringify(classSymTable, null, 2));
}

module.exports = { compileFile: compileFile };
