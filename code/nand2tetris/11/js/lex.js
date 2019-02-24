// Jack 詞彙分析器，用法範例： node lex <file>.jack
var lexer = require("./lexer");
lexer.scanFile(process.argv[2]);
