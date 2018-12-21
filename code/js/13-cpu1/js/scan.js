// 本來應該用 .*? 來比對 /*...*/ 註解的，但 javascript 的 . 並不包含 \n, 因此用 \s\S 代替 . 就可以了。
var re = /(\/\*[\s\S]*?\*\/)|(\/\/[^\r\n])|(\d+)|([a-zA-Z]\w*)|(\r?\n)|(.)/gm; // *?, +? non greedy, m for multiline
text = "a=3+x-num*99; // comment\r\n y=5; /* block \r\n comment 1 */ z=3; /* block comment 2 */";
var tokens = text.match(re);
console.log(tokens);
