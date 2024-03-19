int twotimes(const char *s);
int twotimes2(const char *begin, const char *end);

int twotimes(const char *s)
{
    // reuse the code from twotimes2
    const char *p = s;
    while (*p)
        p++;
    return twotimes2(s, p);
}

int twotimes2(const char *begin, const char *end)
{
    // if the string have not an even length, then can't be made from two equal substrings
    unsigned int length = end - begin;
    if (length & 1 != 0)
        return 0;

    // proceed confronting the string from the beginning and the middle, if the characters
    // don't match, return 0, otherwise at the end, return 1
    for (const char *middle = begin + length / 2; middle != end; middle++, begin++)
    {
        if (*begin != *middle)
            return 0;
    }
    return 1;
}
