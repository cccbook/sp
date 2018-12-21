// jackc 編譯器，用法範例： iojs jackc <file>.jack
var parser = require("./parser"); 

var path = process.argv[2];
parser.parseFile(path);
