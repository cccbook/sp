var util = require("util");
var assert = require("assert");
var fs = require("fs");
var c = require("./ccc");

var Memory = function(size) {
  this.m = new Buffer(size);

  this.getb = function(i) { return this.m.readUInt8(i) }
  this.geti = function(i) { return this.m.readInt32BE(i); }
  this.getw = function(i) { return this.m.readUInt32BE(i); }
  this.setb = function(i, b) { return this.m.writeUInt8(b, i); }
  this.seti = function(i, w) { return this.m.writeInt32BE(w, i); }
  this.setw = function(i, w) { return this.m.writeUInt32BE(w, i); }
  this.setstr = function(i, str) { 
    this.m.write(str, i, str.length, "ascii"); 
    this.setb(i+str.length, 0);  // 寫入字串尾 \0
  }
  this.getstr = function(i) { 
    var str = "";
    for (len=0; ; len++) {
        if (this.getb(i+len) == 0) 
            break;
    }
    return this.m.toString("ascii", i, i+len);
  }
  
  this.load = function(path) {
    this.path = path;
    var stats = fs.statSync(path);
    this.m = new Buffer(stats.size);
    var fd = fs.openSync(path, 'r', 0666);
    fs.readSync(fd, this.m, 0, this.m.length, null);
    fs.closeSync(fd);
  }
  
  this.loadhex = function(hex) {
    assert.ok(hex.length %2 == 0);
    this.m = new Buffer(hex.length/2);
    for (i=0; i<hex.length; i+=2) {
      var h2 = hex.substr(i, 2);
      var b = parseInt(h2, 16);
      this.m.writeUInt8(b, i/2);
    }
  }

  this.dump = function() { 
    dstr = "";
    for (i=0; i<this.m.length; i++) {
      if (i%16==0) dstr += "\n"+c.hex(i,2)+" : ";
      if (i%4==0) dstr += " ";
      dstr += c.hex(this.getb(i), 2);
    }
    c.log(dstr);
  }

  this.save = function(path) {
    if (path==null) path = this.path;
    var fd = fs.openSync(path, 'w', 0666);
    fs.writeSync(fd, this.m, 0, this.m.length, null);
    fs.closeSync(fd);
  }
  
  this.test = function() {
    c.log("========= memory ===========");
    this.load("test.obj");
    this.seti(0, 123);
    c.log("m[0]=%s\n", this.geti(0));
    this.setstr(5, "Hello!");
    var str = this.getstr(5);
    c.log("str=%s", str);
    this.dump();
    this.save("test.obj.bak");
}
  
};

if (process.argv[2] == "-d")
    (new Memory(100)).test();

module.exports = Memory;
