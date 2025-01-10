
void isr_svcall(void)
{
    /*uint32_t type,param;
    asm volatile ("\t mov %0, r0\n" : "=r" (type));
	asm volatile ("\t mov %0, r7\n" : "=r" (param));
    switch (type)
    {
    case 1:
        printf("Getting signal: %d",param);
        break;
    
    default:
        printf("Not valid type: %d param: %d",type,param);
        break;
    }*/
   printf("Got signal");
}