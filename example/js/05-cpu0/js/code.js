var c = require("./ccc");

var code = function(line, opTable) {
  this.parseR = function(str) {
    var rmatch = /R(\d+)/.exec(str);
    if (rmatch == null)
      return NaN;
    return parseInt(rmatch[1]);
  }

  this.toString = function() {
    return c.format("%s %s %s %s %s %s %s", c.hex(this.address, 4), 
      c.fill(' ',this.label,8), c.fill(' ',this.op.name, 8), 
      c.fill(' ',this.args, 16), this.op.type, c.hex(this.op.id,2), this.obj);
  }
  
  var labCmd = /^((\w+):)?\s*([^;]*)/;
  var parts  = labCmd.exec(line);           // 分割出標記與命令
  var tokens = parts[3].trim().split(/[ ,\t\r]+/); // 將命令分割成基本單元
  var opName = tokens[0];                   // 取出指令名稱
  
  this.label = c.nonull(parts[2]);          // 取出標記 (\w+)
  this.args  = tokens.slice(1);             // 取出參數部份
  this.op    = opTable[opName];
  this.obj   = ""; 
}

module.exports = code;
