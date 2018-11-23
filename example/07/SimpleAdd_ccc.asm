@SP     // SP=256
M=256
// push constant 7  
// 1. _val_to_stack(val)
@7      // 1.1 _a_command(val)                # A=val
D=A     // 1.2 _c_command('D', 'A')           # D=A
        // 1.3 _comp_to_stack(comp='D')
        //   1.3.1 _load_sp()
@SP     //     1.3.1.1 self._a_command('SP')               # A=&SP
A=M     //     1.3.1.2 self._c_command('A', 'M')           # A=SP
M=D  		//   1.3.2 _c_command('M', comp)
// 2. _inc_sp(self):
@SP     // 2.1 self._a_command('SP')               # A=&SP
M=M+1   // 2.2 self._c_command('M', 'M+1')         # SP=SP+1
// push constant 8
@8
D=A
@SP
M=D
@SP
M=M+1
// add // if   command == 'add':  self._binary(comp='D+A')
// 1. self._dec_sp()                      # --SP
@SP
M=M-1
// 2. self._stack_to_dest('D')            # D=*SP
//      self._load_sp()
@SP
A=M 				
        self._c_command(dest, 'M')          # dest=*SP
D=M
// 3. self._dec_sp()                      # --SP
@SP
M=M-1
// 4. self._stack_to_dest('A')            # A=*SP
@SP
A=M // A=SP
A=M // A=*SP
// 5. self._c_command('D', comp)          # D=comp
D=D+A
// 6. self._comp_to_stack('D')            # *SP=D
...   // 6.1  self._load_sp()
M=D+A // 6.2  self._c_command('M', comp)          # *SP=comp

// 7. self._inc_sp()                      # ++SP
@SP
M=M+1

