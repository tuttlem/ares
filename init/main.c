
void main() {
   // just throw a crap-load of red/blue A's to the console
   unsigned char *console = (unsigned char *)0xb8000;
   int i;
   for (i = 0; i < 100; i ++) {
      console[i] = 65;
   }
   while (1);
}

