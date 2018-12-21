#include "x86.h"

void as(char *x, char *rx) {
  int i = -1;
  if (isdigit(*x)) { // Number
    sprintf(rx, "$%s", x);
  } else if (*x == '_') { // Global
    sprintf(rx, "%s", x);
  } else if (*x == 'L') { // Local
    sscanf(x, "L%d", &i);
    sprintf(rx, "-%d(%%ebp)", (i+1)*4);
  } else if (*x == 'P') { // Param 參考: https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86
    sscanf(x, "P%d", &i);
    sprintf(rx, "%d(%%ebp)", (i+2)*4); // 0: saved ebp, 1: return address, 2: 第一個參數
  } else { // LABEL, ....
    sprintf(rx, "%s", x);
  }
}

// Intel 指令集參考 -- https://web.itu.edu.tr/kesgin/mul06/intel/index.html
// https://www.aldeid.com/wiki/X86-assembly/Instructions
// 注意: GNU 語法是目標在後的，所以 cmpl %eax, %ebx 會造成 (%ebx-%eax) 狀況的旗標改變。
void xCode(char *op, char *_d, char *_p1, char *_p2, char *x) {
  char d[SMAX], p1[SMAX], p2[SMAX];
  as(_d, d); as(_p1, p1); as(_p2, p2);
  if (strcmp(op, "label") == 0) {
    xEmit("%s:\n", d);
  } else if (strcmp(op, "file") == 0) {
    xEmit("	.file %s\n", d);
    xEmit("	.def	___main;	.scl	2;	.type	32;	.endef\n");
    // xEmit("	.comm	_t0, 4, 2\n	.comm	_t1, 4, 2\n	.comm	_t2, 4, 2\n	.comm	_t3, 4, 2\n	.comm	_t4, 4, 2\n	.comm	_t5, 4, 2\n	.comm	_t6, 4, 2\n	.comm	_t7, 4, 2\n	.comm	_t8, 4, 2\n");
  } else if (strcmp(op, "-file") == 0) {
    xEmit("	.ident	\"c0c: 0.0.1\"\n	.def	_puts;	.scl	2;	.type	32;	.endef\n");
  } else if (strcmp(op, "global") == 0) {
    xEmit("	.comm	%s, 4, 2\n", d);
  } else if (strcmp(op, "jmp") == 0) {
    xEmit("	jmp	%s\n", d);
  } else if (strcmp(op, "call") == 0) {
    xEmit("	call %s\n	movl %%eax, %s\n", p1, d);
  } else if (strcmp(op, "arg") == 0) {
    int argIdx = atoi(x);
    xEmit("	movl %s, %%eax\n", d);
    xEmit("	movl %%eax, %d(%%esp)\n", argIdx*4);
  } else if (strcmp(op, "str") == 0) {
    char literal[SMAX];
    sscanf(_p1, "\"%[^\"]*\"", literal);
    xEmit("	.section .rdata,\"dr\"\n%s:\n	.ascii \"%s\\0\"\n	.text\n", d, literal);
  } else if (strcmp(op, "jz") == 0) {
    xEmit("	movl	%s, %%eax\n	cmpl	$0, %%eax\n	je	%s\n", p1, d);
  } else if (strcmp(op, "jnz") == 0) {
    xEmit("	movl	%s, %%eax\n	cmpl	$0, %%eax\n	jne	%s\n", p1, d);
  } else if (strcmp(op, "++")==0) {
    char *sizeStr = (strcmp(x, "char*") == 0) ? "1" : "4";
    xCode("+", d, d, sizeStr, x);
  } else if (strcmp(op, "--")==0) {
    char *sizeStr = (strcmp(x, "char*") == 0) ? "1" : "4";
    xCode("-", d, d, sizeStr, x);
  } else if (*op=='=') {
    xEmit("	movl	%s, %%ebx\n	movl	%%ebx, %s\n", p1, d);
  } else if (strcmp(op, "function")==0) {
    xEmit("	.text\n	.globl	_%s\n	.def	%s;	.scl	2;	.type	32;	.endef\n_%s:\n", d, d, d);
    xEmit("	pushl	%%ebp\n	movl	%%esp, %%ebp\n");
    int frameSize = atoi(x);
    xEmit("	subl	$%d, %%esp\n", frameSize*4);
    if (strcmp(d, "main") == 0) { xEmit("	call	___main\n"); }
  } else if (strcmp(op, "return") == 0) {
    xEmit("	movl %s, %%eax\n	leave\n	ret\n", d);
  } else if (strcmp(op, "-function") == 0) {
    xEmit("	movl $0, %%eax\n	leave\n	ret\n"); // leave = movl %ebp, %esp + popl %ebp
  } else if (strcmp(op, "param")==0) {
  } else if (strcmp(op, "local") == 0) {
  } else if (strcmp(op, "extern") == 0) {
  } else if (isMember(op, "~ + - * / & | ^ && || [] ptr*")) {
    xEmit("	movl	%s, %%eax\n", p1);
    switch (*op) {
      // uniary operator
      case '~': xEmit("	notl	%%eax\n"); break;
      case 'p': xEmit("	movl	(%%eax), %%eax\n"); break; // ptr*
      // binary operator
      case '+': xEmit("	addl	%s, %%eax\n", p2); break;
      case '-': xEmit("	subl	%s, %%eax\n", p2); break;
      case '*': xEmit("	imull	%s, %%eax\n", p2); break;
      case '/': xEmit("	cltd\n	idivl	%s, %%eax\n", p2); break; // ??　	movl	_a, %eax	movl	_b, %ecx	cltd	idivl	%ecx	 # D.1567
      case '&': xEmit("	andl	%s, %%eax\n", p2); break;
      case '|': xEmit("	orl	%s, %%eax\n", p2); break;
      case '^': xEmit("	xorl	%s, %%eax\n", p2); break;
      case '[': 
        xEmit("	addl	%s, %%eax\n", p2);
        if (strcmp("int*", x)==0) xEmit("	shll	$2, %%eax\n"); // int* a[i] => a[i*4] => a[i<<2]
        break;
    }
    xEmit("	movl	%%eax, %s\n", d);
  } else if (isMember(op, "< > == != >= <=")) {
    // http://www.fermimn.gov.it/linux/quarta/x86/cmp.htm
    // CMP subtracts the second operand from the first but, unlike the SUB instruction, does not store the result; only the flags are changed.
    // CMP is typically used in conjunction with conditional jumps and the SETcc instruction. 
    // https://c9x.me/x86/html/file_module_x86_id_288.html (注意有號數和無號數的比較方法是不同的)
    // The terms "above" and "below" are associated with the CF flag and refer to the relationship between two unsigned integer values. 
    // The terms "greater" and "less" are associated with the SF and OF flags and refer to the relationship between two signed integer values.
    xEmit("	movl %s, %%eax\n	movl %s, %%ebx\n	cmpl %%ebx, %%eax\n", p1, p2); // cmpl %%ebx, %%eax 是 eax-ebx
    if (strcmp(op, "==")==0) xEmit("	sete %%al");
    if (strcmp(op, "!=")==0) xEmit("	setne %%al");
    if (strcmp(op, "<")==0) xEmit("	setl %%al");
    if (strcmp(op, "<=")==0) xEmit("	setle %%al");
    if (strcmp(op, ">")==0) xEmit("	setg %%al");
    if (strcmp(op, ">=")==0) xEmit("	setge %%al");
    xEmit("\n	movsbl	%%al, %%eax\n	movl	%%eax, %s\n", d); // 不能用 movzbl, 應該用 movsbl (move and sign extend)
  } else {
    xEmit(" --- not handle yet ! ----\n");
  }
}
