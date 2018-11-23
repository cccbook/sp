const UglifyJS = require('uglify-js')

var ast = UglifyJS.parse("function sum(x, y){ return x + y }")

console.log('ast=', ast)
