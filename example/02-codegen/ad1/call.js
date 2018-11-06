const UglifyJS = require('uglify-js')

var code = function toplevel() {
  var a = foo("x", "y", (function(){
      var b = "stuff";
      var c = "bar";
  })(), 1, "z");
};
code = code.toString();
console.log(code)
var toplevel = UglifyJS.parse(code);

var call_expression = null;
var walker = new UglifyJS.TreeWalker(function(node, descend){
  if (node instanceof UglifyJS.AST_Call) {
    console.log('f=', )
    let args = []
    for (let arg of node.args) {
      args.push(arg.value)
    }
    console.log('args=', args)
    return true; // prevent descending again
  }

});
toplevel.walk(walker);