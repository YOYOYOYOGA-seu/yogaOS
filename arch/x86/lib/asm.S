.global enterSystemCall
/**
 * @brief  system call entery of x86 arch
 * @note  enter 0x80 interrupt
 * @param {type} none
 * @retval none
 */
enterSystemCall:
  mov 16(%esp), %edx
  mov 12(%esp), %ecx
  mov 8(%esp), %ebx
  mov 4(%esp), %eax
  int $0x80
  ret