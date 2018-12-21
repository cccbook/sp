// jackc 編譯器，用法範例： iojs jackc <file>.jack
var fs = require("fs");
var lib  = require("./lib");

var lexer = {
	tokens : [],
	tokenIdx : 0
}

var log = function(ws, msg) {
//	console.log(msg);
	ws.write(msg+"\n");
}

lexer.scanFile=function(path) {
	var text = fs.readFileSync(path, "utf8");
	var scanXmlFile = path.replace(".jack", "T.xml");
  var ws = fs.createWriteStream(scanXmlFile);
	log(ws, "<tokens>");
  var re = /\/\*([\s\S]*?)\*\/|\/\/([^\r\n]*)[\r\n]|"(.*?)"|(\d+)|([a-zA-Z]\w*)|([>=<!\+\-\*\/&%|\.\(\)\{\}\[\];,])|(\s+)|(.)/gm;
  var types = [ "", "comment", "comment", "stringConstant", "integerConstant", "identifier", "symbol", "space", "ch" ];
	var keyMap = { "int":"keyword", "boolean":"keyword", "char":"keyword", "class":"keyword", "function":"keyword", "var":"keyword", "let":"keyword", "do":"keyword", "void":"keyword", "if":"keyword", "else":"keyword","while":"keyword", "constructor": "keyword", "method":"keyword", "static":"keyword", "return":"keyword", "true":"keywordConstant", "false":"keywordConstant", "null":"keywordConstant", "this":"keywordConstant" };
  tokens = [];
  tokenIdx = 0;
  var lines = 1, m;
  while((m = re.exec(text)) !== null) {
    var token = m[0], type;
    for (i=1; i<=9; i++) {
      if (m[i] !== undefined) {
        type = types[i];
				token = m[i];
				break;
			}
    }
		if (type==="identifier") {
			if (token in keyMap)
				type = keyMap[token];
		}
    if (!token.match(/^[\s\r\n]/)) {
			var t = { "token":token, "type":type, "lines":lines };
			if (type!=="comment") {
				log(ws, lib.token2xml(t));
        tokens.push(t);
			}
		}
    lines += token.split(/\n/).length-1;
  }
	log(ws, "</tokens>");
  ws.end();
  return tokens;
}

module.exports = lexer;
