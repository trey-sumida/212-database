#ifndef record_h
#define record_h

struct record
{
    int            accountno;
    char           name[25];
    char           address[80];
    struct record* next;
};

#endif /* record_h */
