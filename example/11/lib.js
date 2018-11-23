var fs = require("fs");

var Lib = {}

Lib.str2xml=function(str) {
	return str.replace("<", "&lt;").replace(">", "&gt;");
}

Lib.token2xml=function(t) {
	return "<"+t.type+"> "+Lib.str2xml(t.token)+" </"+t.type+">";	
}

Lib.isDir=function(path) {
  if (fs.existsSync(path)) {
    var stat = fs.statSync(path);
	  if (stat.isDirectory())
		  return true;
	}
	return false;
}

module.exports = Lib;
