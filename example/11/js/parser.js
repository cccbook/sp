// jackc 編譯器，用法範例： iojs jackc <file>.jack
var fs = require("fs");
var lib = require("./lib");
var lexer = require("./lexer");

var stack = [];
var ws = null;
var tokens = null;
var tokenIdx = 0;

var ID="identifier";
var TYPE="type";

var log = function(msg) {
	console.log(msg);
	ws.write(msg+"\n");
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
	if (isType())
		return next();
	else
		error("Type");
}

var varType = null;

// class : 'class' id '{' classVarDec* subroutineDec* '}'
var Class=function() {
	pushNT("class");
  next("class");
  var id = nextType(ID);
  next("{");
	while (isNext("static") || isNext("field")) {
		ClassVarDec();
	}
	while (!isNext('}')) {
		SubroutineDec();
	}
	popNT("class");
}

// classVarDec: {'static'|'field'} type varList ';' 
var ClassVarDec=function() {
	pushNT("classVarDec");
  varType = next(); // {'static'|'field'}
	Type();
	VarList();
	next(";");
	popNT("classVarDec");
}

// varList: varName (',' varName)*
var VarList=function() {
	var name=VarName();
	while (isNext(",")) {
		next(",");
		name = VarName();
	}
}

// varName: ID
var VarName=function() {
	return nextType(ID);
}

// subroutineDec: ('constructor'|'function'|'method') ('void'|type) ID '(' parameterList? ')' subroutineBody
var SubroutineDec=function() {
	pushNT("subroutineDec");
  var tag = next(/(constructor)|(function)|(method)/); // ('constructor'|'function'|'method')
	if (isType() || isNext("void")) {
		var vtype = next();
		nextType(ID);
		next("(");
		if (!isNext(")")) {
			varType = "argument";
			ParameterList();
		}
		next(")");
		SubroutineBody();
	}
	popNT("subroutineDec");
}

// parameterList: (parameter (',' parameter)*)?
var ParameterList=function() {
	pushNT("parameterList");
	Parameter();
	while (isNext(",")) {
		next(",");
		Parameter();
	}
	popNT("parameterList");
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
	varType = "var";
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
	VarName();
	if (isNext("[")) {
		ArraySubscript();
	}
	next("=");
	Expression();
	next(";");
	popNT("letStatement");
}

// arraySubscript: '[' expression ']'
var ArraySubscript=function() {
	next("[");
	Expression();
	next("]");
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
	Block();
	if (isNext("else")) {
		next("else");
		Block();
	}
	popNT("ifStatement");
}

// whileStatement: 'while' '(' expression ')' block
var WhileStatement=function() {
	pushNT("whileStatement");
	next("while");
	next("(");
	Expression();
	next(")");
	Block();
	popNT("whileStatement");	
}

// doStatement: 'do' call ';'
var DoStatement=function() {
	pushNT("doStatement");
	next("do");
	Call();
	next(";");
	popNT("doStatement");
}

// returnStatement: 'return' expression? ';'
var ReturnStatement=function() {
	pushNT("returnStatement");
	next("return");
	if (!isNext(";"))
		Expression();
	next(";")
	popNT("returnStatement");
}

// expression: term (op term)* 
var Expression=function() {
	pushNT("expression");
	Term();
	while (isNext(/[\+\-\*\/\&<>=]/)) { // op in "+/-*&<>="
		var op = next();
		Term();
	}
	popNT("expression");
}

// term: integerConstant | stringConstant | keywordConstant | varName arraySubscript?| call | '(' expression ')' | op1 term
var Term=function() {
	pushNT("term");
	if (isNextType("integerConstant")) {
		nextType("integerConstant");
	} else if (isNextType("stringConstant")) {
		nextType("stringConstant");
	} else if (isNextType("keywordConstant")) {
		nextType("keywordConstant");		
	} else if (isNextType(ID)) {
		var name = nextType(ID);
		if (isNext("[")) {
			ArraySubscript();
		} else if (isNext("(") | isNext(".")) {
			back();
			Call();
		}
	} else if (isNext("(")) {
		next("(");
		Expression();
		next(")");
	} else if (isNext("-") || isNext("~")) { // op1 = "-~"
		var op1=next();
		Term();
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
	} else if (isNext(".")) {
		next(".");
		var subName = nextType(ID);
		next("(")
		ExpressionList();
		next(")");
	}
}

// expressionList: (expression (',' expression)*)?
var ExpressionList=function() {
	pushNT("expressionList");
	Expression();
	while (isNext(",")) {
		next(",");
		Expression();
	}
	popNT("expressionList");
}

var parseFile=function(path) {
  file = path.split("/").pop();
	console.log("==============scan======================");
  tokens = lexer.scanFile(path);
  tokenIdx = 0;
	console.log("==============parse======================");
	var parseXmlFile = path.replace(".jack", ".xml");
  ws = fs.createWriteStream(parseXmlFile);
  stack = [];
  Class();
	ws.end();
}

module.exports = { parseFile: parseFile };
