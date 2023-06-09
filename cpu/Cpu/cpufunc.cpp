void regprint(cpu* proc)
{
    printf("REGISTERS: ");

    for(int i = 1; i <= 4; i++)
    {
        printf("%03d ",proc -> registers[i]);
    }

    printf("\n");
}

void cpufunc(cpu* proc, int lenOfCommandline)
{
    while (proc -> commandLine[proc -> ip] != CMD_HLT)
    {
        switch (proc -> commandLine[proc -> ip])
        {
            case CMD_PUSH:
            {
                printf("Command: push.\n");

                (proc -> ip)++;

                stkpush(&(proc -> stk), proc -> commandLine [proc -> ip]);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_POP:
            {
                printf("Command: pop.\n");

                stkpop(&(proc -> stk));

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_PUSHR:
            {
                printf("Command: pushReg.\n");

                (proc -> ip)++;

                stkpush(&(proc -> stk), proc -> registers[proc -> commandLine [proc -> ip]]);

                (proc -> ip)++;

                regprint(proc);

                printf("\n");

                break;
            }

            case CMD_POPR:
            {
                printf("Command: popReg.\n");

                (proc -> ip)++;

                proc -> registers [proc -> commandLine [proc -> ip]] = stkpop(&(proc -> stk));

                (proc -> ip)++;

                regprint(proc);

                printf("\n");

                break;
            }

            case CMD_OUT:
            {
                printf("Command: out.\n");

                printf("Out result: %d.\n",stkpop(&(proc -> stk)));

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_ADD:
            {
                printf("Command: add.\n");

                int a = stkpop(&(proc -> stk));
                printf("Param a: %d. \n", a);

                int b = stkpop(&(proc -> stk));
                printf("Param b: %d. \n", b);

                stkpush(&(proc -> stk), a+b);
                printf("Param a + Param b = %d. \n", a+b);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_SUB:
            {
                printf("Command: sub. \n");

                int a = stkpop(&(proc -> stk));
                printf("Param a: %d. \n", a);

                int b = stkpop(&(proc -> stk));
                printf("Param b: %d. \n", b);

                stkpush(&(proc -> stk), a - b);
                printf("Param a - Param b = %d. \n", a - b);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_MUL:
            {
                printf("Command: mul. \n");

                int a = stkpop(&(proc -> stk));
                printf("Param a: %d. \n", a);

                int b = stkpop(&(proc -> stk));
                printf("Param b: %d. \n", b);

                stkpush(&(proc -> stk), a * b);
                printf("Param a * Param b = %d. \n", a * b);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_DIV:
            {
                printf("Command: div. \n");

                int a = stkpop(&(proc -> stk));
                printf("Param a: %d. \n", a);

                int b = stkpop(&(proc -> stk));
                printf("Param b: %d. \n", b);

                stkpush(&(proc -> stk), ((a * 1000) / b) / 1000);
                printf("Param a / Param b = %d. \n", a / b);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_SQRT:
            {
                printf("Command: sqrt. \n");

                int a = stkpop(&(proc -> stk));
                printf("Param a: %d. \n", a);

                int sqrta = sqrt(a * 1000) / sqrt(1000);

                stkpush(&(proc -> stk), sqrta);
                printf("sqrt(a) = %d. \n", sqrta);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_IN:
            {
                printf("Command: in. \n");

                int a = 0;
                printf("Enter param a. \n");

                scanf("%d", &a);

                stkpush(&(proc -> stk), a);
                printf("Param a = %d. \n", a);

                (proc -> ip)++;

                printf("\n");

                break;
            }

            case CMD_JMP:
            {
                printf("Command: jmp. \n");

                (proc -> ip)++;

                printf("Should jump to %d position. \n", proc -> commandLine [proc -> ip]);

                proc -> ip = proc -> commandLine [proc -> ip];

                printf("Now ip is %d. \n", proc -> ip);

                printf("\n");

                break;
            }

            case CMD_JMPA:
            {
                printf("Command: jmpa. \n");

                (proc -> ip)++;

                printf("Last eleement in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 1]);

                printf("Previous element in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 2]);

                if((proc -> stk.data [(proc -> stk.size) - 1]) > (proc -> stk.data [(proc -> stk.size) - 2]))
                {
                    proc -> ip = proc -> commandLine [proc -> ip];

                    printf("Jump. Now ip is %d. \n", proc -> ip);
                }

                else
                {
                    (proc -> ip)++;

                    printf("No jump. \n");
                }

                printf("\n");

                break;
            }

            case CMD_JMPAE:
            {
                printf("Command: jmpae. \n");

                (proc -> ip)++;

                printf("Last eleement in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 1]);

                printf("Previous element in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 2]);

                if((proc -> stk.data [(proc -> stk.size) - 1]) >= (proc -> stk.data [(proc -> stk.size) - 2]))
                {
                    proc -> ip = proc -> commandLine [proc -> ip];

                    printf("Jump. Now ip is %d. \n", proc -> ip);
                }

                else
                {
                    (proc -> ip)++;

                    printf("No jump. \n");
                }

                printf("\n");

                break;
            }

            case CMD_JMPB:
            {
                printf("Command: jmpb. \n");

                (proc -> ip)++;

                printf("Last eleement in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 1]);

                printf("Previous element in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 2]);

                if((proc -> stk.data [(proc -> stk.size) - 1]) < (proc -> stk.data [(proc -> stk.size) - 2]))
                {
                    proc -> ip = proc -> commandLine [proc -> ip];

                    printf("Jump. Now ip is %d. \n", proc -> ip);
                }

                else
                {
                    (proc -> ip)++;

                    printf("No jump. \n");
                }

                printf("\n");

                break;
            }

            case CMD_JMPBE:
            {
                printf("Command: jmpbe. \n");

                (proc -> ip)++;

                printf("Last eleement in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 1]);

                printf("Previous element in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 2]);

                if((proc -> stk.data [(proc -> stk.size) - 1]) <= (proc -> stk.data [(proc -> stk.size) - 2]))
                {
                    proc -> ip = proc -> commandLine [proc -> ip];

                    printf("Jump. Now ip is %d. \n", proc -> ip);
                }

                else
                {
                    (proc -> ip)++;

                    printf("No jump. \n");
                }

                printf("\n");

                break;
            }

            case CMD_JMPE:
            {
                printf("Command: jmpe. \n");

                (proc -> ip)++;

                printf("Last eleement in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 1]);

                printf("Previous element in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 2]);

                if((proc -> stk.data [(proc -> stk.size) - 1]) == (proc -> stk.data [(proc -> stk.size) - 2]))
                {
                    proc -> ip = proc -> commandLine [proc -> ip];

                    printf("Jump. Now ip is %d. \n", proc -> ip);
                }

                else
                {
                    (proc -> ip)++;

                    printf("No jump. \n");
                }

                printf("\n");

                break;
            }

            case CMD_JMPNE:
            {
                printf("Command: jmpne. \n");

                (proc -> ip)++;

                printf("Last eleement in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 1]);

                printf("Previous element in data = %d. \n", proc -> stk.data [(proc -> stk.size) - 2]);

                if((proc -> stk.data [(proc -> stk.size) - 1]) != (proc -> stk.data [(proc -> stk.size) - 2]))
                {
                    proc -> ip = proc -> commandLine [proc -> ip];

                    printf("Jump. Now ip is %d. \n", proc -> ip);
                }

                else
                {
                    (proc -> ip)++;

                    printf("No jump. \n");
                }

                printf("\n");

                break;
            }

            default:
            {
                printf("Number of command: %d. \n", proc -> commandLine[proc -> ip]);

                printf("Sorry. Proc does not have such command. \n");

                proc -> commandLine[proc -> ip] = CMD_HLT;

                printf("\n");

                break;
            }

        }
    }
}
