// jackc 編譯器，用法範例： node compile <file>.jack
var fs = require("fs");
var lib = require("./lib");
var compiler = require("./compiler");

var path = process.argv[2];

if (lib.isDir(path)) {
	var files = fs.readdirSync(path);
	for (var i in files) {
		if (files[i].endsWith(".jack")) {
			compiler.compileFile(path+"/"+files[i]);
		}
	}
} else {
  compiler.compileFile(path);
}
