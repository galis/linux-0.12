# 1 "/Volumes/mac-code/linux-0.12/kernel/vsprintf.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/Volumes/mac-code/linux-0.12/kernel/vsprintf.c"
# 12 "/Volumes/mac-code/linux-0.12/kernel/vsprintf.c"
# 1 "/Volumes/mac-code/linux-0.12/include/stdarg.h" 1



typedef char *va_list;
# 21 "/Volumes/mac-code/linux-0.12/include/stdarg.h"
void va_end (va_list);
# 13 "/Volumes/mac-code/linux-0.12/kernel/vsprintf.c" 2
# 1 "/Volumes/mac-code/linux-0.12/include/string.h" 1
# 10 "/Volumes/mac-code/linux-0.12/include/string.h"
typedef unsigned int size_t;


extern char * strerror(int errno);
# 27 "/Volumes/mac-code/linux-0.12/include/string.h"
static inline char * strcpy(char * dest,const char *src)
{
__asm__("cld\n"
 "1:\tlodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b"
 ::"S" (src),"D" (dest):) ;
return dest;
}

static inline char * strncpy(char * dest,const char *src,int count)
{
__asm__("cld\n"
 "1:\tdecl %2\n\t"
 "js 2f\n\t"
 "lodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n\t"
 "rep\n\t"
 "stosb\n"
 "2:"
 ::"S" (src),"D" (dest),"c" (count):) ;
return dest;
}

static inline char * strcat(char * dest,const char * src)
{
__asm__("cld\n\t"
 "repne\n\t"
 "scasb\n\t"
 "decl %1\n"
 "1:\tlodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b"
 ::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff):) ;
return dest;
}

static inline char * strncat(char * dest,const char * src,int count)
{
__asm__("cld\n\t"
 "repne\n\t"
 "scasb\n\t"
 "decl %1\n\t"
 "movl %4,%3\n"
 "1:\tdecl %3\n\t"
 "js 2f\n\t"
 "lodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n"
 "2:\txorl %2,%2\n\t"
 "stosb"
 ::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff),"g" (count)
 :) ;
return dest;
}

static inline int strcmp(const char * cs,const char * ct)
{
register int __res __asm__("ax");
__asm__("cld\n"
 "1:\tlodsb\n\t"
 "scasb\n\t"
 "jne 2f\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n\t"
 "xorl %%eax,%%eax\n\t"
 "jmp 3f\n"
 "2:\tmovl $1,%%eax\n\t"
 "jl 3f\n\t"
 "negl %%eax\n"
 "3:"
 :"=a" (__res):"D" (cs),"S" (ct):) ;
return __res;
}

static inline int strncmp(const char * cs,const char * ct,int count)
{
register int __res __asm__("ax");
__asm__("cld\n"
 "1:\tdecl %3\n\t"
 "js 2f\n\t"
 "lodsb\n\t"
 "scasb\n\t"
 "jne 3f\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n"
 "2:\txorl %%eax,%%eax\n\t"
 "jmp 4f\n"
 "3:\tmovl $1,%%eax\n\t"
 "jl 4f\n\t"
 "negl %%eax\n"
 "4:"
 :"=a" (__res):"D" (cs),"S" (ct),"c" (count):) ;
return __res;
}

static inline char * strchr(const char * s,char c)
{
register char * __res __asm__("ax");
__asm__("cld\n\t"
 "movb %%al,%%ah\n"
 "1:\tlodsb\n\t"
 "cmpb %%ah,%%al\n\t"
 "je 2f\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n\t"
 "movl $1,%1\n"
 "2:\tmovl %1,%0\n\t"
 "decl %0"
 :"=a" (__res):"S" (s),"0" (c):) ;
return __res;
}

static inline char * strrchr(const char * s,char c)
{
register char * __res __asm__("dx");
__asm__("cld\n\t"
 "movb %%al,%%ah\n"
 "1:\tlodsb\n\t"
 "cmpb %%ah,%%al\n\t"
 "jne 2f\n\t"
 "movl %%esi,%0\n\t"
 "decl %0\n"
 "2:\ttestb %%al,%%al\n\t"
 "jne 1b"
 :"=d" (__res):"0" (0),"S" (s),"a" (c):) ;
return __res;
}

static inline int strspn(const char * cs, const char * ct)
{
register char * __res __asm__("si");
__asm__("cld\n\t"
 "movl %4,%%edi\n\t"
 "repne\n\t"
 "scasb\n\t"
 "notl %%ecx\n\t"
 "decl %%ecx\n\t"
 "movl %%ecx,%%edx\n"
 "1:\tlodsb\n\t"
 "testb %%al,%%al\n\t"
 "je 2f\n\t"
 "movl %4,%%edi\n\t"
 "movl %%edx,%%ecx\n\t"
 "repne\n\t"
 "scasb\n\t"
 "je 1b\n"
 "2:\tdecl %0"
 :"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
 :) ;
return __res-cs;
}

static inline int strcspn(const char * cs, const char * ct)
{
register char * __res __asm__("si");
__asm__("cld\n\t"
 "movl %4,%%edi\n\t"
 "repne\n\t"
 "scasb\n\t"
 "notl %%ecx\n\t"
 "decl %%ecx\n\t"
 "movl %%ecx,%%edx\n"
 "1:\tlodsb\n\t"
 "testb %%al,%%al\n\t"
 "je 2f\n\t"
 "movl %4,%%edi\n\t"
 "movl %%edx,%%ecx\n\t"
 "repne\n\t"
 "scasb\n\t"
 "jne 1b\n"
 "2:\tdecl %0"
 :"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
 :) ;
return __res-cs;
}

static inline char * strpbrk(const char * cs,const char * ct)
{
register char * __res __asm__("si");
__asm__("cld\n\t"
 "movl %4,%%edi\n\t"
 "repne\n\t"
 "scasb\n\t"
 "notl %%ecx\n\t"
 "decl %%ecx\n\t"
 "movl %%ecx,%%edx\n"
 "1:\tlodsb\n\t"
 "testb %%al,%%al\n\t"
 "je 2f\n\t"
 "movl %4,%%edi\n\t"
 "movl %%edx,%%ecx\n\t"
 "repne\n\t"
 "scasb\n\t"
 "jne 1b\n\t"
 "decl %0\n\t"
 "jmp 3f\n"
 "2:\txorl %0,%0\n"
 "3:"
 :"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
 :) ;
return __res;
}

static inline char * strstr(const char * cs,const char * ct)
{
register char * __res __asm__("ax");
__asm__("cld\n\t"
 "movl %4,%%edi\n\t"
 "repne\n\t"
 "scasb\n\t"
 "notl %%ecx\n\t"
 "decl %%ecx\n\t"
 "movl %%ecx,%%edx\n"
 "1:\tmovl %4,%%edi\n\t"
 "movl %%esi,%%eax\n\t"
 "movl %%edx,%%ecx\n\t"
 "repe\n\t"
 "cmpsb\n\t"
 "je 2f\n\t"
 "xchgl %%eax,%%esi\n\t"
 "incl %%esi\n\t"
 "cmpb $0,-1(%%eax)\n\t"
 "jne 1b\n\t"
 "xorl %%eax,%%eax\n\t"
 "2:"
 :"=a" (__res):"0" (0),"c" (0xffffffff),"S" (cs),"g" (ct)
 :) ;
return __res;
}

static inline int strlen(const char * s)
{
register int __res __asm__("cx");
__asm__("cld\n\t"
 "repne\n\t"
 "scasb\n\t"
 "notl %0\n\t"
 "decl %0"
 :"=c" (__res):"D" (s),"a" (0),"0" (0xffffffff):) ;
return __res;
}

extern char * ___strtok;

static inline char * strtok(char * s,const char * ct)
{
register char * __res __asm__("si");
__asm__("testl %1,%1\n\t"
 "jne 1f\n\t"
 "testl %0,%0\n\t"
 "je 8f\n\t"
 "movl %0,%1\n"
 "1:\txorl %0,%0\n\t"
 "movl $-1,%%ecx\n\t"
 "xorl %%eax,%%eax\n\t"
 "cld\n\t"
 "movl %4,%%edi\n\t"
 "repne\n\t"
 "scasb\n\t"
 "notl %%ecx\n\t"
 "decl %%ecx\n\t"
 "je 7f\n\t"
 "movl %%ecx,%%edx\n"
 "2:\tlodsb\n\t"
 "testb %%al,%%al\n\t"
 "je 7f\n\t"
 "movl %4,%%edi\n\t"
 "movl %%edx,%%ecx\n\t"
 "repne\n\t"
 "scasb\n\t"
 "je 2b\n\t"
 "decl %1\n\t"
 "cmpb $0,(%1)\n\t"
 "je 7f\n\t"
 "movl %1,%0\n"
 "3:\tlodsb\n\t"
 "testb %%al,%%al\n\t"
 "je 5f\n\t"
 "movl %4,%%edi\n\t"
 "movl %%edx,%%ecx\n\t"
 "repne\n\t"
 "scasb\n\t"
 "jne 3b\n\t"
 "decl %1\n\t"
 "cmpb $0,(%1)\n\t"
 "je 5f\n\t"
 "movb $0,(%1)\n\t"
 "incl %1\n\t"
 "jmp 6f\n"
 "5:\txorl %1,%1\n"
 "6:\tcmpb $0,(%0)\n\t"
 "jne 7f\n\t"
 "xorl %0,%0\n"
 "7:\ttestl %0,%0\n\t"
 "jne 8f\n\t"
 "movl %0,%1\n"
 "8:"
 :"=b" (__res),"=S" (___strtok)
 :"0" (___strtok),"1" (s),"g" (ct)
 :) ;
return __res;
}

static inline void * memcpy(void * dest,const void * src, int n)
{
__asm__("cld\n\t"
 "rep\n\t"
 "movsb"
 ::"c" (n),"S" (src),"D" (dest)
 :) ;
return dest;
}

static inline void * memmove(void * dest,const void * src, int n)
{
if (dest<src)
__asm__("cld\n\t"
 "rep\n\t"
 "movsb"
 ::"c" (n),"S" (src),"D" (dest)
 :) ;
else
__asm__("std\n\t"
 "rep\n\t"
 "movsb"
 ::"c" (n),"S" (src+n-1),"D" (dest+n-1)
 :) ;
return dest;
}

static inline int memcmp(const void * cs,const void * ct,int count)
{
register int __res __asm__("ax");
__asm__("cld\n\t"
 "repe\n\t"
 "cmpsb\n\t"
 "je 1f\n\t"
 "movl $1,%%eax\n\t"
 "jl 1f\n\t"
 "negl %%eax\n"
 "1:"
 :"=a" (__res):"0" (0),"D" (cs),"S" (ct),"c" (count)
 :) ;
return __res;
}

static inline void * memchr(const void * cs,char c,int count)
{
register void * __res __asm__("di");
if (!count)
 return ((void *) 0);
__asm__("cld\n\t"
 "repne\n\t"
 "scasb\n\t"
 "je 1f\n\t"
 "movl $1,%0\n"
 "1:\tdecl %0"
 :"=D" (__res):"a" (c),"D" (cs),"c" (count)
 :) ;
return __res;
}

static inline void * memset(void * s,char c,int count)
{
__asm__("cld\n\t"
 "rep\n\t"
 "stosb"
 ::"a" (c),"D" (s),"c" (count)
 :) ;
return s;
}
# 14 "/Volumes/mac-code/linux-0.12/kernel/vsprintf.c" 2




static int skip_atoi(const char **s)
{
 int i=0;

 while (((**s) >= '0' && (**s) <= '9'))
  i = i*10 + *((*s)++) - '0';
 return i;
}
# 40 "/Volumes/mac-code/linux-0.12/kernel/vsprintf.c"
static char * number(char * str, int num, int base, int size, int precision
 ,int type)
{
 char c,sign,tmp[36];
 const char *digits="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 int i;

 if (type&64) digits="0123456789abcdefghijklmnopqrstuvwxyz";
 if (type&16) type &= ~1;
 if (base<2 || base>36)
  return 0;
 c = (type & 1) ? '0' : ' ' ;
 if (type&2 && num<0) {
  sign='-';
  num = -num;
 } else
  sign=(type&4) ? '+' : ((type&8) ? ' ' : 0);
 if (sign) size--;
 if (type&32)
  if (base==16) size -= 2;
  else if (base==8) size--;
 i=0;
 if (num==0)
  tmp[i++]='0';
 else while (num!=0)
  tmp[i++]=digits[({ int __res; __asm__("divl %4":"=a" (num),"=d" (__res):"0" (num),"1" (0),"r" (base)); __res; })];
 if (i>precision) precision=i;
 size -= precision;
 if (!(type&(1 +16)))
  while(size-->0)
   *str++ = ' ';
 if (sign)
  *str++ = sign;
 if (type&32)
  if (base==8)
   *str++ = '0';
  else if (base==16) {
   *str++ = '0';
   *str++ = digits[33];
  }
 if (!(type&16))
  while(size-->0)
   *str++ = c;
 while(i<precision--)
  *str++ = '0';
 while(i-->0)
  *str++ = tmp[i];
 while(size-->0)
  *str++ = ' ';
 return str;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
 int len;
 int i;
 char * str;
 char *s;
 int *ip;

 int flags;

 int field_width;
 int precision;

 int qualifier;

 for (str=buf ; *fmt ; ++fmt) {
  if (*fmt != '%') {
   *str++ = *fmt;
   continue;
  }


  flags = 0;
  repeat:
   ++fmt;
   switch (*fmt) {
    case '-': flags |= 16; goto repeat;
    case '+': flags |= 4; goto repeat;
    case ' ': flags |= 8; goto repeat;
    case '#': flags |= 32; goto repeat;
    case '0': flags |= 1; goto repeat;
    }


  field_width = -1;
  if (((*fmt) >= '0' && (*fmt) <= '9'))
   field_width = skip_atoi(&fmt);
  else if (*fmt == '*') {

   field_width = (args += (((sizeof (int) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((int *) (args - (((sizeof (int) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)))));
   if (field_width < 0) {
    field_width = -field_width;
    flags |= 16;
   }
  }


  precision = -1;
  if (*fmt == '.') {
   ++fmt;
   if (((*fmt) >= '0' && (*fmt) <= '9'))
    precision = skip_atoi(&fmt);
   else if (*fmt == '*') {

    precision = (args += (((sizeof (int) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((int *) (args - (((sizeof (int) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)))));
   }
   if (precision < 0)
    precision = 0;
  }


  qualifier = -1;
  if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
   qualifier = *fmt;
   ++fmt;
  }

  switch (*fmt) {
  case 'c':
   if (!(flags & 16))
    while (--field_width > 0)
     *str++ = ' ';
   *str++ = (unsigned char) (args += (((sizeof (int) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((int *) (args - (((sizeof (int) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)))));
   while (--field_width > 0)
    *str++ = ' ';
   break;

  case 's':
   s = (args += (((sizeof (char *) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((char * *) (args - (((sizeof (char *) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)))));
   len = strlen(s);
   if (precision < 0)
    precision = len;
   else if (len > precision)
    len = precision;

   if (!(flags & 16))
    while (len < field_width--)
     *str++ = ' ';
   for (i = 0; i < len; ++i)
    *str++ = *s++;
   while (len < field_width--)
    *str++ = ' ';
   break;

  case 'o':
   str = number(str, (args += (((sizeof (unsigned long) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((unsigned long *) (args - (((sizeof (unsigned long) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))))), 8,
    field_width, precision, flags);
   break;

  case 'p':
   if (field_width == -1) {
    field_width = 8;
    flags |= 1;
   }
   str = number(str,
    (unsigned long) (args += (((sizeof (void *) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((void * *) (args - (((sizeof (void *) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))))), 16,
    field_width, precision, flags);
   break;

  case 'x':
   flags |= 64;
  case 'X':
   str = number(str, (args += (((sizeof (unsigned long) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((unsigned long *) (args - (((sizeof (unsigned long) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))))), 16,
    field_width, precision, flags);
   break;

  case 'd':
  case 'i':
   flags |= 2;
  case 'u':
   str = number(str, (args += (((sizeof (unsigned long) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((unsigned long *) (args - (((sizeof (unsigned long) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))))), 10,
    field_width, precision, flags);
   break;

  case 'n':
   ip = (args += (((sizeof (int *) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)), *((int * *) (args - (((sizeof (int *) + sizeof (int) - 1) / sizeof (int)) * sizeof (int)))));
   *ip = (str - buf);
   break;

  default:
   if (*fmt != '%')
    *str++ = '%';
   if (*fmt)
    *str++ = *fmt;
   else
    --fmt;
   break;
  }
 }
 *str = '\0';
 return str-buf;
}
