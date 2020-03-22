.global enterSystemCall
/**
 * @brief  system call entery of x86 arch
 * @note  enter 0x80 interrupt
 * @param {type} none
 * @retval none
 */
enterSystemCall:
  push %eax
  push %ebx
  push %ecx
  push %edx
  mov 32(%esp), %edx
  mov 28(%esp), %ecx
  mov 24(%esp), %ebx
  mov 20(%esp), %eax
  int $0x80
  pop %edx
  pop %ecx
  pop %ebx
  pop %eax
  ret