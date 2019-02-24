// Jack 編譯器 (被 compile.js 呼叫)

var POINTER_THIS=0; // pointer [0] for this
var POINTER_THAT=1; // pointer [1] for that
var TEMP_RETURN=0;  // Use temp 0 for popping an unused return value
var TEMP_ARRAY=1;   // Use temp 1 for temporarily saving value to assign to array

var fs = require("fs");
var lib = require("./lib");
var lexer = require("./lexer");
var gen = require("./code_generator");

var stack, wsXml, tokens, tokenIdx;

var ID="identifier";
var TYPE="type";

var labelTop, classSymTable, methodSymTable;
var className, classStaticList, classFieldList, classSubroutineList;
var methodName, methodArgList, methodVarList;
var varKind, varType, varId;

var error=function(expect) {  
  var token = tokens[tokenIdx];
  log("Error: line=%d token (%s) do not match expect (%s)!", token.lines, token.token, expect); 
  log(new Error().stack);
  throw Error("error");
}

var newLabel = function() {
  labelTop++;
  return "label"+labelTop;
}

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
//  console.log("addSymbol: %j", symbol);
}

var symLookup = function(name) {
  if (name in methodSymTable)
    return methodSymTable[name];
  else if (name in classSymTable)
    return classSymTable[name];
  else
    return null;
}

var genPush=function(name) {
//  console.log("typeof name=%s name=%s", typeof name, name);
  if (typeof name === "number" || name.match(/\d+/)) {
    gen.command("push constant "+name);
  } else {
    var symbol = symLookup(name);
    if (symbol !== null) {
      gen.command("push "+symbol.kind+" "+symbol.id);
    } else 
      error("genPush : "+name+" not found!");
  }
}

var genPop=function(name) {
  var symbol = symLookup(name);
  if (symbol !== null) {
    gen.command("pop "+symbol.kind+" "+symbol.id);
  } else {
    error("genPop : "+name+" not found!");
  }
}

var log = function(msg) {
//  console.log(msg);
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
  classSymTable={}; classStaticList=[]; classFieldList=[]; classSubroutineList=[]; classSymTable={};
  next("{");
  while (isNext("static") || isNext("field")) {
    ClassVarDec();
  }
  while (!isNext('}')) {
    SubroutineDec();
  }
  popNT("class");
//  console.log("classStaticList=%j", classStaticList);
//  console.log("classFieldList=%j", classFieldList);
//  console.log("classSubroutineList=%j", classSubroutineList);
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
  varCount ++;
  while (isNext(",")) {
    next(",");
    name = VarName();
    varCount ++;
  }
}

// varName: ID
var VarName=function() {
  var name=nextType(ID);
  if (varKind == "let") return name;
  var symbol = { name:name, type:varType, kind:varKind };
  switch (varKind) {
    case "class": break;
    case "static": addSymbol(classSymTable, classStaticList, symbol); break;
    case "field": symbol.kind="this"; addSymbol(classSymTable, classFieldList, symbol); break;
    case "subroutine":addSymbol(classSymTable, classSubroutineList, symbol); break;
    case "argument": addSymbol(methodSymTable, methodArgList, symbol); break;
    case "var": symbol.kind="local"; addSymbol(methodSymTable, methodVarList, symbol); break;
    default:
      error("VarKind not Found!");
  }
  return name;
}

var methodTag;

// subroutineDec: ('constructor'|'function'|'method') ('void'|type) varName '(' parameterList? ')' subroutineBody
var SubroutineDec=function() {
  pushNT("subroutineDec");
  
  methodSymTable={}; methodArgList=[]; methodVarList=[];  
  
  methodTag = next(/(constructor)|(function)|(method)/); // ('constructor'|'function'|'method')
  if (isType() || isNext("void")) {
    var vtype = next();
    varKind = "subroutine";
    methodName = VarName();
    next("(");
    if (methodTag === "method") { // method 函數預設第一個參數為 this
      var symbol = { name:"this", type:className, kind:"argument" };
      addSymbol(methodSymTable, methodArgList, symbol);
    }
    if (!isNext(")")) {
      varKind = "argument";
      ParameterList();
    }
    next(")");
    SubroutineBody();
  } else 
    error("SubroutineDec(): void or type expected!");
  
//  console.log("methodArgList=%j", methodArgList);
//  console.log("methodVarList=%j", methodVarList);
//  console.log("methodSymTable=%j", methodSymTable);
  
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

var varCount;

// subroutineBody: '{' varDec* statements '}'
var SubroutineBody=function() {
  pushNT("subroutineBody");
  next("{");
  varCount = 0;
  while (isNext("var")) {
    VarDec();
  }
  gen.method(methodTag, className+"."+methodName, varCount);
  if (methodTag === "method") { // method 函數預設第一個參數為 this
    gen.command('push argument 0');
    gen.command('pop pointer '+POINTER_THIS); // set up 'this' pointer
  } else if (methodTag === "constructor") {
    genPush(classFieldList.length);
    gen.command('call Memory.alloc 1');
    gen.command('pop pointer '+POINTER_THIS); // set up 'this' pointer
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
  var name = VarName(), subscript = false;
  if (isNext("[")) {
    subscript = true;
    next("[");
    genPush(name);
    Expression();
    next("]");
    gen.command('add');
//    ArraySubscript(name);
  }
  next("=");
  Expression();
  next(";");
  if (subscript) {
    gen.command('pop temp '+TEMP_ARRAY);         // Pop expr value to temp register
    gen.command('pop pointer '+POINTER_THAT);    // Pop base+index into 'that' register
    gen.command('push temp '+TEMP_ARRAY);        // Push expr back onto stack
    gen.command('pop that 0');                   // Pop value into *(base+index)
  } else 
    genPop(name);
  popNT("letStatement");
}

// arraySubscript: '[' expression ']'
var ArraySubscript=function(arrayName) {
  genPush(arrayName);
  next("[");
  Expression();
  next("]");
  gen.command("add");
  gen.command("pop pointer "+POINTER_THAT); // pop into that ptr
  gen.command("push that 0"); //  push *(base+index) onto stack
}

// block = '{' statements '}'
var Block=function() {
  next("{");
  Statements();
  next("}");
}

// condExpression = ( expression ) block
var CondExpression=function(gotoLabel) {
  next("(");
  Expression();
  next(")");
  gen.command("not"); // ~(cond)
  var notifLabel = newLabel();
  gen.command("if-goto "+notifLabel);
  Block();
  gen.command("goto "+gotoLabel);
  gen.label(notifLabel);
}

// ifStatement : 'if' '(' expression ')' block '('else' block)?
var IfStatement=function() {
  pushNT("ifStatement");
  next("if");
  var endifLabel = newLabel();
  CondExpression(endifLabel);
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
  next("while");
  var whileLabel = newLabel();  
  gen.label(whileLabel);
  CondExpression(whileLabel);
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
    genPush("0");
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
    genPush(t);
  } else if (isNextType("stringConstant")) {
    t = nextType("stringConstant");
    gen.stringConstant(t);
  } else if (isNextType("keywordConstant")) {
    t = nextType("keywordConstant");    
    gen.keywordConstant(t);
  } else if (isNextType(ID)) {
    var name = nextType(ID);
    if (isNext("[")) {
      ArraySubscript(name);
    } else if (isNext("(") | isNext(".")) {
      back();
      Call();
    } else {
      genPush(name);
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
  var name1 = nextType(ID);
  var args = 0, callClass, callMethod;
  if (isNext("(")) {
    gen.command('push pointer '+POINTER_THIS); // push this as first argument
    args ++;
    callClass = className;
    callMethod = name1;
  } else if (isNext(".")) {
    next(".");
    callMethod = nextType(ID); // subroutineName
    var symbol = symLookup(name1);
    if (callClass in {"int":"", "boolean":"", "char":"", "void":""}) { // calling using builtin type
      error("Cannot use . operator on builtin type");
    } else if (symbol === null) {
      callClass = name1; // calling using class name =>  SomeClass.new();
    } else {
      callClass = symbol.type;
      genPush(name1);
      args++;
    }
  }
  next("(");
  args += ExpressionList();
  next(")");
  gen.call(callClass+"."+callMethod, args);
}

// expressionList: (expression (',' expression)*)?
var ExpressionList=function() {
  pushNT("expressionList");
  var expCount = 0;
  if (!isNext(")")) {
    Expression();
    expCount++;
  }
  while (isNext(",")) {
    next(",");
    Expression();
    expCount ++;
  }
  popNT("expressionList");
  return expCount;
}

var compileFile=function(path) {
  console.log("===========compile %s===================", path);  
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
  labelTop = 0;
  Class();
  wsXml.end();
  gen.closeVmFile();
//  console.log(JSON.stringify(classSymTable, null, 2));
}

module.exports = { compileFile: compileFile };
