// https://stackoverflow.com/questions/1472138/c-default-arguments
#include <stdio.h>                                                               

struct range { int from; int to; int step; };
#define range(...) range((struct range){.from=1,.to=10,.step=1, __VA_ARGS__})   

/* use parentheses to avoid macro subst */             
void (range)(struct range r) {                                                     
    for (int i = r.from; i <= r.to; i += r.step)                                 
        printf("%d ", i);                                                        
    puts("");                                                                    
}                                                                                

int main() {                                                                     
    range();                                                                    
    range(.from=2, .to=4);                                                      
    range(.step=2);                                                             
}  