#include "vm.h"

int argTop = 0, localTop = 0, paramTop = 0, tempTop = 0;
int argIdx = 0, labelIdx = 0, tempIdx = 0;
int vmCodeTop = 0, vmGlobalTop = 0;
VmCode vmCodes[CODEMAX], vmGlobals[CODEMAX], *fCode = NULL;
Pair localList[CODEMAX], globalList[CODEMAX];
Map  symLocal, symGlobal;

VmCode *lookup(char *name) {
  VmCode *c = mapLookup(&symLocal, name);
  if (c != NULL) return c;
  c = mapLookup(&symGlobal, name);
  if (c != NULL) return c;
  return NULL;
}

char *vmId(char *name) {
  if (isdigit(*name) || *name=='\0') return name;
  VmCode *c = mapLookup(&symLocal, name);
  if (c != NULL) return c->x;
  c = mapLookup(&symGlobal, name);
  if (c != NULL) {
    if (strcmp(c->op, "str") == 0)
      return stPrint("$%s", c->d);
    else // global or extern
      return stPrint("_%s", c->d);
  }
  if (*name == '_') return name;
  return stPrint("?%s", name);
}

/*
char *vmId(char *name) {
  if (isdigit(*name) || *name=='\0') return name;
  VmCode *c = lookup(name);
  if (*name == '_') return name;
  if (c == NULL) return stPrint("?%s", name);
  if (strcmp(c->op, "str")==0)
    return stPrint("$%s", c->d);
  else if (isMember(c->op, "extern global")) 
    return stPrint("_%s", c->d);
  else // local
    return c->_p2;
}
*/

VmCode vmCodeNew(char *op, char *d, char *p1, char *p2) {
  VmCode c = { .op=op, .d=d, .p1=p1, .p2=p2, ._d=d, ._p1=p1, ._p2=p2, .x="" };
  if (!isMember(op, "file str global extern function param local label -function -file")) {
    c._d=vmId(d); c._p1=vmId(p1); c._p2=vmId(p2);
  }
  return c;
}

void vmInit() {
  vmCodeTop = 0;
  vmGlobalTop = 0;
  mapNew(&symLocal, localList, SYMMAX);
  mapNew(&symGlobal, globalList, SYMMAX);
  vmGlobal("extern", "printf", "", "");
}

VmCode *vmCode(char *op, char *d, char *p1, char *p2) {
  vmCodes[vmCodeTop] = vmCodeNew(op, d, p1, p2);
  VmCode *c = &vmCodes[vmCodeTop++];
  if (strcmp(op, "function")==0) {
    symLocal.top = localTop = paramTop = tempTop = argTop = 0;
    fCode = c;
    mapAdd(&symGlobal, d, c);
  } else if (strcmp(op, "label")==0) {
  } else if (strcmp(op, "param")==0) {
    c->x = stPrint("P%d", paramTop++);
    mapAdd(&symLocal, d, c);
  } else if (strcmp(op, "local")==0) {
    c->x = stPrint("L%d", localTop++);
    mapAdd(&symLocal, d, c);
  } else if (strcmp(op, "-function")==0) {
    // 參考: https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86
    int argSize = argTop + 1; // +1 存放 return address
    int frameSize = MAX(localTop, argSize) + 1; // +1 存放 saved ebp
    fCode->x = stPrint("%d", frameSize);
  } else if (strcmp(op, "call")==0) {
    argIdx = 0;
  } else if (strcmp(op, "arg")==0) {
    c->x = stPrint("%d", argIdx++);
    if (argIdx > argTop) argTop = argIdx;
  } else if (isMember(op, "++ --")) {
    VmCode *tc = lookup(d);
    printf("op=%s d=%s dc->p1=%s\n", op, d, tc->p1);
    c->x = tc->p1;
  } else if (isMember(op, "[]")) {
    VmCode *tc = lookup(p1);
    printf("op=%s p1=%s dc->p1=%s\n", op, p1, tc->p1);
    c->x = tc->p1;
  }
  return c;
}

VmCode *vmLabel(char *label) {
  return vmCode("label", label, "", "");
}

VmCode *vmGlobal(char *op, char *d, char *p1, char *p2) {
  vmGlobals[vmGlobalTop] = vmCodeNew(op, d, p1, p2);
  VmCode *c = &vmGlobals[vmGlobalTop++];
  if (strcmp(op, "global")==0) {
    c->_d = stPrint("_%s", c->d);
  }
  mapAdd(&symGlobal, d, c);
  return c;
}

char *vmNextLabel(char *prefix) {
  return stPrint("_%s%d", prefix, labelIdx++);
}

char *vmNextTemp() {
  char *temp = stPrint("t%d", tempIdx++);
  if (tempIdx > tempTop) {
    vmCode("local", temp, "", "");
    tempTop = tempIdx;
  }
  return temp;
}

void vmDump(VmCode *codes, int top) {
  printf("=============vmDump()==============\n");
  for (int i=0; i<top; i++) {
    VmCode *c = &codes[i];
    printf("%-8s %-8s %-8s %-8s # %-8s %-8s %-8s # %-8s\n", c->op, c->d, c->p1, c->p2, c->_d, c->_p1, c->_p2, c->x);
  }
}

void asmInit(char *file) {
  char sFileName[SMAX];
  sprintf(sFileName, "%s0.s", file);
  sFile = fopen(sFileName, "wt");
}

void asmCode(VmCode *c) {
  asmEmit("# %-8s %-8s %-8s %-8s # %-8s %-8s %-8s # %-8s\n", c->op, c->d, c->p1, c->p2, c->_d, c->_p1, c->_p2, c->x);
  xCode(c->op, c->_d, c->_p1, c->_p2, c->x);
}

void asmClose() {
  fclose(sFile);
}

void vmToAsm(char *file) {
  asmInit(file);
  printf("=============vmToAsm()==============\n");
  for (int i=0; i<vmGlobalTop; i++) {
    VmCode *c = &vmGlobals[i];
    asmCode(c);
  }
  for (int i=0; i<vmCodeTop; i++) {
    VmCode *c = &vmCodes[i];
    asmCode(c);
  }
  asmClose();
}
