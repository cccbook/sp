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
      var tmp = call_expression;
      call_expression = node;
      descend();
      call_expression = tmp;
      return true; // prevent descending again
  }
  if (node instanceof UglifyJS.AST_Lambda) { // ← here
      // when encounters a lambda, temporarily forget
      // the call expression.
      var tmp = call_expression;
      call_expression = null;
      descend();
      call_expression = tmp;
      return true; // again, to prevent diving this node twice
  }
  if (node instanceof UglifyJS.AST_String && call_expression) {
      console.log("Found string: %s at %d,%d", node.getValue(),
                  node.start.line, node.start.col);
  }
});
toplevel.walk(walker);