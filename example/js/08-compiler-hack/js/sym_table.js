var table = {};

var classSymTable={}, methodSymTable={};
var classStaticList, classFieldList, classSubroutineList;
var methodArgList, methodVarList;

var tableAdd=function(symTable, symbol) {
	if (symTable[symbol.name])
	  error("addSymbol: varName "+symbol.name+" duplicate!");
	else
	  symTable[symbol.name] = symbol;
}

var listAdd = function(list, symbol) {
	symbol.id = list.length;
	list.push(symbol);
}

table.add=function(symTable, symList, symbol) {
	tableAdd(symTable, symbol);
	listAdd(symList, symbol);
	console.log("addSymbol: %j", symbol);
}

table.lookup = function(name) {
	if (name in methodSymTable)
		return methodSymTable[name];
	else if (name in classSymTable)
		return classSymTable[name];
	else
		return null;
}

module.exports = table;
