/* 
  This is an interview question I came across this morning (which I think I screwed up in making several mistakes and responding too slowly). 
  The interviewer asked me to implement a function to count the occurence of characters 'a' in a given character string, 
  without involving conditional jump instructions. 
  The most straightforward way is to use a loop and check each character once. (never use "strlen" in the loop condition, 
  it is a O(n) operation, for example:
  for (int i = 0; i < strlen(s); i++)
  Instead, code as follows:
  for (int i = 0; s[i]; i++)
  
  However, the tricky thing is the condition judgment inside the iteration condition. 
  I was asked to eliminate any conditional jump instruction here. 
  The basic idea is to use a function pointer and match it to respective function calls for continuing or terminating the loop condition, depending on wether a termination char null is hit.
  Below is the code I came up with and verified. 
  
  According to the output of "objdump -d xxx", it does not contain any conditional jump instructions (i.e. beq, bne) in the assembly code for the "countas" function. 
  00000000004007e4 <_Z5checkPc>:
  4007e4:       55                      push   %rbp
  4007e5:       48 89 e5                mov    %rsp,%rbp
  4007e8:       53                      push   %rbx
  4007e9:       48 83 ec 18             sub    $0x18,%rsp
  4007ed:       48 89 7d e8             mov    %rdi,-0x18(%rbp)
  4007f1:       48 8b 45 e8             mov    -0x18(%rbp),%rax
  4007f5:       0f b6 00                movzbl (%rax),%eax
  4007f8:       3c 61                   cmp    $0x61,%al
  4007fa:       0f 94 c0                sete   %al
  4007fd:       0f b6 d8                movzbl %al,%ebx
  400800:       48 83 45 e8 01          addq   $0x1,-0x18(%rbp)
  400805:       48 8b 45 e8             mov    -0x18(%rbp),%rax
  400809:       48 89 c7                mov    %rax,%rdi
  40080c:       e8 19 00 00 00          callq  40082a <_Z7countasPc>
  400811:       8d 04 03                lea    (%rbx,%rax,1),%eax
  400814:       48 83 c4 18             add    $0x18,%rsp
  400818:       5b                      pop    %rbx
  400819:       c9                      leaveq
  40081a:       c3                      retq

000000000040081b <_Z10check_donePc>:
  40081b:       55                      push   %rbp
  40081c:       48 89 e5                mov    %rsp,%rbp
  40081f:       48 89 7d f8             mov    %rdi,-0x8(%rbp)
  400823:       b8 00 00 00 00          mov    $0x0,%eax
  400828:       c9                      leaveq
  400829:       c3                      retq

000000000040082a <_Z7countasPc>:
  40082a:       55                      push   %rbp
  40082b:       48 89 e5                mov    %rsp,%rbp
  40082e:       48 83 ec 20             sub    $0x20,%rsp
  400832:       48 89 7d e8             mov    %rdi,-0x18(%rbp)
  400836:       48 c7 45 f0 e4 07 40    movq   $0x4007e4,-0x10(%rbp)
  40083d:       00
  40083e:       48 c7 45 f8 1b 08 40    movq   $0x40081b,-0x8(%rbp)
  400845:       00
  400846:       48 8b 45 e8             mov    -0x18(%rbp),%rax
  40084a:       0f b6 00                movzbl (%rax),%eax
  40084d:       84 c0                   test   %al,%al
  40084f:       0f 94 c0                sete   %al
  400852:       0f b6 c0                movzbl %al,%eax
  400855:       48 98                   cltq
  400857:       48 8b 54 c5 f0          mov    -0x10(%rbp,%rax,8),%rdx
  40085c:       48 8b 45 e8             mov    -0x18(%rbp),%rax
  400860:       48 89 c7                mov    %rax,%rdi
  400863:       ff d2                   callq  *%rdx
  400865:       c9                      leaveq
  400866:       c3                      retq

*/

#include <iostream>
using namespace std;

int countas(char* s);

int check(char* s)
{
     return (s[0]=='a') + countas(++s);
}

int check_done(char* s)
{
     return 0;
}

int countas(char* s)
{
     int (*count_char[])(char*) = {check, check_done};
     return count_char[s[0]==0](s);
}

int main()
{
     cout << countas("aaaaa") << endl;
     cout << countas("aabda") << endl;
     cout << countas("bbbbcc") << endl;
}
