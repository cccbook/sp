var c = require("./ccc");

var Op = function(line) {
    var tokens = line.split(/\s+/);
    this.name = tokens[0];
    this.id   = parseInt(tokens[1], 16);
    this.type = tokens[2];
}

var opTable = function(opList) {
  for (i in  opList) {
    var op = new Op(opList[i]);
    this[op.name] = op;
  }  
}

opTable.prototype.ID = function(op) { 
  return this[op].id; 
}

opTable.prototype.dump=function() {
    for (key in this) {
      var op = this[key];
      if (typeof(op)!="function")
        c.log("%s %s %s", c.fill(' ', op.name, 8), c.hex(op.id, 2), op.type);
    }
}

module.exports = opTable;
