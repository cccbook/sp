// j0c 編譯器，用法範例： node j0c test.j0
var fs = require("fs");
var util = require("util");
var log = console.log;     // 將 console.log 名稱縮短一點
var format = util.format;  // 字串格式化
var tokens = [];
var tokenIdx = 0;
var end = "$END";
var funcName = "main";
var funcStack = [ funcName ];
var symTable = {};
symTable[funcName] = { type:"function", name:"main", pcodes:[] };

var scan=function(text) { 
  var re = new RegExp(/(\/\*[\s\S]*?\*\/)|(\/\/[^\r\n])|(".*?")|(\d+(\.\d*)?)|([a-zA-Z]\w*)|([>=<!\+\-\*\/&%|]+)|(\s+)|(.)/gm);
  var types = [ "", "COMMENT", "COMMENT", "STRING", "INTEGER", "FLOAT", "ID", "OP2", "SPACE", "CH" ];
  tokens = [];
  tokenIdx = 0;
  var lines = 1, m;
  while((m = re.exec(text)) !== null) {
    var token = m[0], type;
    for (i=1; i<=9; i++) { 
      if (m[i] !== undefined)
        type = types[i];
    }
    if (!token.match(/^[\s\r\n]/) && type!="COMMENT") {
      tokens.push({ "token":token, "type":type, "lines":lines });
    }
    lines += token.split(/\n/).length-1;
  }
  tokens.push({ "token": end, "type":end, "lines":lines });
  return tokens;
}

var error=function(expect) {  
  var token = tokens[tokenIdx];
  log("Error: line=%d token (%s) do not match expect (%s)!", token.lines, token.token, expect); 
  log(new Error().stack);
  process.exit(1);
}

var skip=function(o) { if (isNext(o)) next(o); }

var next=function(o) {
  if (o==null || isNext(o)) {
    return tokens[tokenIdx++].token;
  }
  error(o);
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
  if (o==null || isNextType(o)) {
    return tokens[tokenIdx++].token;
  }
  error(o);
}

var isNextType=function(pattern) {
  var type = tokens[tokenIdx].type;
  return (("|"+pattern+"|").indexOf("|"+type+"|")>=0);
}

var pcode=function(label, op, p, p1, p2) {
  symTable[funcName].pcodes.push({"label":label, "op":op, "p":p, "p1":p1, "p2":p2});
  var irCode = format("%s\t%s\t%s\t%s\t%s", label, op, p, p1, p2);
  log(irCode);
}

var tempIdx = 1;
var nextTemp=function() { 
  var name="T"+tempIdx++;
  symTable[name] = { type:"var", name:name };
  return name; 
}

var labelIdx = 1;
var nextLabel=function() { return "L"+labelIdx++; }

var elseIdx = 1;
var nextElse=function() { return "else"+elseIdx++; }

var compile=function(text) {
  scan(text);
  PROG();
}

// PROG = STMTS
var PROG=function() {
  STMTS();
}

// STMTS = STMT*
var STMTS=function() {
  while (!isNext("}") && !isNext(end))
    STMT();
}

// BLOCK = { STMTS }
var BLOCK=function() {
  next("{");
  STMTS();
  next("}");
}

// STMT = FOR | WHILE | IF | FUNCTION | return EXP ; | ASSIGN ; | BLOCK
var STMT=function() {
  if (isNext("for")) {
    FOR();
  } else if (isNext("while")) {
    WHILE();
  } else if (isNext("if")) {
    IF();
  } else if (isNext("function")) {
    FUNCTION();
  } else if (isNext("return")) {
    next("return");
    var e = EXP();
    pcode("", "return", e, "", "");
    next(";");
  } else if (isNext("{")) {
    BLOCK();
  } else {
    ASSIGN();
    next(";");
  }
}

// FOR = for (ID in EXP) BLOCK
var FOR=function() {
  var startLabel = nextLabel(), exitLabel = nextLabel();
  next("for"); 
  next("("); 
  var id = nextType("ID");
  pcode("", "=", id, "0", "");
  next("in");
  var e=EXP(); 
  next(")");
  var tLen = nextTemp();
  pcode(startLabel, "length", tLen, e, "");
  var tCmp = nextTemp();
  pcode("", "<", tCmp, id, tLen);
  pcode("", "if0", tCmp, exitLabel, "");
  BLOCK(); 
  pcode("", "goto", startLabel, "", "");
  pcode(exitLabel, "", "", "", "");
}

// WHILE = while (EXP) BLOCK
var WHILE=function() {
  var startLabel = nextLabel(), exitLabel=nextLabel();
  pcode(startLabel, "", "", "", "");
  next("while"); 
  next("("); 
  var e = EXP(); 
  next(")"); 
  pcode("", "if0", e, exitLabel, "");
  BLOCK();
  pcode("", "goto", startLabel, "", "");
  pcode(exitLabel, "", "", "", "");
}

// IF = if (EXP) STMT (else STMT)?
var IF=function() {
  next("if"); 
  next("("); 
  var e = EXP(); 
  next(")"); 
  var elseLabel = nextLabel();
  pcode("", "if0", e, elseLabel, "");
  STMT();
  if (isNext("else")) {
    next("else");
    pcode(elseLabel, "", "", "", "");
    STMT();
  }
}

// ASSIGN = ID[++|--]?(=EXP?)?
var ASSIGN=function() {
  var id, op, hasNext = false;
  if (isNextType("ID")) {
    id = nextType("ID");
    symTable[id] = { type:"var", name:id };
    if (isNext("++") || isNext("--")) {
      var op = next(null);
      pcode("", op, id, "", "");
    }
    hasNext = true;
  }
  if (isNext("=")) {
    next("=");
    var e = EXP();
    if (id != undefined)
      pcode("", "=", id, e, "");
    hasNext = true;
  }
  if (!hasNext)
    return EXP();
}

// EXP=TERM (OP2 TERM)?
var EXP=function() {
  t1 = TERM();
  if (isNextType("OP2")) {
    var op2 = next(null);
    t2 = TERM();
    var t = nextTemp();
    pcode("", op2, t, t1, t2);
    t1 = t;
  }
  return t1;
}

// TERM=STRING | INTEGER | FLOAT | ARRAY | TABLE | ID (TERMS)? | ID [TERMS]?| ( EXP )
var TERM=function() {
  if (isNextType("STRING|INTEGER|FLOAT")) {
    return next(null);
  } else if (isNext("[")) {
    return ARRAY();
  } else if (isNext("{")) {
    return TABLE();
  } else if (isNextType("ID")) { // function call
    var id = next(null);
    if (isNext("(")) { 
      next("("); 
      while (!isNext(")")) {
        // TERM();
        var arg = next(null);
        pcode("", "arg", arg, "", "");
        skip(",");
      }
      next(")");
      var ret = nextTemp();
      pcode("", "call", ret, id, "");
      return ret;
    }
    var array = id;
    if (isNext("[")) { 
      next("["); 
      while (!isNext("]")) {
        var idx = TERM();
        var t = nextTemp();
        pcode("", "[]", t, array, idx);
        skip(",");
        array = t;
      }
      next("]");
      return array;
    }
    return id;
  } else if (isNext("(")) {
    next("(");  
    var e = EXP();  
    next(")");
    return e;
  } else error();
}

// FUNCTION = function ID(ARGS) BLOCK
var FUNCTION = function() {
  next("function");
  funcName = nextType("ID");
  funcStack.push(funcName);
  symTable[funcName] = { type:"function", name:funcName, pcodes: [] };
  pcode(funcName, "function", "", "", "");
  next("(");
  while (!isNext(")")) {
    var arg=nextType("ID");
    pcode("", "param", arg, "", "");
    skip(",");
  }
  next(")"); 
  BLOCK();
  pcode("", "endf", "", "", "");
  funcStack.pop();
  funcName = funcStack[funcStack.length-1];
}

// ARRAY = [ TERMS ];
var ARRAY = function() {
  next("[");
  var array = nextTemp();
  pcode("", "array", array, "", "");
  while (!isNext("]")) {
    var t = TERM();
    pcode("", "apush", array, t, "");
    skip(",");
  }
  next("]");
  return array;
}

// TABLE = { (TERM:TERM)* }
var TABLE = function() {
  next("{"); 
  var table = nextTemp();
  pcode("", "table", table, "", "");
  while (!isNext("}")) {
    var key = TERM(); 
    next(":"); 
    var value = TERM();
    skip(",");
    pcode("", "map", table, key, value);
  }
  next("}");
  return table;
}

var source = fs.readFileSync(process.argv[2], "utf8");
compile(source);
