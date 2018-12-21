    function   sum                             
    param      n                               
    local      s          var                  
    local      i          var                  
    =          s          0                    
    =          i          1                    
(WBEGIN0)
    <=         $t0        i          n         
    jnz        WEND1      $t0                  
    +          $t0        s          i         
    =          s          $t0                  
    +          $t0        i          1         
    =          i          $t0                  
    jmp        WBEGIN0                         
(WEND1)
    return     s                               
    fend       sum                             
    push       10                              
    call       $t0        sum                  
    =          s          $t0                  
    str        S2         "sum=%s\n"           
    push       S2                              
    push       s                               
    call       $t0        printf               
