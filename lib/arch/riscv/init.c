void lib_main()
{
    volatile char *uart = (volatile char *) 0x10000000;
    uart[0] = '2';
    // TODO: we should do some preparation then goto 'main'
    while(1);
}
