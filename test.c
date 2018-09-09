int global;

int main()
{
    global = 0;

    for (int i = 0; i < 10; i++)
    {
        global++;
    }

    int local = 3;

    while (local > 0)
        local--;

    return 0;
}