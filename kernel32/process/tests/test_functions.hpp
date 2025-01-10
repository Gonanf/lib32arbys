int hello_world(){
    int a = 2;
    int b = 3;
    char text[] = "hello world";
    printf("Hola mundo");
    /*asm volatile("\t push {r7, r0, lr}\n");
    asm volatile("\t movs r0, #1\n");
    asm volatile("\t movs r7, #100\n");
    asm volatile("\t pop {r7, r0, pc}\n");*/
    //asm volatile("\t SVC 0 \n");
    return 0;
}