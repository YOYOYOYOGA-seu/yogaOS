00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
00007C00  EB75              jmp short 0x7c77
00007C02  90                nop
00007C03  59                pop cx
00007C04  4F                dec di
00007C05  59                pop cx
00007C06  4F                dec di
00007C07  59                pop cx
00007C08  4F                dec di
00007C09  47                inc di
00007C0A  41                inc cx
00007C0B  0002              add [bp+si],al
00007C0D  0101              add [bx+di],ax
00007C0F  0002              add [bp+si],al
00007C11  A00040            mov al,[0x4000]
00007C14  0BF0              or si,ax
00007C16  0900              or [bx+si],ax
00007C18  1200              adc al,[bx+si]
00007C1A  0200              add al,[bx+si]
00007C1C  0000              add [bx+si],al
00007C1E  0000              add [bx+si],al
00007C20  0000              add [bx+si],al
00007C22  0000              add [bx+si],al
00007C24  0000              add [bx+si],al
00007C26  2900              sub [bx+si],ax
00007C28  0000              add [bx+si],al
00007C2A  007379            add [bp+di+0x79],dh
00007C2D  7374              jnc 0x7ca3
00007C2F  656D              gs insw
00007C31  46                inc si
00007C32  696C657346        imul bp,[si+0x65],word 0x4673
00007C37  41                inc cx
00007C38  54                push sp
00007C39  3132              xor [bp+si],si
00007C3B  2020              and [bx+si],ah
00007C3D  2000              and [bx+si],al
00007C3F  1200              adc al,[bx+si]
00007C41  4C                dec sp
00007C42  4F                dec di
00007C43  41                inc cx
00007C44  44                inc sp
00007C45  45                inc bp
00007C46  52                push dx
00007C47  2020              and [bx+si],ah
00007C49  42                inc dx
00007C4A  49                dec cx
00007C4B  4E                dec si
00007C4C  204E6F            and [bp+0x6f],cl
00007C4F  20626F            and [bp+si+0x6f],ah
00007C52  6F                outsw
00007C53  7446              jz 0x7c9b
00007C55  696C65210A        imul bp,[si+0x65],word 0xa21
00007C5A  0D4669            or ax,0x6946
00007C5D  6E                outsb
00007C5E  64206C6F          and [fs:si+0x6f],ch
00007C62  61                popa
00007C63  6465722E          gs jc 0x7c95
00007C67  0A0D              or cl,[di]
00007C69  46                inc si
00007C6A  696E697368        imul bp,[bp+0x69],word 0x6873
00007C6F  206C6F            and [si+0x6f],ch
00007C72  61                popa
00007C73  642E0A0D          or cl,[cs:di]
00007C77  8CC8              mov ax,cs
00007C79  8ED8              mov ds,ax
00007C7B  8EC0              mov es,ax
00007C7D  8ED0              mov ss,ax
00007C7F  BC007C            mov sp,0x7c00
00007C82  B400              mov ah,0x0
00007C84  8A16247C          mov dl,[0x7c24]
00007C88  CD13              int 0x13
00007C8A  B80200            mov ax,0x2
00007C8D  CD10              int 0x10
00007C8F  B8007E            mov ax,0x7e00
00007C92  C1E804            shr ax,byte 0x4
00007C95  8EC0              mov es,ax
00007C97  83063F7C01        add word [0x7c3f],byte +0x1
00007C9C  B101              mov cl,0x1
00007C9E  A13F7C            mov ax,[0x7c3f]
00007CA1  BB0000            mov bx,0x0
00007CA4  E8D600            call 0x7d7d
00007CA7  E80B00            call 0x7cb5
00007CAA  833E3F7C1D        cmp word [0x7c3f],byte +0x1d
00007CAF  0F831101          jnc near 0x7dc4
00007CB3  EBE2              jmp short 0x7c97
00007CB5  BF417C            mov di,0x7c41
00007CB8  BB0000            mov bx,0x0
00007CBB  89DE              mov si,bx
00007CBD  B103              mov cl,0x3
00007CBF  26668B04          mov eax,[es:si]
00007CC3  663B05            cmp eax,[di]
00007CC6  7513              jnz 0x7cdb
00007CC8  83C704            add di,byte +0x4
00007CCB  83C604            add si,byte +0x4
00007CCE  E2EF              loop 0x7cbf
00007CD0  BF5B7C            mov di,0x7c5b
00007CD3  B90E00            mov cx,0xe
00007CD6  E8D500            call 0x7dae
00007CD9  EB13              jmp short 0x7cee
00007CDB  3B1E0B7C          cmp bx,[0x7c0b]
00007CDF  730C              jnc 0x7ced
00007CE1  83C320            add bx,byte +0x20
00007CE4  89DE              mov si,bx
00007CE6  BF417C            mov di,0x7c41
00007CE9  B103              mov cl,0x3
00007CEB  EBD2              jmp short 0x7cbf
00007CED  C3                ret
00007CEE  83C60E            add si,byte +0xe
00007CF1  268B04            mov ax,[es:si]
00007CF4  83C01B            add ax,byte +0x1b
00007CF7  A33F7C            mov [0x7c3f],ax
00007CFA  B101              mov cl,0x1
00007CFC  A10E7C            mov ax,[0x7c0e]
00007CFF  BB0000            mov bx,0x0
00007D02  E87800            call 0x7d7d
00007D05  B80080            mov ax,0x8000
00007D08  89C7              mov di,ax
00007D0A  83E70F            and di,byte +0xf
00007D0D  C1E804            shr ax,byte 0x4
00007D10  8EE8              mov gs,ax
00007D12  BE0300            mov si,0x3
00007D15  B9FF00            mov cx,0xff
00007D18  268B04            mov ax,[es:si]
00007D1B  25FF0F            and ax,0xfff
00007D1E  658905            mov [gs:di],ax
00007D21  83C702            add di,byte +0x2
00007D24  46                inc si
00007D25  268B04            mov ax,[es:si]
00007D28  C1E804            shr ax,byte 0x4
00007D2B  658905            mov [gs:di],ax
00007D2E  83C702            add di,byte +0x2
00007D31  83C602            add si,byte +0x2
00007D34  E2E2              loop 0x7d18
00007D36  66B800000900      mov eax,0x90000
00007D3C  66C1E804          shr eax,byte 0x4
00007D40  8EC0              mov es,ax
00007D42  BB0000            mov bx,0x0
00007D45  A13F7C            mov ax,[0x7c3f]
00007D48  89C7              mov di,ax
00007D4A  83EF1D            sub di,byte +0x1d
00007D4D  D1E7              shl di,1
00007D4F  B101              mov cl,0x1
00007D51  E82900            call 0x7d7d
00007D54  658B05            mov ax,[gs:di]
00007D57  3DFF0F            cmp ax,0xfff
00007D5A  7410              jz 0x7d6c
00007D5C  031E0B7C          add bx,[0x7c0b]
00007D60  83C01B            add ax,byte +0x1b
00007D63  89C7              mov di,ax
00007D65  83EF1D            sub di,byte +0x1d
00007D68  D1E7              shl di,1
00007D6A  EBE3              jmp short 0x7d4f
00007D6C  BF697C            mov di,0x7c69
00007D6F  B90E00            mov cx,0xe
00007D72  E83900            call 0x7dae
00007D75  66EA001800000090  jmp dword 0x9000:0x1800
00007D7D  55                push bp
00007D7E  6683EC02          sub esp,byte +0x2
00007D82  89E5              mov bp,sp
00007D84  884E00            mov [bp+0x0],cl
00007D87  F636187C          div byte [0x7c18]
00007D8B  FEC4              inc ah
00007D8D  88E1              mov cl,ah
00007D8F  88C5              mov ch,al
00007D91  88C6              mov dh,al
00007D93  D0ED              shr ch,1
00007D95  80E601            and dh,0x1
00007D98  8A4600            mov al,[bp+0x0]
00007D9B  8A16247C          mov dl,[0x7c24]
00007D9F  B402              mov ah,0x2
00007DA1  8A4600            mov al,[bp+0x0]
00007DA4  CD13              int 0x13
00007DA6  72F7              jc 0x7d9f
00007DA8  6683C402          add esp,byte +0x2
00007DAC  5D                pop bp
00007DAD  C3                ret
00007DAE  1E                push ds
00007DAF  53                push bx
00007DB0  B80000            mov ax,0x0
00007DB3  8ED8              mov ds,ax
00007DB5  8A05              mov al,[di]
00007DB7  B40E              mov ah,0xe
00007DB9  BB1500            mov bx,0x15
00007DBC  CD10              int 0x10
00007DBE  47                inc di
00007DBF  E2F4              loop 0x7db5
00007DC1  5B                pop bx
00007DC2  1F                pop ds
00007DC3  C3                ret
00007DC4  EB00              jmp short 0x7dc6
00007DC6  F4                hlt
00007DC7  EBFD              jmp short 0x7dc6
00007DC9  0000              add [bx+si],al
00007DCB  0000              add [bx+si],al
00007DCD  0000              add [bx+si],al
00007DCF  0000              add [bx+si],al
00007DD1  0000              add [bx+si],al
00007DD3  0000              add [bx+si],al
00007DD5  0000              add [bx+si],al
00007DD7  0000              add [bx+si],al
00007DD9  0000              add [bx+si],al
00007DDB  0000              add [bx+si],al
00007DDD  0000              add [bx+si],al
00007DDF  0000              add [bx+si],al
00007DE1  0000              add [bx+si],al
00007DE3  0000              add [bx+si],al
00007DE5  0000              add [bx+si],al
00007DE7  0000              add [bx+si],al
00007DE9  0000              add [bx+si],al
00007DEB  0000              add [bx+si],al
00007DED  0000              add [bx+si],al
00007DEF  0000              add [bx+si],al
00007DF1  0000              add [bx+si],al
00007DF3  0000              add [bx+si],al
00007DF5  0000              add [bx+si],al
00007DF7  0000              add [bx+si],al
00007DF9  0000              add [bx+si],al
00007DFB  0000              add [bx+si],al
00007DFD  0055AA            add [di-0x56],dl
