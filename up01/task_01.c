int bitcount(STYPE value)
{
    UTYPE uvalue = (UTYPE) value;

    int counter = 0;
    while(uvalue != 0)
    {
        if((uvalue&1) == 1) counter++;
        uvalue >>= 1;
    }

    return counter;
}
