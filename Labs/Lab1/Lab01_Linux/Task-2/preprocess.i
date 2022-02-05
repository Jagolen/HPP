# 1 "preprocess.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "preprocess.c"
# 1 "preprocess.h" 1






int add(int, int);

void function_we_dont_use();
# 2 "preprocess.c" 2




int main()
{
   int two = 2;
   int sum = add(two, 9);
}

int add(int a, int b)
{
   return a + b;
}
