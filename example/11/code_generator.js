var fs = require("fs");
var wsVm;

var command = function(msg) {
  console.log(msg);
  wsVm.write(msg+"\n");
}

var gen = {
};

gen.openVmFile = function(file) {
  wsVm  = fs.createWriteStream(file);
}

gen.closeVmFile=function() {
  wsVm.end();
}

gen.method=function(tag, name, n) {
  command("function "+name+" "+n);
}

var opMap = { "+":"add", "-":"sub", "*":"call Math.multiply 2", "/":"call Math.divide 2", "&":"and", "|":"or", ">":"gt", "<":"lt", "=":"eq" };

gen.op=function(op) {
  command(opMap[op])
}

var op1Map = { "-":"neg", "~":"not" };

gen.op1=function(op) {
  command(op1Map[op])
}

gen.let=function(name) {
  command("pop "+name);
}

gen.stringConstant=function(str) {
  command('push constant '+str.length);
  gen.call("String.new", 1);
  for (var i=0; i<str.length; i++) {
    command('push constant '+str.charCodeAt(i));
    gen.call("String.appendChar", 2);
  }
}

gen.keywordConstant=function(str) {
  switch (str) {
    case "this" : gen.command("push pointer 0"); break;
    case "true" : gen.command("push constant 1"); gen.command("neg"); break;
    case "false": gen.command("push constant 0"); break;
    case "null" : gen.command("push constant 0"); break;
    default: throw Error("keywordConstant not found :"+str);
  }
}

gen.label = function(name) {
  command("label "+name);
}

gen.call=function(name, n) {
  command("call "+name+" "+n);
}

gen.command = function(cmd) {
  command(cmd);
}

gen.ret=function() {
  command("return");
}


module.exports = gen;